#pragma once

#include <iostream>
#include <cmath>
#include <map>
#include <utility>
#include <fstream>
#include <string>
#include <set>
#include <list>
#include <vector>
#include "part2.pb.h"

class IRepository {
	virtual void Open() = 0; // бинарная десериализация в файл
	virtual void Save() = 0; // бинарная сериализация в файл
};

class IMethods {
	virtual double GetAverageScore(const FullName& name) = 0;
	virtual std::string GetAllInfo(const FullName& name) = 0;
	virtual std::string GetAllInfo() = 0;
};

class STGroups : public IRepository, public IMethods
{
public:

    STGroups() = default;
    STGroups(const std::string& fname) : fileName(fname) {};

    virtual void Open() override;
    virtual void Save() override;

    virtual double GetAverageScore(const FullName& name) override;
    virtual std::string GetAllInfo(const FullName& name) override;
    virtual std::string GetAllInfo() override;

    bool operator == (const FullName& p1, const FullName& p2);


private:
    std::string fileName{ "StudentsGroups.bin" };
    StudentsGroup stGrups;
};

void STGroups::Open()
{
    std::ifstream file{ fileName, std::ios_base::binary };

    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла" << std::endl;
        return;
    }
    else {
        std::cout << "Файл открыт на чтение" << std::endl;
    }
};

void STGroups::Save()
{
    std::ofstream file{ fileName, std::ios_base::binary };

    if (!file.is_open()) {
        std::cout << "Ошибка сохранения файла" << std::endl;
        return;
    }
    else {
        file.close();
        std::cout << "Файл закрыт " << std::endl;
    }
};

bool STGroups::operator == (const FullName& p1, const FullName& p2)
{
    return std::tie(p1.name(), p1.surname(), p1.patronymic()) ==
        std::tie(p2.name(), p2.surname(), p2.patronymic());
}

double STGroups::GetAverageScore(const FullName& name)
{
    for ( ; ; ) {
    {   
        // проверка по итератору и вывод информации

        if (name == w ) {

        }
            
};

int main()
{
    setlocale(LC_ALL, "rus");

}
