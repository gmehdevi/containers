#ifndef RB_TREE_H
#define RB_TREE_H
#define RED 1
#define BLACK 0
#include "bits/stdc++.h"
#include "tree_iterators.hpp"
#include "pair.hpp"

namespace ft {

    template<typename T>
    struct RB_Node{
        RB_Node():parent(NULL),left(NULL),right(NULL),color(BLACK),val(T()) {;}
        RB_Node(RB_Node *parent = NULL, T &val = T(), bool color = BLACK):parent(parent),left(NULL),right(NULL),color(color),val(val) {;}
        RB_Node *parent;
        RB_Node *left;
        RB_Node *right;
        bool     color;
        T        val;
    };
    
    template<typename T, typename Compare, typename Alloc = std::allocator<RB_Node<T>>>
    class RB_Tree {
		typedef Alloc allocator_type;
		typedef Compare value_compare;
		typedef RB_Node<T> Node;
    private:
        typedef bidirectional_iterator<T, Compare, allocator_type, RB_Node<T>>        iterator;
        typedef bidirectional_iterator<const T, Compare, allocator_type, RB_Node<T>>  const_iterator;
        typedef ft::reverse_iterator<iterator>                                                          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                                                    const_reverse_iterator;
        typedef pair<Node *, bool> return_type ;
       
        Node            *root;
        Alloc           alloc;
        value_compare   comp;
        size_t          count;
            
    public:
        RB_Tree(Compare comp):root(NULL), alloc(Alloc()), comp(comp), count(0){};

        size_t size() {return count;}    

        Node &rotateLeft(Node &node) {
            if (!node || !node.left)
				return NULL;
            Node x = node.right;
            Node y = x.left;
            x.left = node;
            node.right = y;
            node.parent = x; // parent resetting is also important.
            if(y != NULL)
                y.parent = node;
            return(x);
        }
        //this function performs right rotation
        Node &rotateRight(Node &node) {
            if (!node || !node.right)
				return NULL;
            Node x = node.left;
            Node y = x.right;
            x.right = node;
            node.left = y;
            node.parent = x;
            if(y!= NULL)
                y.parent = node;
            return(x);
        }
    
        void rbTransplant(Node *u, Node *v) {
            if (u->parent == NULL) 
                root = v;
            else if (u == u->parent->left)
                u->parent->left = v;
            else 
                u->parent->right = v;
            v->parent = u->parent;
        }

        Node *minimum(Node *node) {
            while (node->left != NULL) {
                node = node->left;
            }
            return node;
        }
        Node *maximum(Node *node) {
            while (node->right != NULL) {
                node = node->right;
            }
            return node;
        }
 	    // fix the red-black tree after insert
        void fixInsert(Node *k) {
            Node *u;
            while (k->parent->color == RED) {
                if (k->parent == k->parent->parent->right) {
                    u = k->parent->parent->left; // uncle
                    if (u->color == RED) {
                        // case 3.1
                        u->color = BLACK;
                        k->parent->color = BLACK;
                        k->parent->parent->color = RED;
                        k = k->parent->parent;
                    } else {
                        if (k == k->parent->left) {
                            // case 3.2.2
                            k = k->parent;
                            rotateRight(k);
                        }
                        // case 3.2.1
                        k->parent->color = BLACK;
                        k->parent->parent->color = RED;
                        rotateLeft(k->parent->parent);
                    }
                } else {
                    u = k->parent->parent->right; // uncle

                    if (u->color == RED) {
                        // mirror case 3.1
                        u->color = BLACK;
                        k->parent->color = BLACK;
                        k->parent->parent->color = RED;
                        k = k->parent->parent;	
                    } else {
                        if (k == k->parent->right) {
                            // mirror case 3.2.2
                            k = k->parent;
                            rotateLeft(k);
                        }
                        // mirror case 3.2.1
                        k->parent->color = BLACK;
                        k->parent->parent->color = RED;
                        rotateRight(k->parent->parent);
                    }
                }
                if (k == root) {
                    break;
                }
            }
            root->color = 0;
        }
         
        void fixRemove(Node *k) {
            Node *s;
            while (k != root && k->color == BLACK) {
                if (k == k->parent->left) {
                    s = k->parent->right;
                    if (s->color == 1) {
                        // case 3.1
                        s->color = BLACK;
                        k->parent->color = RED;
                        rotateLeft(k->parent);
                        s = k->parent->right;
                    }

                    if (s->left->color == BLACK && s->right->color == BLACK) {
                        // case 3.2
                        s->color = RED;
                        k = k->parent;
                    } else {
                        if (s->right->color == BLACK) {
                            // case 3.3
                            s->left->color = BLACK;
                            s->color = RED;
                            rotateRight(s);
                            s = k->parent->right;
                        } 

                        // case 3.4
                        s->color = k->parent->color;
                        k->parent->color = BLACK;
                        s->right->color = BLACK;
                        rotateLeft(k->parent);
                        k = root;
                    }
                } else {
                    s = k->parent->left;
                    if (s->color == RED) {
                        // case 3.1
                        s->color = BLACK;
                        k->parent->color = RED;
                        rotateRight(k->parent);
                        s = k->parent->left;
                    }

                    if (s->right->color == BLACK && s->right->color == BLACK) {
                        // case 3.2
                        s->color = RED;
                        k = k->parent;
                    } else {
                        if (s->left->color == BLACK) {
                            // case 3.3
                            s->right->color = BLACK;
                            s->color = RED;
                            rotateLeft(s);
                            s = k->parent->left;
                        } 

                        // case 3.4
                        s->color = k->parent->color;
                        k->parent->color = BLACK;
                        s->left->color = BLACK;
                        rotateRight(k->parent);
                        k = root;
                    }
                } 
            }
            k->color = BLACK;
	    }
        
        Node *search_rec(Node *node, T& val) {
            if (node == NULL || (!comp(val, node->val) && !comp(node->val, val)))
                return node;
            if (comp(val, node->val))
                return search_rec(node->left, val);
            return search_rec(node->right, val);
        }
        public:


        Node *search(T &key) {
            return search_rec(root, key);
        }

       return_type insert(T& key) {
            Node *x = root;
            Node *y = NULL;
            Node *node;

            while (x) {
                y = x;
                if (comp(key, x->val))
                    x = x->left;
                else if (comp(x->val, key))
                    x = x->right;
                else
                    return (make_pair(&x, false));
            }
            alloc.construct(node, y, key, RED);
            if (!y)
                root = node;
            else if (comp(node->val ,y->val))
                y->left = node;
            else
                y->right = node;
            count++;
             if (!node->parent)
                node->color = BLACK;
            else if (node->parent->parent)
                fix_insert(node);
            return(make_pair(node, 1));
        }

		void deleteNode(Node node) {
			alloc.destroy(node);
			alloc.deallocate(node, 1);
		}

        size_t remove(T& key) {
            // find the node containing key
            Node *node = root;
            Node * z = NULL;
            Node * x, y;
            while (node != NULL) {
                if (node->val == key)
                    {z = node; break;}
                if (comp(key, node->val))
                    node = node->left;
                else 
                    node = node->right;
            }
            if (z == NULL) 
                return 0;
            count --;
            y = z;
            int y_original_color = y->color;
            if (z->left == NULL) {
                x = z->right;
                rbTransplant(z, z->right);
            } else if (z->right == NULL) {
                x = z->left;
                rbTransplant(z, z->left);
            } else {
                y = minimum(z->right);
                y_original_color = y->color;
                x = y->right;
                if (y->parent == z) {
                    x->parent = y;
                } else {
                    rbTransplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }

                rbTransplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            deleteNode(z);
            if (y_original_color == 0)
                fixRemove(x);
            return (1);
        }

		void clear() {
            iterator it(minimum(root));
            iterator last(maximum(root));
            iterator tmp;
            while (tmp != last) {
                tmp = it++;
                deleteNode(tmp);
            }
            count = 0;
		}

        ~RB_Tree() {
            iterator it(minimum(root));
            iterator tmp;
            Node *last = maximum(root);
            while (tmp != last) {
                tmp = it++;
                deleteNode(tmp);
            }
        };
    };
}
#undef RED
#undef BLACK
#endif