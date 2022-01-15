#include <iostream>
#include <vector>
#include <algorithm>

const size_t SIZE = 100;

template <typename T>
std::vector<T>& insert_sorted(std::vector<T>& v, T val)
{
    std::sort(v.begin(), v.end());
    
    if ( v.back() < val) {
        v.push_back(val);
    }
    else {
        typename std::vector<T>::iterator it;
        it = std::lower_bound(v.begin(), v.end(), val);
        v.insert(it, val);
    }
    return v;
};

std::vector<double>& setRand(std::vector<double>& v)
{
    for (auto it = v.begin(); it != v.end(); ++it) {
        *it = ( rand() % 100 ) * 0.1;
    }
    return v;
};


void no_double(const std::vector<double>& v_double, std::vector<int>& v_int)
{
    for (auto it : v_double) {
        v_int.push_back( static_cast<int>(it) );
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    
    // part1

    std::vector<int> vec{ 10, 20, 30, 40, 50, 60, 70, 80, 90 };
    int newValue;
    std::cout << "Введите целое число : ";
    std::cin >> newValue;
    insert_sorted(vec, newValue);
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl;

    // part2
    
 
    std::vector<double> vector(SIZE);
    vec.clear();
    vec.reserve(SIZE);
    setRand(vector);
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<double>{std::cout, " "});
    std::cout << "---------------------" << std::endl;
    no_double(vector, vec);
    std::cout << std::endl;
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl;
}

