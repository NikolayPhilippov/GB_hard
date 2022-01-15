#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <clocale>
#include <array>
#include <string_view>
#include "Timer.h"

using namespace std;

void Sort(vector<int> numbers) {
    Timer timer("STL sort");
    sort(numbers.begin(), numbers.end());
    timer.print();
}

void BubbleSort(vector<int> numbers) {
    size_t size = numbers.size();
    int temp;
    Timer timer("Bubble sort");
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
    timer.print();
}

void InsertionSort(vector<int> numbers) {
    size_t size = numbers.size();
    int temp, item;
    Timer timer("Insertion sort");
    for (size_t counter = 1; counter < size; counter++) {
        temp = numbers[counter];
        item = counter - 1;
        while (item >= 0 && numbers[item] > temp) {
            numbers[item + 1] = numbers[item];
            numbers[item] = temp;
            item--;
        }
    }
    timer.print();
}

template <typename Type>
void mySwap(Type*& ptr1, Type*& ptr2) {
    Type *ptrTemp(ptr2);
    ptr2 = move(ptr1);
    ptr1 = move(ptrTemp);
}

template <typename T>
void SortPointers(std::vector<T>& vec) {

    sort(vec.begin(), vec.end(), [](const auto& it1, const auto& it2) { return *it1 < *it2; });

    for (const auto i : vec) {
        std::cout << "Указатель " << i << " \t значение " << *i << std::endl;
    }

/*  auto size = _vec.size();
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (*_vec[j] > *_vec[j + 1]) {
                mySwap(_vec[j], _vec[j + 1]);
            }
        }
    } */
}


int find_For(const std::string& stringWnP, const std::string& vowels) {

    Timer timer("find_For");
    size_t result = 0;
    size_t resultOnChar = 0;
    size_t itString = stringWnP.size();

    for (auto it_str : vowels) {
        auto nextPos = stringWnP.begin();
        auto tempPos = stringWnP.begin();
        while (true) {
            tempPos = std::find(nextPos, stringWnP.end(), it_str);
            if (tempPos == stringWnP.end()) {
                result += resultOnChar;
                resultOnChar = 0;
                break;
            }
            resultOnChar++;
            nextPos = tempPos + 1;
        }
    }
    timer.print();
    std::cout << "Общее количество соглассных букв : " << result << std::endl;
    return result;
};


auto count_if_find(const std::string_view strWnP, const std::string & vowels) {
    
    Timer timer("count_if_find");
    
    auto result{ std::count_if(strWnP.begin(), strWnP.end(),[strWnP, vowels](auto ch)
                    { return (std::find(vowels.begin(), vowels.end(), ch) != vowels.end()); })};
        
    timer.print();
    std::cout << "найдено гласных букв : " << result << std::endl;
    return result;
}

size_t count_if_for(std::string_view strWnP, const std::string& vowels) {

    Timer timer("count_if_for");
    size_t result = 0;

    for (const auto& it : vowels)
    {
        auto result_it{ std::count_if(strWnP.begin(), strWnP.end(),[it](auto ch) { return it == ch; })};
        result += result_it;
    }

    timer.print();
    std::cout << "найдено гласных букв : " << result << std::endl;
    return result;
}

size_t twoFor1(std::string& stringWnP, const std::string& vowels) {

    Timer timer("two_for_1");

    size_t result = 0;
    int size_str = stringWnP.size();

    for (const auto& it : vowels) {
        int tempPos = 0;
        for (int nextPos = 0; nextPos < size_str; ) {
            tempPos = stringWnP.find(it, nextPos);
            if (tempPos == -1) {
                break;
            }
            ++result;
            nextPos = tempPos + 1;
        }
    }
    timer.print();
    std::cout << "найдено гласных букв : " << result << std::endl;
    return result;

}

size_t twoFor2(std::string& stringWnP, const std::string& vowels) {

    Timer timer("two_for_2");

    size_t result = 0;
    for (auto it_char : vowels) {
        for (auto it_str : stringWnP) {
            if (it_char == it_str) {
                ++result;
            }
        }
    }
    timer.print();
    std::cout << "найдено гласных букв : " << result << std::endl;
    return result;
}


int main() {

    setlocale(LC_ALL, "Russian");

    //size_t size = 10000;
    //vector<int> numbers;
    //for (size_t i = 0; i < size; i++) {
    //    numbers.push_back(rand());
    //}

    //Sort(numbers);
    //InsertionSort(numbers);
    //BubbleSort(numbers);

    // part1

    int* ptrMaster = new int(100);
    int* ptrSlave = new int(5);

    std::cout << *ptrMaster <<  " адресс указателя ptrMaster " << ptrMaster << "\t " << *ptrSlave << " адресс указателя ptrSlave  " << ptrSlave << std::endl;

    mySwap(ptrMaster, ptrSlave);

    std::cout << *ptrSlave << " адресс указателя ptrSlave  " << ptrSlave << "\t " << *ptrMaster << " адресс указателя ptrMaster " << ptrMaster << std::endl;

    //part2

    const size_t SIZE_VEC = 10;
    std::vector<int*> vecToPtr;
    std::vector<int*>::iterator iter;

    for (size_t i = 0; i < SIZE_VEC; ++i) {
        vecToPtr.push_back(new int(rand()));
    }

    SortPointers(vecToPtr);

    for (auto it : vecToPtr) {
        delete it;
    }
    vecToPtr.clear();

    //part3



    std::ifstream fileWnP("War_n_Peace.txt");
    if (!fileWnP)
    {
        std::cout << "Ошибка открытия файла" << std::endl;
        return 404;
    }

    fileWnP.seekg(0, std::ios::end);
    size_t stringSize = fileWnP.tellg();
    fileWnP.seekg(0);
    std::string stringWnP(stringSize, ' ');
    fileWnP.read(&stringWnP[0], stringSize);    
    
    const std::string vowels = { "АИЕЁОУЭЮЯаиеёоуыэюяAEIOUaeiou" };

    std::string_view string_view_WnP = stringWnP;

    find_For(stringWnP, vowels);

    count_if_find(string_view_WnP, vowels);

    count_if_for(string_view_WnP, vowels);
    
    twoFor1(stringWnP, vowels);

    twoFor2(stringWnP, vowels);

    fileWnP.close();
}
