#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <set>
#include <map>
#include <string>

template<typename T>
void print(T it_begin, T it_end)
{
    std::set<typename T::value_type> unique_set(it_begin, it_end);
    std::for_each(unique_set.begin(), unique_set.end(), [](const auto& it) { std::cout << it << " \t "; });
    std::cout << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    // part1

    std::vector<std::string> vec_str{ "1-one", "2-two", "1-one", "3-three", "4-four", "3-three", "5-five", "5-five" };
    print(vec_str.begin(), vec_str.end());

    std::list<std::string> list_str{ "1-one", "2-two", "1-one", "3-three", "4-four", "3-three", "5-five", "5-five" };
    print(list_str.begin(), list_str.end());

    std::vector<int> vec_int{ 1, 2, 1, 3, 4, 3, 5, 5 };
    print(vec_int.begin(), vec_int.end());

    std::list<int> list_int{ 1, 2, 1, 3, 4, 3, 5, 5 };
    print(list_int.begin(), list_int.end());

    // part2

    std::multimap<size_t, std::string, std::greater<size_t>> lines;

    while (true) {
        if (std::string line; !std::getline(std::cin, line)) {
            throw "Критическая ошибка ввода!!!";
        }
        else if (line.empty()) {
            break;
        }
        else
            lines.insert(std::make_pair(line.size(), line));
    }

    std::for_each(lines.begin(), lines.end(), [](const auto& v) { std::cout << v.first << ": " << v.second << "\n"; });
};

};

