#ifndef VECTOR_H
#define VECTOR_H
#include "iterators.hpp"
#include "utils.hpp"
#include <memory>
#include <algorithm>
#include <iostream>

namespace ft
{
	template < class T, typename Alloc = std::allocator<T> > 
	class vector
	{ 
        // alloc	-	allocator to use for all memory allocations of this container
        // count	-	the _size of the container
        // value	-	the value to initialize elements of the container with
        // first, last	-	the range to copy the elements from
        // other	-	another container to be used as source to initialize the elements of the container with
        // init	-	initializer list to initialize the elements of the container with
    public:
        typedef T                                           value_type;
        typedef Alloc                                       allocator_type;
        typedef std::size_t                                 size_type;
        typedef random_access_iterator<T>                   iterator;
        typedef const random_access_iterator<T>             const_iterator;
        typedef reverse_iterator<T>                         rev_iterator;
        typedef const reverse_iterator<T>                   const_rev_iterator;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef	typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;

    private:
        pointer arr;
        size_type _size;
        Alloc alloc;
       	size_type _capacity;

    public:
        //member functions
        // vector():arr(NULL),_size(0), alloc(Alloc()), _capacity(0) {;}
        
        explicit vector(const Alloc& alloc = Alloc()):arr(NULL),_size(0), alloc(alloc), _capacity(0) {;}
        

        template<class InputIt>
        vector(InputIt first, InputIt last, const allocator_type& alloc = Alloc(),
        typename enable_if<!is_integral<InputIt>::value, bool>::type is = 0)
        :arr(NULL),_size(is), alloc(alloc), _capacity(0)
        {
		    _size = ft::distance(first, last);
			_capacity = ft::distance(first, last);
			arr = this->alloc.allocate(_capacity);
			for (int i = 0; first != last; i++)
				this->alloc.construct(arr + i, *first++);
		}


        vector(size_type count, const T& value = T(), const allocator_type& alloc = Alloc())
        :arr(NULL),_size(count), alloc(alloc), _capacity(count) {
			arr = this->alloc.allocate(count);
            for (size_type i = 0; i < _size; i++) {
				this->alloc.construct(arr + i, value);
			}
        }

        vector( const vector& other )
        : _size(other._size), alloc(other.alloc), _capacity(other._capacity){ 
        	arr = this->alloc.allocate(_capacity);
            for (size_type i = 0; i < _size; i++)
				this->alloc.construct(arr + i, *(other.arr + i)); 
        }
        ~vector() {
            clear();
            if (_capacity)
                alloc.deallocate(arr, _capacity);
        }

        vector& operator=( const vector& other ) {
            clear();
            alloc.deallocate(arr, _capacity);
            alloc = other.alloc; _capacity = other._capacity;  _size = other._size;
            arr = alloc.allocate(_capacity);
            for (size_type i = 0; i < _size; i++)
				alloc.construct(arr + i, *(other.arr + i));
            return (*this);
        }
        
        void assign( size_type count, const T& value ) {clear(); resize(count, value);}
        
		template <class InputIt>
  		void assign (InputIt first, InputIt last,
		typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type is = 0) { // if is_integer<InputIt>::val == 0 , if_is::exist will not exist :)
            (void) is;
			clear();
			int sz = ft::distance(first, last);
			if (sz > (int)_capacity)
				reserve(sz);
			while (first != last)
				alloc.construct(arr + _size++, *first++);
		}


        allocator_type get_allocator() const    {
            return alloc;
        }

        //element access
        reference operator[] (size_type n) {return arr[n];}
        const_reference operator[] (size_type n) const {return arr[n];}
		reference at (size_type n) {
			if (n >= _size) throw std::out_of_range("vector");
			return arr[n];
		}
		const_reference at (size_type n) const {
			if (n >= _size) throw std::out_of_range("vector");
			return arr[n];
		}
		reference front() {return arr[0];}
		const_reference front() const {return arr[0];}
		reference back() {return arr[_size-1];}
		const_reference back() const {return arr[_size-1];}
        pointer data() {return arr;}
        const_pointer data() const {return arr;}
    
        //iterators
		iterator            begin() {return iterator(arr);}
		iterator            end() {return iterator(arr + _size);}
		const_iterator      begin() const {return const_iterator(arr);}
		const_iterator      end() const {return const_iterator(arr + _size);}
		rev_iterator        rbegin() {return rev_iterator((arr + _size));}
		rev_iterator        rend() {return rev_iterator(arr);}
		const_rev_iterator  rbegin() const {return const_rev_iterator((arr + _size));}
		const_rev_iterator  rend() const {return const_rev_iterator(arr);}

        //_capacity
        bool empty() {return !_size;}
        size_type size() const {return _size;}
        size_type max_size() {return alloc.max_size();}
		size_t capacity() const {return _capacity;}

        void reserve (size_type n) {
			if (n <= _capacity) return;
			pointer tmp = alloc.allocate(n);
			for (size_type i = 0; i < _size; i++) {
				alloc.construct(tmp + i, *(arr + i));
				alloc.destroy(arr + i);
			}
			alloc.deallocate(arr, _capacity);
			arr = tmp;
			_capacity = n;
		}

        //modifiers
        void clear() {
            for (size_type i = 0; i < _size; i++) 
				alloc.destroy(arr + i);
            _size = 0;
        }

        iterator insert(iterator pos, const T& value ) {
            size_type dist = (pos - begin());
            if (_size + 1 > _capacity) {
                _capacity *= 2;
                pointer ptr = alloc.allocate(_capacity);
                size_type i = -1;
                while (++i < size_type(pos - begin()))
                    alloc.construct(ptr + i , arr[i]);
                alloc.construct(ptr + i , value); 
                while (++i < _size + 1)
                    alloc.construct(ptr + i , arr[i - 1]);
                for (size_type i = 0; i < _size; i++) 
				    alloc.destroy(arr + i);
                alloc.deallocate(arr, _capacity);
                arr = ptr;
            }  else {
                iterator it = end() - 1;
                while (it >= pos) {
                    ft::swap<T>(*it, *(it + 1)); it--;}
                    *pos = value;     
            }
            ++_size;
            return (begin() + dist);
        }

        void    insert(iterator pos, size_type count, const T& value ) {
            iterator it = pos;
            size_type i = -1;
            if (_size + count > _capacity) {
                _capacity = ft::max(_capacity * 2, _capacity + count);
                pointer ptr = alloc.allocate(_capacity);
                while (++i < size_type(pos - begin()))
                    alloc.construct(ptr + i , arr[i]);
                while (i < size_type((pos - begin()) + count)) {
                    alloc.construct(ptr + i , value); i++;}
                while (i < _size + count) {
                    alloc.construct(ptr + i , arr[i - count]); i++;}
                for (size_type i = 0; i < _size; i++) 
				    alloc.destroy(arr + i);
                alloc.deallocate(arr, _capacity);
                arr = ptr;
            } else {
                while (it != end() + count) {
                    *(it + count)   = *it; it++;}
                it = pos;
                while (it != pos + count) {
                    *(it)           = value; it++;}
            }

            _size += count;
        }
        
		template <class InputIt>
  		void insert (iterator position, InputIt first, InputIt last,
			typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type is = 0) {
            (void) is;
			int dist = position - begin();
			while (first != last)
				insert(iterator(begin() + dist++), *first), ++first;
  		}
          
        iterator erase( iterator pos ) {
            int dist = pos - begin();
            for (iterator it = pos; it != end() - 1; it++)
                ft::swap(*(it), *(it + 1));
            _size--;
            return iterator(arr + dist);
        }

        iterator erase(iterator first, iterator last) {
            iterator it = first;
            int dist = first - begin();
            for (; first != last; first++)
                alloc.destroy(arr + (first - begin()));
            for (size_type i = 0;first + i != end(); i++)
                alloc.construct(arr + i + (it - begin()), *(first + i));
            _size -= last - it;
            return iterator(arr + dist);
        }

        void push_back( const T& value ) {
            insert(end(), value);
        }

        void pop_back() {
            *(end() - 1) = 0;
            --_size;
        }
        
        void resize(size_type count, T value = T()) {
            if (_capacity >= count) {
                if (_size < count) 
                    for (size_t i = _size; i < count; i++) 
                        arr[i] = value;
                _size = count;
            } else {
                _capacity = count;
                pointer ptr = alloc.allocate(_capacity);
                size_t i = 0;
                for (;i < _size && i < count; i++)
                    alloc.construct(ptr + i , arr[i]);
                for (;i < count; i++)
                    alloc.construct(ptr + i , value);
                clear();
                alloc.deallocate(arr, _capacity);
                arr = ptr;
            }
        }

        // void resize (size_type n, value_type val = value_type()) {
		// 	while (_size > n)
		// 		alloc.destroy(arr + --_size);
		// 	if (n > _capacity) {
		// 		int sz = ft::max(_capacity * 2, n);
		// 		pointer tmp = alloc.allocate(sz);
		// 		for (int i = 0; i < (int)_size; i++) {
		// 			alloc.construct(tmp + i, *(arr + i));
		// 			alloc.destroy(arr + i);
		// 		}
		// 		alloc.deallocate(arr,_capacity);
		// 		_capacity = sz;
		// 		arr = tmp;
		// 	}
		// 	while (_size < n)
		// 		alloc.construct(arr + _size++, val);
		// }
        void swap(vector &other) {
            vector tmp(other);
            other.arr = this->arr;
            other._size = this->_size;
            other._capacity = this->_capacity;
            other.alloc = this->alloc;

            this->arr = tmp.arr;
            this->_size = tmp._size;
            this->_capacity = tmp._capacity;
            this->alloc = tmp.alloc;
        }
            
        friend bool operator==( const vector<T,Alloc>& lhs,
                    const vector<T,Alloc>& rhs ) {
                if (lhs.size() != rhs.size())  return 0;    
                for (size_t i = 0; i < lhs.size(); i++) 
                    if (lhs[i] != rhs[i]) return 0;
                return 1;
        }
        friend bool operator!=( const vector<T,Alloc>& lhs,
                    const vector<T,Alloc>& rhs ) {
                        return !(lhs == rhs);
        }

        friend bool operator<( const vector<T,Alloc>& lhs,
                    const vector<T,Alloc>& rhs ) {
            return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }
        friend bool operator<=( const vector<T,Alloc>& lhs,
                    const vector<T,Alloc>& rhs ) {
            return (lhs == rhs || lhs < rhs);
        }
        friend bool operator>( const vector<T,Alloc>& lhs,
                    const vector<T,Alloc>& rhs ) {
            return lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
        }
        friend bool operator>=( const vector<T,Alloc>& lhs,
                    const vector<T,Alloc>& rhs ) {
            return (lhs == rhs || lhs > rhs);
        }
    };
    
    template< class T, class Alloc >
    void swap(vector<T,Alloc>& lhs, vector<T,Alloc>& rhs) {
        lhs.swap(rhs);
    }


}


#endif 