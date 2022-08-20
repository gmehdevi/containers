#ifndef MAP_H
#define MAP_H
#include "utils.hpp"
#include "pair.hpp"
#include "RB_Tree.hpp"
#include "tree_iterators.hpp"
#include "iterators.hpp"

namespace ft
{
template
    <
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T>>
    > 
    class map {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const Key, T> value_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type ;
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointerAllocator::const_pointer const_pointer	;
        typedef bidirectional_iterator<value_type, Compare, allocator_type, RB_Node<value_type>>        iterator;
        typedef bidirectional_iterator<const value_type, Compare, allocator_type, RB_Node<value_type>>  const_iterator;
        typedef ft::reverse_iterator<iterator>                                                          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                                                    const_reverse_iterator;

        class value_compare {
			friend class map;
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type &x, const value_type &y) const {return comp(x.first, y.first);}
			value_compare() : comp(Compare()) {}
		protected:
			Compare comp;
		};

    private:
        typedef RB_Tree<T, Compare, Allocator>  Tree;
        Tree                             *tree;
        allocator_type                   alloc;
        key_compare                      k_comp;
        value_compare                    v_comp;
    
    public:

		explicit map(const key_compare &comp = key_compare(),
              const allocator_type &alloc = allocator_type())
		:  tree(value_compare(comp)),alloc(alloc),k_comp(comp),v_comp(comp){}		

		template <class InputIterator>
  		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		:  tree(value_compare(comp)),alloc(alloc),k_comp(comp),v_comp(comp) {		
			insert(first, last);
        }

		map(const map &cpy)
		:  tree(value_compare(cpy.comp)),alloc(cpy.alloc),k_comp(cpy.k_comp),v_comp(cpy.v_comp) {		
			this->insert(cpy.begin(), cpy.end());
		}

		map& operator=(const map& cpy) { 
			k_comp = cpy.k_omp;
			v_comp = cpy.v_comp;
			this->clear();
			this->insert(cpy.begin(), cpy.end());
			return *this;
		}
        ~map()
        {}

        allocator_type &get_allocator(void) {return alloc;}
       
        //Element access
        T &at(Key &k) {
            value_type res = tree->search(k)->val;
            if (!res) throw std::out_of_range("map");
            return res;
        }

        T &operator[](Key &k){
            T res = tree->search(k)->val;   
            if (!res) insert(make_pair(k, T()));
            else return *res;
        }
        
        //Iterators
        iterator begin() {
            return (iterator(tree->minimum(tree->root)));
        }
        const_iterator begin() const {
            return (const_iterator(tree->minimum(tree->root)));
        }
        iterator end() {
            return (iterator(tree->maximum(tree->root)));
        }
        const_iterator end() const {
            return (const_iterator(tree->maximum(tree->root)));
        }

        iterator rbegin() {
            return (reverse_iterator(tree->maximum(tree->root)));
        }
        const_iterator rbegin() const {
            return (const_reverse_iterator(tree->maximum(tree->root)));
        }
        iterator rend();
        const_iterator rend() const {
            return (const_reverse_iterator(tree->minimum(tree->root)));
        }

        //Capacity
        bool empty() {
            return (tree == NULL);
        }

        size_type size() {
            return count;
        }

        size_type max_size() {
            return alloc.max_size();
        }

        //Modifiers
        void clear() {tree->clear();}
        
        pair<iterator, bool> insert( const value_type& value ) {
            return tree->insert(value);
        }

        iterator insert(iterator hint, const_reference val) {
            (void) hint;
            return (tree->insert(val).first);
        }

        template< class InputIt>
        void insert( InputIt first, InputIt last ) {
            while (first != last) insert(*first++);
        }

        void erase( iterator pos ) {
            tree->remove(*pos);
        }
        void erase( iterator first, iterator last ) {
            while (first != last) tree->remove(*first++);
        }

        size_type erase( const Key& key )  {
            return tree->remove(key);
        }

        void swap( map& other ) {
			swap(tree->root,  other.tree->root);
            swap(tree->count, other.tree->count);
        }
        
        //Lookup
        size_type count( const Key& key ) const {return (tree->search(key) ?  1 : 0);}

        iterator find( const Key& key ) {return iterator(tree->search(key));}
        
        const_iterator find( const Key& key ) const {return const_iterator(tree->search(key));}

        iterator lower_bound( const Key& key ) {
            return (iterator(tree->search(key)));
        }

        const_iterator lower_bound( const Key& key ) const {
            return (const_iterator(tree->search(key)));
        }
        
        iterator upper_bound( const Key& key ) {
            return (++iterator(tree->search(key)));
        }
        const_iterator upper_bound( const Key& key ) const {
            return (++const_iterator(tree->search(key)));
        }
        
        pair<iterator,iterator> equal_range( const Key& key ) {
            return (make_pair(lower_bound(key),upper_bound(key)));
        }
        pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
            return (make_pair(lower_bound(key),upper_bound(key)));
        }
        //Observers
        key_compare key_comp() const {return key_compare();}

        value_compare value_comp() const {return value_compare();}

        //Non-member functions
        friend void swap(map& lhs, map& rhs ) {lhs.swap(rhs);}

        friend bool operator==( const map& lhs, const map& rhs ) {
            iterator l(lhs.tree->root);
            iterator r(rhs.tree->root);
            while (l != l.end() && r != r.end()) {
                if (l != r) return (0);
                l++;r++;
            }
            return l.end() == r.end() ? 1 : 0; 
        }

        friend bool operator!=( const map& lhs, const map& rhs ) {
            return !(lhs == rhs);
        }
        friend bool operator<( const map& lhs,const map& rhs ) {
            return lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(), rhs.end());
        }
        friend bool operator<=( const map& lhs, const map& rhs ) {
            return lhs == rhs || lhs < rhs;
        }
        friend bool operator>( const map& lhs,const map& rhs ) {
            return lexicographical_compare(rhs.begin(),rhs.end(),lhs.begin(), lhs.end());
        }
        friend bool operator>=( const map& lhs, const map& rhs ) {
            return lhs == rhs || lhs > rhs;

        }

    };


}


#endif 