#include "vector.hpp"
#include <bits/stdc++.h>

using namespace ft;

template <typename T>
std::ostream &operator<<(std::ostream &os, vector<T> &v) {
    os << "mine : ";
    for (size_t i = 0; i < v.size(); i++)
        os << v[i] << "|";
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> &v) {
    os << " stl : ";
    for (size_t i = 0; i < v.size(); i++)
        os << v[i] << "|";
    return os;
}

int main() {

    vector<int> a;
    vector<int> b(5, 7);
    std::vector<int> b_stl(5, 7);
    std::vector<int> test_stl(l.begin(), l.end());
    
    //vector(InputIt first, InputIt last, const Alloc& alloc = Alloc())
    vector<int> c(test_stl.begin() + 1, test_stl.end() - 1);
    std::vector<int> c_stl(test_stl.begin() + 1, test_stl.end() - 1);


	// iterator erase(iterator pos);
	// for (size_t i = 0; i < 6; i++)
	// 	c.erase(c.begin() + 1);
	// for (size_t i = 0; i < 6; i++)
	// 	c_stl.erase(c_stl.begin() + 1);
	
	// std::cout << c << std::endl;
	// std::cout << c_stl << std::endl;
    
	// iterator erase(iterator first, iterator last) {
	// c.erase(c.begin() + 1, c.end() - 3);
	// c_stl.erase(c_stl.begin() + 1, c_stl.end() - 3);
	
	// std::cout << c << std::endl;
	// std::cout << c_stl << std::endl;
	
	
	// iterator insert(iterator pos, const T& value ) {
    // std::cout << c << '\n';
    // std::cout << c_stl << '\n';
    // std::cout << b << '\n';
    // b.insert(b.begin(), 1);
    // b.insert(b.begin(), 2);
    // b.insert(b.begin(), 3);
    // std::cout << b << '\n';
    // b.insert(b.begin(), 4);
    // b.insert(b.begin(), 5);
    // b.insert(b.begin(), 6);
    // std::cout << b << '\n';
    // std::cout << b_stl << '\n';
    // b_stl.insert(b_stl.begin(), 1);
    // b_stl.insert(b_stl.begin(), 2);
    // b_stl.insert(b_stl.begin(), 3);
    // std::cout << b_stl << '\n';
    // b_stl.insert(b_stl.begin(), 4);
    // b_stl.insert(b_stl.begin(), 5);
    // b_stl.insert(b_stl.begin(), 6);



	// //testing insert ret
    // std::cout << b << '\n';
    // std::cout << "ret it elem : " << *(b.insert(b.begin() + b.size()/2, 1))  << std::endl;

    // std::cout << b_stl << '\n';
    // std::cout << "stl ret it elem : " << *(b_stl.insert(b_stl.begin() + b_stl.size()/2, 1)) << std::endl;

    // std::cout << b << '\n';
    // std::cout << "ret it elem : " << *(b.insert(b.begin()+ b.size()/2, 6)) << std::endl;
    
    // std::cout << b_stl << '\n';
    // std::cout << "stl ret it elem : " << *(b_stl.insert(b_stl.begin() + b_stl.size()/2, 6)) << std::endl;

    // std::cout << b << '\n';
    // std::cout << b_stl << '\n';




    // std::cout << b_stl << '\n';
    // std::cout << "void    insert(iterator pos, size_type count, const T& value)" << std::endl;
    // std::cout << b << '\n';
    // std::cout << b_stl << '\n';
    // b.insert(b.begin() + 1, 10, 1);
    // b_stl.insert(b_stl.begin() + 1, 10, 1);
    // std::cout << b << '\n';
    // std::cout << b_stl << '\n';
    // b.insert(b.begin() + 2, 10, 2);
    // b_stl.insert(b_stl.begin() + 2, 10, 2);
    // std::cout << b << '\n';
    // std::cout << b_stl << '\n';


    // void insert( iterator pos, InputIt first, InputIt last );


}



/* 42 main */

#include <iostream>
#include <string>
#include <deque>
#if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}