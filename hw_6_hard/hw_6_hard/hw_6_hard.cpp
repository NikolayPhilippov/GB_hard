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
std::mutex inHomeMut;
std::mutex outHomeMut;

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

void InHouse(std::vector<std::pair<size_t, char>>& in)
{
    std::lock_guard lg(mut);
    size_t first = (rand() % 99 + 1); // cost 
    char second = (rand() % 25 + 41); // A-Z
    in.push_back({ first, second });
    std::this_thread::sleep_for(std::chrono::seconds(1));
};


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

    std::vector<std::pair<size_t, char>> thing;
   
}
