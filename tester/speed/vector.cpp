#include "../../vector.hpp"
#include <memory>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <cstddef>
#include <limits>
#include <climits>
#include <stdio.h>
#include <time.h> 
#include <iostream>
#define count 10000// dont go beyond 10000 takes too long
#ifdef FT
    #define ns ft
#else
    #define ns std
#endif
using namespace ns;


int main(int ac, char **av) {
    (void)ac;
    clock_t begin = clock();
    srand(atoi(av[1]));
    // clock_t end = clock();

    //std::cout << (double)(end - begin) / CLOCKS_PER_SEC << std::endl;
    
    
{    
    //  begin = clock();
    // clock_t b = clock();
    
    ns::vector<int> v(count, 1);
    //  end = clock();

    //std::cout << "count construct :" << (double)(end - begin) / CLOCKS_PER_SEC << std::endl;
    //  begin = clock();

	for (int i = 0; i < count; i++)
		v.insert(v.begin() + rand() % v.size(), 42);
    //  end = clock();

    //std::cout << "insert pos :" << (double)(end - begin) / CLOCKS_PER_SEC << std::endl;
    //  begin = clock();

    v.insert(v.begin() +  rand() % v.size(), count, 42);
    // end = clock();

    //std::cout << "insert pos n:" << (double)(end - begin) / CLOCKS_PER_SEC << std::endl;
    //  begin = clock();

    while (!v.empty()) v.pop_back();
    //  end = clock();

    //std::cout << "pop back :" << (double)(end - begin) / CLOCKS_PER_SEC << std::endl;
    //  begin = clock();

    for (int i = 0; i < count; i++) v.push_back(rand());
    //  end = clock();

    //std::cout << "push_back :" << (double)(end - begin) / CLOCKS_PER_SEC << std::endl;
    //  begin = clock();

    v.assign(count, 42);
    //  end = clock();

    //std::cout << "assign :" << (double)(end - begin) / CLOCKS_PER_SEC << std::endl;
    //  begin = clock();

    v.resize(v.size() * 10);
    //  end = clock();

    //std::cout << "resize :" << (double)(end - begin) / CLOCKS_PER_SEC << std::endl;

    clock_t end = clock();
    std::cout << (double)(end - begin) / CLOCKS_PER_SEC << std::endl;
    
    }
    return 0;
}