#include <iostream>
#include <cstddef>
#include <utility>
#ifdef FT
# define ns ft
#include "../map.hpp"
#include "../vector.hpp"
#include "../iterators.hpp"
#else
# define ns std
#include <map>
#include <vector>
#endif


using namespace ns;
int main()
{
	{
    map<int, int> v;
	for (int i = 0; i < 10; i++)
		v.insert(pair<int, int>(i * 4, i));
	
	// for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
	map<int, int>::const_iterator it = v.begin();
	map<int, int>::const_iterator ite = v.end();
	while (it != ite){
		std::cout << (*(it)).first << std::endl;
		it++;
	}

    // std::cout << std::endl;
    }





    {

        vector<int> v;
        for (int i = 0; i < 10; i++)
            v.push_back(i * 4);
        
        // for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        vector<int>::const_iterator it = v.begin();
        vector<int>::const_iterator ite = v.end();
        while (it != ite){
            std::cout << *it << std::endl;
            it++;
        }

        // test comparison of 2 iterators (const & non-const)
        vector<char> a;
        for (int i = 0 ; i < 6; i ++)
            a.push_back(i + 'a');
        vector<char>::iterator it1 = a.begin() + 1;
        vector<char>::const_iterator cit = a.begin() + 2;
        std::cout << (it1 != cit) << std::endl;
        std::cout << (it1 > cit) << std::endl;



    }

    {
	map<int, int> v;
	for (int i = 0; i < 10; i++)
		v.insert(pair<int, int>(i * 4, i));
	
	// for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
	map<int, int>::const_reverse_iterator it = v.rbegin();
	map<int, int>::const_reverse_iterator ite = v.rend();
	while (it != ite){
		std::cout << (*(it)).first << std::endl;
		it++;
	}
    // std::cout << std::endl;

    {
        	vector<int> v;
	for (int i = 0; i < 10; i++)
		v.push_back(i * 4);

	std::string s = "0101010001111010101010101001010111101";

	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (s[i] == '1')
			v.push_back(i);
		if (s[i] == '0')
			v.pop_back();
	}
	
	// for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
	vector<int>::const_reverse_iterator it = v.rbegin();
	vector<int>::const_reverse_iterator ite = v.rend();
	while (it != ite){
		std::cout << (*(it)) << std::endl;
		it++;
	}
    }



}










}