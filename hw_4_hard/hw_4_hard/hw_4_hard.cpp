#include <iostream>
#include <vector>
#include <algorithm>

const size_t SIZE = 100;

template <typename T>
void insert_sorted(std::vector<T>& v, const T val)
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
};

void setRandDoubleVector(std::vector<double>& v)
{
    for (auto it = v.begin(); it != v.end(); ++it) {
        *it = ( rand() % 1000 ) * 0.1;
    }
};


void no_double(std::vector<double>& v_double, std::vector<int>& v_int)
{
   /* for (auto it : v_double) {
        v_int.push_back( static_cast<int>(it) );
    }*/
    std::transform(v_double.begin(), v_double.end(), v_int.begin(), [](double& it) { return static_cast<int>(it); });
};

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    
    // part1

    std::vector<int> vec_int{ 10, 20, 30, 40, 50, 60, 70, 80, 90 };
    int newValue;
    std::cout << "Введите целое число : ";
    std::cin >> newValue;
    insert_sorted(vec_int, newValue);
    std::copy(vec_int.begin(), vec_int.end(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl << "---------------------" << std::endl;

    // part2
 
    std::vector<double> vec_double(SIZE);
    std::vector<double> delta(SIZE);
    vec_int.clear();
    vec_int.resize(SIZE);
    double temp;
    setRandDoubleVector(vec_double);
    std::copy(vec_double.begin(), vec_double.end(), std::ostream_iterator<double>{std::cout, " "});
    std::cout << std::endl << "---------------------" << std::endl;
    no_double(vec_double, vec_int);
    std::copy(vec_int.begin(), vec_int.end(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl << "---------------------" << std::endl;
    
    //здесь что-то не срабатывает (( 0 0 0 0 0 одни

    std::transform(vec_double.begin(), vec_double.end(), vec_int.begin(), delta.begin(),
                    [](double& it1, int& it2)->double { return static_cast<double>((it1 - it2) * (it1 - it2)); }); 
    std::copy(delta.begin(), delta.end(), std::ostream_iterator<int>{std::cout, " "});
}

