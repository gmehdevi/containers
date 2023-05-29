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
        typedef  T *                           					pointer;
        typedef  T &                             				reference;
    private:
		typedef Node *											nodePtr;
	public:
		nodePtr _ptr;
		nodePtr _end;
		Compare _comp;  

		bidirectional_iterator(const nodePtr ptr = NULL, const nodePtr tend = NULL)
		: _ptr(ptr), _end(tend), _comp(Compare()) {}

		bidirectional_iterator(const bidirectional_iterator &cpy)
		: _ptr(cpy._ptr), _end(cpy._end), _comp(cpy._comp) {}

		bidirectional_iterator &operator=(const bidirectional_iterator &cpy) {
			_ptr = cpy._ptr;
			_end = cpy._end;
			_comp = cpy._comp;
			return *this;
		}

		~bidirectional_iterator() {}

		reference operator*() const {return  _ptr->data;}
		pointer operator->() const {return &(**this);}

		bidirectional_iterator &operator++() {
			if (_ptr && _ptr->right && _ptr->right != _end) {
				_ptr = _ptr->right;
				while (_ptr && _ptr->left && _ptr->left != _end) 
					_ptr = _ptr->left;
			} else {
				value_type cur_val = _ptr->data;
				while (_ptr && _ptr != _end && !_comp(cur_val, _ptr->data))
					_ptr = _ptr->parent;
			} 
			if (!_ptr) _ptr = _end;
			return *this;
		}

		bidirectional_iterator operator++(int) {
            bidirectional_iterator out(*this);
            ++(*this);
            return out;
		}

		bidirectional_iterator &operator--() {
			if (_ptr == _end)
				_ptr = _end->parent;
			else if (_ptr->left && _ptr->left != _end) {
				_ptr = _ptr->left;
				while (_ptr->right && _ptr->right != _end) 
					_ptr = _ptr->right;
			} else {
				value_type cur_val =  _ptr->data;	
				while (_ptr != _end && !_comp( _ptr->data, cur_val))
					_ptr = _ptr->parent;
			}
			return *this;
		}
		
		bidirectional_iterator operator--(int) {
            bidirectional_iterator out(*this);
            --(*this);
            return out;
		}

		friend bool operator==(const bidirectional_iterator &x, const bidirectional_iterator &y) {return (x._ptr == y._ptr);}
		friend bool operator!=(const bidirectional_iterator &x, const bidirectional_iterator &y) {return (x._ptr != y._ptr);}


		operator bidirectional_iterator<const T, Compare, Alloc, Node> () const {
			bidirectional_iterator<const T, Compare, Alloc, Node> out(_ptr, _end);
			return out;
		}
	};

}
#endif
