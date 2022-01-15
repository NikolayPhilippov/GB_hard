#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <clocale>
#include <array>
#include <string_view>

void addEndList(std::list<double>& ls) {
	double temp{ 0 };

	for (auto it : ls) {
		std::cout << it << std::endl;
		temp += it;
	}

	ls.push_back(temp / ls.size());
};

class Matrix
{
private:
	double** arr2D = nullptr;
	size_t size;

public:
	Matrix(size_t s) : size(s)
	{
		arr2D = new double* [size];
		for (size_t i = 0; i < size; ++i) {
			arr2D[i] = new double[size];
		}
	};
	
	~Matrix()
	{
		for (size_t i = 0; i < size; ++i) {
			delete[] arr2D[i];
		};
		delete[] arr2D;
	};

	void setRand() 
	{
		if (arr2D == nullptr) {
			return;
		};
		for (size_t j = 0; j < size; ++j) {
			for (size_t i = 0; i < size; ++i) {
				arr2D[j][i] = rand() % 25 + 10;
			}
		}
	};

	double determinant()
	{
		if (size == 1) {
			return arr2D[0][0];
		}

		if (size == 2) {
			return (arr2D[0][0] * arr2D[1][1] - arr2D[0][1] * arr2D[1][0]);
		}

		double det{ 1 };
		int ij; // i в j строке
		int i;
		int j;
		double step1;
		size_t stepDown{ 1 };

		while (stepDown < size) {

			j = ij = stepDown;

			while (ij != 0) { // идем к началу по i в ряду j
				--ij;
				if (arr2D[j][ij] == 0) { // 0 - дроп
					continue;
				}

				step1 = arr2D[j][ij] / arr2D[0][ij]; //  значение для делителя и юзаем всегда первую строку

				for (size_t i = 0; i < size; ++i) { // забег по сторке
					if (arr2D[j][i] == 0) { // 0 - дроп
						continue;
					}
					arr2D[j][i] = arr2D[j][i] - (arr2D[0][i] * step1); // изменили сторку j 
				}
			}
			++stepDown; // итерация
		}

		i = j = 0;
		for (; i < size; ++i, ++j) { // умножаем главную диагональ
			det *= arr2D[j][i];
			std::cout << arr2D[j][i] << " \t ";
		}
		std::cout << det << std::endl; // тест
		return det;
	};

	void print()
	{
		for (size_t j = 0; j < size; ++j) {
			for (size_t i = 0; i < size; i++) {
				std::cout << arr2D[j][i] << " \t";
			}
			std::cout << std::endl;
		}
	};

};




template <class T>
class MyArray
{
private:
	T* arr = nullptr;
	int size;

public:
	class MyIterator;
	MyArray(int s = 1) : size(s)
	{
		arr = new T[s];
	};
	
	~MyArray() { delete[] arr; };

	T& operator [] (const int& s)
	{
		if (s > 0 &&  s < size) {
			return arr[s];
		}
		return arr[0];
	};

	MyIterator begin() { return (arr); };
	MyIterator end() { return (arr + size); };

	class MyIterator
	{
	private:
		T* current;

	public:
		MyIterator(T* itr) : current(itr) { };
		~MyIterator() = default;
		T& operator + (int val) { return *(current + val); };
		T& operator - (int val) { return *(current - val); };
		T& operator ++ (int) { return *(++current); };
		T& operator -- (int) { return *(--current); };
		T& operator ++ () { return *(++current); };
		T& operator -- () { return *(--current); };
		bool operator != (const MyIterator& it) { return current != it.current; };
		bool operator == (const MyIterator& it) { return current == it.current; };
		T& operator * () { return *(current); };
	};
};

int main()
{
	// часть 1

	srand(time(0));
	std::list<double> n{ 333.333, 11.11 , 1, 123.321, -22.22 };
	addEndList(n);

	// часть 2

	Matrix matrix(5);
	matrix.setRand();
	matrix.print();
	std::cout << matrix.determinant() << std::endl;

	// часть 3

	MyArray<int> arr(5);
	int i;
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 2;
	arr[3] = 3;
	arr[4] = 4;

	for (auto itr = arr.begin(); itr != arr.end(); ++itr  ) {
		i = *itr;
	}

}

