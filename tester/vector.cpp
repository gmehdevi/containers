#include "../vector.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#ifdef FT
    #define ns ft
#else
    #define ns std
#endif

using namespace ns;

template <typename T>
std::ostream &operator<<(std::ostream &os, ns::vector<T> &v) {
    os << "|";
    for (size_t i = 0; i < v.size(); i++)
        os << v[i] << "|";
    return os;
}

int main(int ac, char **av) {
    srand(atoi(av[1]));
    std::vector<int> init(1000);
    for (size_t i = 0; i < init.size()); i++)
        init.push_back(rand());
    // vector::vector
    {
        // explicit vector(const Alloc& alloc = Alloc()):arr(NULL),_size(0), alloc(alloc), _capacity(0) {;}
        vector<int> v_def;
        // vector(InputIt first, InputIt last, const allocator_type& alloc = Alloc(),
        vector<int> v_it(init.begin(), init.end());
        // vector(size_type count, const T& value = T(), const allocator_type& alloc = Alloc())
        vector<int> v_count(init.size(),*init.begin());
        // vector( const vector& other )
        vector<int> v_other(v_it);
        std::cout << v_def << '\n' << v_it << '\n' << v_count << '\n' << v_other << '\n';
    }
    // vector::~vector
    {
        vector<int> v;
         
    }
    // vector::operator=
    {
        vector<int> v;
         
    }
    // vector::assign
    {
        vector<int> v;
         
    }
    // vector::get_allocator
    {
        vector<int> v;
         
    }
    // Element access
    {
        vector<int> v;
         
    }
    // vector::at
    {
        vector<int> v;
         
    }
    // vector::operator[]
    {
        vector<int> v;
         
    }
    // vector::front
    {
        vector<int> v;
         
    }
    // vector::back
    {
        vector<int> v;
         
    }
    // vector::data
    {
        vector<int> v;
         
    }
    // Iterators
    {
        vector<int> v;
         
    }
    // vector::begin
    {
        vector<int> v;
         
    }
    // vector::end
    {
        vector<int> v;
         
    }
    // vector::rbegin
    {
        vector<int> v;
         
    }
    // vector::rend
    {
        vector<int> v;
         
    }
    // Capacity
    {
        vector<int> v;
         
    }
    // vector::empty
    {
        vector<int> v;
         
    }
    // vector::size
    {
        vector<int> v;
         
    }
    // vector::max_size
    {
        vector<int> v;
         
    }
    // vector::reserve
    {
        vector<int> v;
         
    }
    // vector::capacity
    {
        vector<int> v;
         
    }
    // Modifiers
    {
        vector<int> v;
         
    }
    // vector::clear
    {
        vector<int> v;
         
    }
    // vector::insert
    {
        vector<int> v;
         
    }
    // vector::erase
    {
        vector<int> v;
         
    }
    // vector::push_back
    {
        vector<int> v;
         
    }
    // vector::pop_back
    {
        vector<int> v;
         
    }
    // vector::resize
    {
        vector<int> v;
         
    }
    // vector::swap
    {
        vector<int> v;
         
    }
    // Non-member functions
    {
        vector<int> v;
         
    }
    // ns::swap
    {
        vector<int> v;
         
    }
    // operator==
    {
        vector<int> v;
         
    }
    // operator!=
    {
        vector<int> v;
         
    }
    // operator<
    {
        vector<int> v;
         
    }
    // operator>
    {
        vector<int> v;
         
    }
    // operator<=
    {
        vector<int> v;
         
    }
    // operator>=
    {
        vector<int> mine_equal(init.begin(), init.begin() + 100);
        vector<int> mine_greater(init.begin(), init.begin() + 100);
        vector<int> mine_lesser(init.begin(), init.begin() + 100);
        for (auto &e : mine_greater)
            e += 1;
        for (auto &e : mine_lesser)
            e -= 1;

        ns::vector<int> stl_equal(init.begin(), init.begin() +100); 
        ns::vector<int> stl_greater(init.begin(), init.begin() +100); 
        ns::vector<int> stl_lesser(init.begin(), init.begin() +100); 
        for (auto &e : stl_greater)
            e += 1;
        for (auto &e : stl_lesser)
            e -= 1;
        
    }
}