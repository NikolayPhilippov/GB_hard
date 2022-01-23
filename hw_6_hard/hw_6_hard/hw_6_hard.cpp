#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <string>
#include <future>
#include <iomanip>
#include <chrono>
#include <thread>
#include <mutex>
#include <utility>

std::mutex mut;

void pcout_class(const std::string str)
{
    std::lock_guard lg(mut);
    std::cout << "mutex lock_guard = start, thread ID = " << std::this_thread::get_id() << std::endl;
    std::cout << str << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "mutex lock_guard = end, thread ID =  " << std::this_thread::get_id() <<
                    std::endl << "------------========================------------" << std::endl;
};

void pcout_std(const std::string str)
{
    mut.lock();
    std::cout << "mutex lock method = start, thread ID = " << std::this_thread::get_id() << std::endl;
    std::cout << str << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "mutex lock method = end, thread ID =  " << std::this_thread::get_id() <<
                    std::endl << "------------========================------------" << std::endl;
    mut.unlock();
};
 
size_t FindSimpleNumber(size_t val)
{
    if (val <= 2) {
        std::cout << "Числа 1 и 2 простые" << std::endl;
        if (val == 1) {
            return 1;
        }
        else {
            return 2;
        }
    }

    if (val % 2 == 0) {
        --val;
    }
   
    bool flag = true; // условие прочтого числа
    size_t temp; 
    size_t val_sqrt=std::sqrt(val); // кв корень

    std::cout << "Calculate : ";

    do
    {
        temp = val;
        flag = true;

        for (size_t i = 3; i < val_sqrt; i += 2) {
            if ((val) % i == 0) {
                val -= 2;
                flag = false;
                break;
            }
            std::cout << "*";
        }
    } while (!((temp == val) && flag));

    std::cout << " end!" << std::endl;
    return temp;
};

void AddItemFromStore(std::vector<std::pair<size_t, char>>& store)
{
    while (!store.empty())
    {
        srand(time(0));
        size_t cost_element = (rand() % 99 + 1); // cost
        char name_element = (rand() % 25 + 65); // A-Z 
        {
            std::lock_guard lg(mut);
            store.push_back({ cost_element, name_element });
            std::cout << "+++ User +++ Total object = " << store.size() << ". Аdd in house : cost = " <<
                cost_element << ", short name : " << name_element << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
};

void DeleteItemFromStore(std::vector<std::pair<size_t, char>>& store)
{
    while (!store.empty())
    {
        auto dell_element = std::max_element(store.begin(), store.end());
        std::pair<size_t, char> temp = *dell_element;
        {
            std::lock_guard lg(mut);
            std::cout << "!! Thief !! Total object = " << store.size() << ". Delete object : cost = " <<
                temp.first << ", short name : " << temp.second << std::endl;
            store.erase(dell_element);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    // part1
    std::thread th_class_1(pcout_class, "big data!!! th_class_1");
    std::thread th_class_2(pcout_class, "big data!!! th_class_2");
    std::thread th_class_3(pcout_class, "big data!!! th_class_3");
    th_class_1.join();
    th_class_2.join();
    th_class_3.join();

    std::thread th_std_1(pcout_std, "big data!!! pcout_std_1");
    std::thread th_std_2(pcout_std, "big data!!! pcout_std_2");
    std::thread th_std_3(pcout_std, "big data!!! pcout_std_3");
    th_std_1.join();
    th_std_2.join();
    th_std_3.join();

    // part2
    size_t value = 150000558;
    
    mut.lock();
    std::cout << "begin thread ID = " << std::this_thread::get_id() << std::endl;
    std::cout << "Просое число из числа " << value << " = " << FindSimpleNumber(value) << std::endl;
    std::cout << "end thread ID = " << std::this_thread::get_id() << std::endl;
    mut.unlock();

    //part3

    std::vector<std::pair<size_t, char>> store_house;
    store_house.reserve(15);
    store_house.push_back({ 11,'A'});
    store_house.push_back({ 23,'B' });
    store_house.push_back({ 63,'C' });
    store_house.push_back({ 74,'D' });
    store_house.push_back({ 25,'E' });
    store_house.push_back({ 46,'F' });
    store_house.push_back({ 77,'A' });
    store_house.push_back({ 45,'B' });
    store_house.push_back({ 53,'C' });
    store_house.push_back({ 50,'D' });

    std::thread inHouse(AddItemFromStore, ref(store_house));
    std::thread outHouse(DeleteItemFromStore, ref(store_house));
    inHouse.join();
    outHouse.join();


}
