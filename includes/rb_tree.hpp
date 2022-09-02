#ifndef RB_TREE_HPP
# define RB_TREE_HPP

#include <reverse_iterator.hpp>
#include <utility.hpp>
#include <algorithm.hpp>
#include <functional.hpp>
#include <memory>
#include <rb_tree_iterator.hpp>

namespace ft
{

	template< class Key, class T, class KeyOfValue, class Compare = ft::less<Key>, class Alloc = std::allocator< ft::pair< const Key, T > > >
	class rb_tree {

		public:
			//members types
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef const T*								const_pointer;
			typedef const T&								const_reference;
			typedef Alloc									allocator_type;
			typedef Compare									key_compare;
			typedef typename Alloc::value_type				value_type;
			typedef Node<value_type, allocator_type>		node_type;
			typedef node_type*								ptr_node;
			typedef node_type const &						ref_node;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef rbt_iterator<value_type>				iterator;
			typedef rbt_const_iterator<value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef std::allocator<node_type>				node_allocator_type;

			//constructors
			explicit rb_tree( const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type() )
							: _size( 0 ), _alloc( alloc ), _node_alloc( node_allocator_type() ), _comp( comp ) {
				this->_nil = this->_node_alloc.allocate(1);
				this->_node_alloc.construct(this->_nil, node_type());
				this->_nil->parent = this->_nil->left = this->_nil->right = this->_nil;
				this->_root = this->_nil;
			}

			rb_tree( const rb_tree & tree ) : _size( tree._size ), _alloc( tree._alloc ), 
					_node_alloc( node_allocator_type(tree._node_alloc) ), _comp( tree._comp ) {
				this->_nil = this->_node_alloc.allocate(1);
				this->_nil->parent = this->_nil->left = this->_nil->right = this->_nil;
				this->_node_alloc.construct(this->_nil, node_type());
				this->_root = this->_copy_tree(tree._root, tree._nil);
				this->_nil->tmp = _maximum(this->_root);
			}

			//destructor
			virtual ~rb_tree( void ) {
				clear();
				this->_node_alloc.destroy(this->_nil);
				this->_node_alloc.deallocate(this->_nil, 1);
			}

			//copy assignment operator
			rb_tree & operator=( const rb_tree & tree ) {
				if (this != &tree) {
					this->_destroy_tree(this->_root);
					this->_root = _copy_tree(tree._root, tree._nil);
					this->_size = tree._size;
				}
				return *this;
			}

			// getters
			ptr_node get_root( void ) const { return this->_root; }
			
			ptr_node get_nil( void ) const { return this->_nil; }

			// capacity
			bool empty( void ) const { return size() == 0; }

			size_type size( void ) const { return this->_size; }

			size_type max_size( void ) const { return size_type(-1); }

			//iterators
			iterator begin( void ) { return iterator(_minimum(this->_root), this->_nil); }

			const_iterator begin( void ) const { return const_iterator(_minimum(this->_root), this->_nil); }

			iterator end( void ) { return iterator(this->_nil, this->_nil); }

			const_iterator end( void ) const { return const_iterator(this->_nil, this->_nil); }

			reverse_iterator rbegin( void ) { return reverse_iterator(end()); }

			const_reverse_iterator rbegin( void ) const { return const_reverse_iterator(end()); }

			reverse_iterator rend( void ) { return reverse_iterator(begin()); }

			const_reverse_iterator rend( void ) const { return const_reverse_iterator(begin()); }

			// tree operations

			ft::pair<iterator, bool> insert_unique( const value_type & val ) {
				return this->_insert(val);
			}

			iterator insert_unique( iterator hint, const value_type & val ) {
				(void)hint;
				ft::pair<iterator, bool> p = this->_insert(val);
				return p.first;
			}

			template< class InputIterator >
			void insert_unique( InputIterator first, InputIterator last ) {
				for ( ; first != last; ++first)
					this->_insert(*first);
			}

			void erase( iterator position ) {
				if (position == end())
					return ;
				this->_erase_aux(position);
			}

			size_type erase( const key_type & key ) {
				ft::pair<iterator, iterator> p = equal_range(key);
				const size_type old_size = size();
				this->_erase_aux(p.first, p.second);
				return old_size - size();
			}

			void erase( iterator first, iterator last ) {
				this->_erase_aux(first, last);
			}

			void swap( rb_tree & tree ) {
				rb_tree<Key, T, KeyOfValue, Compare, Alloc> tmp(tree);
				tree = *this;
				*this = tmp;
			}

			void clear( void ) {
				this->_destroy_tree(this->_root);
				this->_root = this->_nil;
				this->_size = 0;
			}

			key_compare key_comp( void ) const { return this->_comp; }

			iterator find( const key_type & key ) {
				ptr_node node = this->_find(key);
				return iterator(node, this->_nil);
			}

			const_iterator find( const key_type & key ) const {
				ptr_node node = this->_find(key);
				return const_iterator(node, this->_nil);
			}

			size_type count( const key_type & key ) const {
				return this->_find(key) == this->_nil ? 0 : 1;
			}

			iterator lower_bound( const key_type & key ) {
				return iterator(this->_lower_bound(key), this->_nil);
			}

			const_iterator lower_bound( const key_type & key ) const {
				return const_iterator(this->_lower_bound(key), this->_nil);
			}

			iterator upper_bound( const key_type & key ) {
				return iterator(this->_upper_bound(key), this->_nil);
			}

			const_iterator upper_bound( const key_type & key ) const {
				return const_iterator(this->_upper_bound(key), this->_nil);
			}

			ft::pair<iterator, iterator> equal_range( const key_type & key ) {
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			ft::pair<const_iterator, const_iterator> equal_range( const key_type & key ) const {
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			allocator_type get_allocator( void ) const { return allocator_type(this->_alloc); }

			private:
				//private members types
				size_type			_size;
				allocator_type		_alloc;
				node_allocator_type	_node_alloc;
				key_compare			_comp;
				ptr_node			_root;
				ptr_node			_nil;


				//private members methods

				const key_type _key( ptr_node node ) const {
					return KeyOfValue()(*(node->data));
				}

				const key_type _key( value_type val ) const {
					return KeyOfValue()(val);
				}

				ptr_node _new_node( const value_type & value, const typename node_type::color_type color = RED) {
					ptr_node z = this->_node_alloc.allocate(1);
					this->_node_alloc.construct(z, node_type(value, color, this->_nil, this->_alloc));
					return z;
				}

				ptr_node _minimum( ptr_node node ) const {
					if (node == this->_nil)
						return this->_nil;
					while (node->left != this->_nil)
						node = node->left;
					return node;
				}

				ptr_node _maximum( ptr_node node ) const {
					if (node == this->_nil)
						return this->_nil;
					while (node->right != this->_nil)
						node = node->right;
					return node;
				}

				ptr_node _find( const key_type & k ) const {
					ptr_node node;
					node = this->_root;
					while (node != this->_nil) {
						if (!(this->_comp(k, _key(node)) || this->_comp(_key(node), k)))
							return node;
						else if (this->_comp(k, _key(node)))
							node = node->left;
						else
							node = node->right;
					}
					return this->_nil;
				}

				ptr_node _lower_bound( const key_type & key ) const {
					ptr_node x = this->_root;
					ptr_node y = this->_nil;
					while (x != this->_nil) {
						if (!this->_comp(_key(x), key)) {
							y = x;
							x = x->left;
						} else
							x = x->right;
					}
					return y;
				}

				ptr_node _upper_bound( const key_type & key ) const {
					ptr_node x = this->_root;
					ptr_node y = this->_nil;
					while (x != this->_nil) {
						if (this->_comp(key, _key(x))) {
							y = x;
							x = x->left;
						} else
							x = x->right;
					}
					return y;
				}

				ptr_node _copy_tree( const ptr_node & node, const ptr_node & tree_copy ) {
					if (node == tree_copy)
						return this->_nil;
					ptr_node new_node = this->_node_alloc.allocate(1);
					this->_node_alloc.construct(new_node, *node);
					new_node->left = _copy_tree(node->left, tree_copy);
					new_node->right = _copy_tree(node->right, tree_copy);
					new_node->parent = this->_nil;
					if (new_node->left != this->_nil)
						new_node->left->parent = new_node;
					if (new_node->right != this->_nil)
						new_node->right->parent = new_node;
					return new_node;
				}

				/**
				 * insert:
				 *      before          after
				 *        p               p
				 *       / \             / \
				 *      l   q           l   q
				 *         / \         /   / \
				 *        p   r       z   l   q
				 */
				ft::pair<iterator, bool> _insert( const value_type & val ) {
					ptr_node y = this->_nil;
					ptr_node x = this->_root;
					while (x != this->_nil) {
						y = x;
						if (!_comp(_key(val), _key(x)) && !_comp(_key(x), _key(val))) {
							this->_nil->tmp = _maximum(this->_root);
							return ft::make_pair(iterator(x, this->_nil), false);
						} else if (_comp(_key(val), _key(x)))
							x = x->left;
						else
							x = x->right;
					}
					ptr_node z = _new_node(val);
					z->parent = y;
					if (y == this->_nil)
						this->_root = z;
					else if (_comp(_key(z), _key(y)))
						y->left = z;
					else
						y->right = z;
					z->left = this->_nil;
					z->right = this->_nil;
					z->color = RED;
					_insert_fixup(z);
					++this->_size;
					this->_nil->tmp = _maximum(this->_root);
					return ft::make_pair(iterator(z, this->_nil), true);
				}

				void _insert_fixup( ptr_node z ) {
					while (z->parent->color == RED) {
						if (z->parent == z->parent->parent->left) {
							ptr_node y = z->parent->parent->right;
							if (y->color == RED) {
								z->parent->color = BLACK;
								y->color = BLACK;
								z->parent->parent->color = RED;
								z = z->parent->parent;
							} else {
								if (z == z->parent->right) {
									z = z->parent;
									_left_rotate(z);
								}
								z->parent->color = BLACK;
								z->parent->parent->color = RED;
								_right_rotate(z->parent->parent);
							}
						} else {
							ptr_node y = z->parent->parent->left;
							if (y->color == RED) {
								z->parent->color = BLACK;
								y->color = BLACK;
								z->parent->parent->color = RED;
								z = z->parent->parent;
							} else {
								if (z == z->parent->left) {
									z = z->parent;
									_right_rotate(z);
								}
								z->parent->color = BLACK;
								z->parent->parent->color = RED;
								_left_rotate(z->parent->parent);
							}
						}
					}
					this->_root->color = BLACK;
				}

				void _destroy_tree( ptr_node node ) {
					if (node != this->_nil) {
						_destroy_tree(node->left);
						_destroy_tree(node->right);
						_destroy_node(node);
					}
				}

				void _destroy_node( ptr_node node ) {
					this->_node_alloc.destroy(node);
					this->_node_alloc.deallocate(node, 1);
				}

				void _erase_aux( iterator position ) {
					ptr_node y = _remove(position._node);
					_destroy_node(y);
					--this->_size;
					this->_nil->tmp = _maximum(this->_root);
				}

				void _erase_aux( iterator first, iterator last ) {
					if (first == begin() && last == end())
						clear();
					else {
						while (first != last) {
							erase(first++);
						}
					}
				}

				ptr_node _remove( ptr_node z ) {
					ptr_node x;
					ptr_node y = z;
					color y_original_color = y->color;
					if (z->left == this->_nil) {
						x = z->right;
						_transplant(z, z->right);
					} else if (z->right == this->_nil) {
						x = z->left;
						_transplant(z, z->left);
					} else {
						y = _minimum(z->right);
						y_original_color = y->color;
						x = y->right;
						if (y->parent == z)
							x->parent = y;
						else {
							_transplant(y, y->right);
							y->right = z->right;
							y->right->parent = y;
						}
						_transplant(z, y);
						y->left = z->left;
						y->left->parent = y;
						y->color = z->color;
					}
					if (y_original_color == BLACK)
						_remove_fixup(x);
					return z;
				}

				void _remove_fixup( ptr_node x ) {
					ptr_node w;
					while (x != this->_root && x->color == BLACK) {
						if (x == x->parent->left) {
							w = x->parent->right;
							if (w->color == RED) {
								w->color = BLACK;
								x->parent->color = RED;
								_left_rotate(x->parent);
								w = x->parent->right;
							}
							if (w->left->color == BLACK && w->right->color == BLACK) {
								w->color = RED;
								x = x->parent;
							} else if (w->right->color == BLACK) {
								w->left->color = BLACK;
								w->color = RED;
								_right_rotate(w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->right->color = BLACK;
							_left_rotate(x->parent);
							x = this->_root;
						} else {
							w = x->parent->left;
							if (w->color == RED) {
								w->color = BLACK;
								x->parent->color = RED;
								_right_rotate(x->parent);
								w = x->parent->left;
							}
							if (w->right->color == BLACK && w->left->color == BLACK) {
								w->color = RED;
								x = x->parent;
							} else if (w->left->color == BLACK) {
								w->right->color = BLACK;
								w->color = RED;
								_left_rotate(w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->left->color = BLACK;
							_right_rotate(x->parent);
							x = this->_root;
						}
					}
					x->color = BLACK;
				}

				ptr_node _tree_rebalance_for_erase( ptr_node const z ) {
					ptr_node y = z;
					ptr_node x = 0;
					ptr_node x_parent = 0;

					if (y->left == this->_nil)
						x = y->right;
					else if (y->right == this->_nil)
						x = y->left;
					else {
						y = y->right;
						while (y->left != this->_nil)
							y = y->left;
						x = y->right;
					}
					if (y != z) {
						z->left->parent = y;
						y->left = z->left;
						if (y != z->right) {
							x_parent = y->parent;
							if (x)
								x->parent = y->parent;
							y->parent->left = x;
							y->right = z->right;
							z->right->parent = y;
						} else
							x_parent = y;
						if (this->_root == z)
							this->_root = y;
						else if (z->parent->left == z)
							z->parent->left = y;
						else
							z->parent->right = y;
						y->parent = z->parent;
						std::swap(y->color, z->color);
						y = z;
					} else {
						x_parent = y->parent;
						if (x)
							x->parent = y->parent;
						if (this->_root == z)
							this->_root = x;
						else if (z->parent->left == z)
							z->parent->left = x;
						else
							z->parent->right = x;
					}
					if (y->color != RED) {
						while (x != this->_root && (x == this->_nil || x->color == BLACK)) {
							if (x == x_parent->left) {
								ptr_node w = x_parent->right;
								if (w->color == RED) {
									w->color = BLACK;
									x_parent->color = RED;
									_left_rotate(x_parent);
									w = x_parent->right;
								}
								if ((w->left == this->_nil || w->left->color == BLACK) &&
									(w->right == this->_nil || w->right->color == BLACK)) {
										w->color = RED;
										x = x_parent;
										x_parent = x_parent->parent;
									} else {
										if (w->right == this->_nil || w->right->color == BLACK) {
											w->left->color = BLACK;
											w->color = RED;
											_right_rotate(w);
											w = x_parent->right;
										}
										w->color = x_parent->color;
										x_parent->color = BLACK;
										if (w->right != this->_nil)
											w->right->color = BLACK;
										_left_rotate(x_parent);
										break ;
									}
							} else {
								ptr_node w = x_parent->left;
								if (w->color == RED) {
									w->color = BLACK;
									x_parent->color = RED;
									_right_rotate(x_parent);
									w = x_parent->left;
								}
								if ((w->right == this->_nil || w->right->color == BLACK) &&
									(w->left == this->_nil || w->left->color == BLACK)) {
									w->color = RED;
									x = x_parent;
									x_parent = x_parent->parent;
								} else {
									if (w->left == this->_nil || w->left->color == BLACK) {
										w->right->color = BLACK;
										w->color = RED;
										_left_rotate(w);
										w = x_parent->left;
									}
									w->color = x_parent->color;
									x_parent->color = BLACK;
									if (w->left != this->_nil)
										w->left->color = BLACK;
									_right_rotate(x_parent);
									break ;
								}
							}
							if (x == this->_nil)
								x->color = BLACK;
						}
					}
					return y;
				}

				/**
				 * The child nodes of y are transplanted to z as well.
				 * If y is the root, the root is changed to z.
				 */
				void _transplant( ptr_node u, ptr_node v ) {
					if (u->parent == this->_nil)
						this->_root = v;
					else if (u == u->parent->left)
						u->parent->left = v;
					else
						u->parent->right = v;
					v->parent = u->parent;
				}

				/**
				 * Left rotation:
				 *       before              after
				 *         p                    q
				 *        / \                  / \
				 *       l   q                p   r
				 *          / \              / \
				 *         p   r            l   q
				 *  
				 */
				void _left_rotate( ptr_node x ) {
					if (x == this->_nil || x->right == this->_nil)
						return;
					ptr_node y = x->right;
					x->right = y->left;
					if (y->left != this->_nil)
						y->left->parent = x;
					y->parent = x->parent;
					if (x->parent == this->_nil)
						this->_root = y;
					else if (x == x->parent->left)
						x->parent->left = y;
					else
						x->parent->right = y;
					y->left = x;
					x->parent = y;
				}

				void _right_rotate( ptr_node x ) {
					if (x == this->_nil || x->left == this->_nil)
						return;
					ptr_node y = x->left;
					x->left = y->right;
					if (y->right != this->_nil)
						y->right->parent = x;
					y->parent = x->parent;
					if (x->parent == this->_nil)
						this->_root = y;
					else if (x == x->parent->right)
						x->parent->right = y;
					else
						x->parent->left = y;
					y->right = x;
					x->parent = y;
				}

	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator==( const ft::rb_tree<Key, T, Compare, Alloc> & lhs, const ft::rb_tree<Key, T, Compare, Alloc> & rhs) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=( const ft::rb_tree<Key, T, Compare, Alloc> & lhs, const ft::rb_tree<Key, T, Compare, Alloc> & rhs) {
		return !(lhs == rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<( const ft::rb_tree<Key, T, Compare, Alloc> & lhs, const ft::rb_tree<Key, T, Compare, Alloc> & rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>( const ft::rb_tree<Key, T, Compare, Alloc> & lhs, const ft::rb_tree<Key, T, Compare, Alloc> & rhs) {
		return rhs < lhs;
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=( const ft::rb_tree<Key, T, Compare, Alloc> & lhs, const ft::rb_tree<Key, T, Compare, Alloc> & rhs) {
		return !(rhs < lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=( const ft::rb_tree<Key, T, Compare, Alloc> & lhs, const ft::rb_tree<Key, T, Compare, Alloc> & rhs) {
		return !(lhs < rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	void swap( const ft::rb_tree<Key, T, Compare, Alloc> & lhs, const ft::rb_tree<Key, T, Compare, Alloc> & rhs) {
		lhs.swap(rhs);
	}

} // namespace ft

#endif