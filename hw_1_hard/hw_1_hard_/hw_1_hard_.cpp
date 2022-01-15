#include <iostream>
#include<tuple>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <optional>
#include <algorithm>

struct Person
{
	std::string surname;
	std::string name;
	std::optional<std::string> patronymic=std::nullopt;

	Person() : surname("-"),name("-"), patronymic(std::nullopt) {	};
	
	Person(const std::string& _surname, const std::string& _name, const std::string& _patronymic) : surname(_surname), name(_name) {
		_patronymic == "-" ? patronymic = std::nullopt : patronymic = _patronymic;
	};

	friend std::ostream& operator << (std::ostream& out, const Person& person);
	friend bool operator < (const Person& person1, const Person& person2);
	friend bool operator == (const Person& person1, const Person& person2);

};

std::ostream& operator << (std::ostream& out, const Person& person) {
	out << "Фамилия: " << person.surname << "   \t Имя  : " << person.name << "    \t  Отчество : " << person.patronymic.value_or("--empty--") << "   \t";
	return out;
};

bool operator < (const Person& person1, const Person& person2) {
	return std::tie(person1.surname, person1.name, person1.patronymic) <
		std::tie(person2.surname, person2.name, person2.patronymic);
};

bool operator == (const Person& person1, const Person& person2) {
	return std::tie(person1.surname, person1.name, person1.patronymic) ==
		std::tie(person2.surname, person2.name, person2.patronymic);
};

struct PhoneNumber
{
	unsigned short int countryPref;
	unsigned short int sityPref;
	std::string phoneNumber;
	unsigned short int extension;

	PhoneNumber() : countryPref(0), sityPref(0), phoneNumber("-"), extension(0) {	};
	
	PhoneNumber(unsigned short int _countryPref, unsigned short int _sityPref, const std::string& _phoneNumber, unsigned short int _extension) :
		countryPref(_countryPref), sityPref(_sityPref), phoneNumber(_phoneNumber), extension(_extension) {	};

	friend std::istream& operator >> (std::istream& in, PhoneNumber& number);
	friend std::ostream& operator << (std::ostream& out, const PhoneNumber& number);
	friend bool operator < (const PhoneNumber& number1, const PhoneNumber& number2);
	friend bool operator == (const PhoneNumber& number1, const PhoneNumber& number2);
};

std::istream& operator >> (std::istream& in, PhoneNumber& number) {
	std::cout << "введите код страны: + ";
	in >> number.countryPref;
	std::cout << "введите код города: ";
	in >> number.sityPref;
	std::cout << "введите номер телефона: ";
	in >> number.phoneNumber;
	std::cout << "введите добавочный номер если имеется: ";
	in >> number.extension;
	return in;
};

std::ostream& operator << (std::ostream& out, const PhoneNumber& number) {
	out << " tel :" << "+" << number.countryPref << "(" << number.sityPref << ")" << number.phoneNumber;
	if (number.extension != 0) {
		out << " ext " << number.extension;
	}
	return out;
};


bool operator < (const PhoneNumber& number1, const PhoneNumber& number2) {
	return std::tie(number1.countryPref, number1.sityPref, number1.phoneNumber, number1.extension) <
		std::tie(number2.countryPref, number2.sityPref, number2.phoneNumber, number2.extension);
};

bool operator == (const PhoneNumber& number1, const PhoneNumber& number2) {
	return std::tie(number1.countryPref, number1.sityPref, number1.phoneNumber, number1.extension) ==
		std::tie(number2.countryPref, number2.sityPref, number2.phoneNumber, number2.extension);
};

class PhoneBook
{
private:
	std::vector< std::pair<Person, PhoneNumber>> allPersonPhone;
public:

	PhoneBook(std::ifstream& streamFile) {
		std::string _name, _surname, _patronymic ;
		int _countryPref, _sityPref, _phoneNumber, _extension;
		while (!streamFile.eof()) {
			streamFile >> _surname >> _name >> _patronymic >> _countryPref >> _sityPref >> _phoneNumber >> _extension;
			allPersonPhone.push_back(std::pair(Person(_surname, _name, _patronymic), PhoneNumber(_countryPref, _sityPref, std::to_string(_phoneNumber), _extension)));
		}
		streamFile.close();
	};

	void SortByPhone() {
		std::sort(allPersonPhone.begin(), allPersonPhone.end(), [](const auto& n1, const auto& n2) -> bool { return n1.second < n2.second; });
	};

	void SortByName() {
		std::sort(allPersonPhone.begin(), allPersonPhone.end());
	}

	std::tuple<std::string, PhoneNumber> GetPhoneNumber(const std::string& _surname) {
		PhoneNumber pn;
		unsigned short int trigger = 0;

		for (auto it : allPersonPhone) {
			if (it.first.surname == _surname) {
				++trigger;
				pn = it.second;
				if (trigger > 1) {
					return { "found more than 1", pn };
				}
			}
		}
		if (trigger == 1) {
			return { " ", pn };
		}
		return { "not found", pn };

	}

	void ChangePhoneNumber(const Person& _person, const PhoneNumber& _phoneNumber) {
		for (auto& it : allPersonPhone) {
			if ( it.first == _person) {
				it.second  = _phoneNumber;
				//std::cout << it.first << it.second << std::endl;
			}
		}
	};

	friend std::ostream& operator << (std::ostream& out, const PhoneBook& persPh);

};

std::ostream& operator << (std::ostream& out, const PhoneBook& _allPersPhone) {
	for ( auto it : _allPersPhone.allPersonPhone)
	{
		std::cout << it.first << it.second << std::endl;
	}
	
	return out;
};


int main()
{
	setlocale(LC_ALL, "Russian");

	Person People1("Николай", "Филиппов", "Александрович");
//	Person People2("Николай", "Филиппов", "Александрович");
	Person People2("Николай", "Филиппов","-");

	std::cout << People1 << std::endl;
	std::cout << People2 << std::endl;
	std::cout << "Записи равны? " << std::boolalpha << (People1 == People2) << std::endl;

	PhoneNumber phoneNunber1;

	std::cin >> phoneNunber1;

	std::cout << phoneNunber1 << std::endl;

	std::ifstream file("PhoneBook.txt");
	if (!file)
	{
		std::cout << "Ошибка открытия файла" << std::endl;
		return 404;
	}
	PhoneBook book(file);
	std::cout << book;

	std::cout << "------SortByPhone-------" << std::endl;
	book.SortByPhone();
	std::cout << book;
	
	std::cout << "------SortByName-------" << std::endl;
	book.SortByName();
	std::cout << book;

	auto print_phone_number = [&book](const std::string& _surname) {
		std::cout << _surname << "\t";
		auto answer = book.GetPhoneNumber(_surname);
		if (std::get<0>(answer).empty()) {
			std::cout << std::get<1>(answer);
		}
		else {
			std::cout << std::get<0>(answer);
		}
		std::cout << std::endl;
	};

	print_phone_number("Ivanov");
	print_phone_number("Petrov");
	
	std::cout << "----ChangePhoneNumber----" << std::endl;
	book.ChangePhoneNumber(Person{ "Kotoff", "Vasiliy", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", 0 });
	book.ChangePhoneNumber(Person{ "Alexov", "George", "-" }, PhoneNumber{ 16, 465, "9155448", 13 });
	std::cout << book;

	system("pause");
	return 0;
}
