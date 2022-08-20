#ifndef TREE_ITERATORS_H
#define TREE_ITERATORS_H

#include "RB_Tree.hpp"
#include "utils.hpp"
#include "iterators.hpp"

namespace ft {

	template<typename T, typename Compare, typename Alloc, typename Node>
    class bidirectional_iterator : public iterator<ft::bidirectional_iterator_tag, T>
    {

    public:
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type            value_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;
        typedef T*                                                                              pointer;
        typedef T&                                                                              reference;
	
    private:
        typedef  Node *                                                              		nodePtr;
		nodePtr _ptr;
		nodePtr _last;
		Compare _comp;  
	public:


	/*------------------Constructor------------------*/

		bidirectional_iterator(const nodePtr ptr=NULL, const nodePtr last=NULL)
		: _ptr(ptr), _last(last), _comp(Compare()) {}

		bidirectional_iterator(const bidirectional_iterator &cpy)
		: _ptr(cpy._ptr), _last(cpy._last), _comp(cpy._comp) {}

		bidirectional_iterator &operator=(const bidirectional_iterator &cpy) {
			_ptr = cpy._ptr;
			_last = cpy._last;
			_comp = cpy._comp;
			return *this;
		}

		~bidirectional_iterator() {}

		
	/*------------------Access------------------*/

		reference operator*() const {return  _ptr->val;}
		pointer operator->() const {return &(**this);}


	/*------------------Increment------------------*/

		bidirectional_iterator &operator++() {
			if (_ptr->right) {
				_ptr = _ptr->right;
				while (_ptr->left) _ptr = _ptr->left;
			} else {
				value_type cur_val = _ptr->val;	
				while (!_comp(cur_val, _ptr->val))
					_ptr = _ptr->parent;
			}
			return *this;
		}

		bidirectional_iterator operator++(int) {
            bidirectional_iterator out(*this);
            ++(*this);
            return out;
		}

		bidirectional_iterator &operator--() {
			if (_ptr == _last)
				_ptr = _ptr->parent;
			else if (_ptr->left) {
				_ptr = _ptr->left;
				while (_ptr->right) _ptr = _ptr->right;
			} else {
				value_type cur_val =  _ptr->val;	
				while (!_comp( _ptr->val, cur_val))
					_ptr = _ptr->parent;
			}
			return *this;
		}
		
		bidirectional_iterator operator--(int) {
            bidirectional_iterator out(*this);
            --(*this);
            return out;
		}


	/*------------------Comparaison------------------*/

		friend bool operator==(const bidirectional_iterator &x, const bidirectional_iterator &y) {return (x._ptr == y._ptr);}
		friend bool operator!=(const bidirectional_iterator &x, const bidirectional_iterator &y) {return (x._ptr != y._ptr);}


	/*------------------Conversion------------------*/

		  operator bidirectional_iterator<T, Compare, Alloc, Node> () {
			return bidirectional_iterator<T, Compare, Alloc, Node> (_ptr, _last);
		}
	};
}
#endif