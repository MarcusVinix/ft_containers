#ifndef RB_TREE_ITERATOR_HPP
# define RB_TREE_ITERATOR_HPP

#include <iterator.hpp>
#include <rb_tree.hpp>

namespace ft
{

	class nullptr_t {
		public:
		template <class T> operator T *() const { return 0; }
		template <class C, class T> operator T C::*() const { return 0; }

		private:
		void operator&() const;
	};

	const nullptr_t _nullptr = {};

	enum color { RED = false, BLACK = true };

	template< class T, class Alloc = std::allocator<T> >
	class Node {
		public:
			typedef Node<T>*	ptr_node;
			typedef Alloc		allocator_type;
			typedef enum color	color_type;
			typedef T			value_type;
			typedef T*			pointer;
			typedef T&			reference;
			typedef const T*	const_pointer;
			typedef const T&	const_reference;

			ptr_node			parent;
			ptr_node			left;
			ptr_node			right;
			ptr_node			tmp;
			color_type			color;
			pointer				data;
			allocator_type		alloc;

			explicit Node( color_type color = BLACK, ptr_node parent = _nullptr,
							ptr_node left = _nullptr, ptr_node right = _nullptr, allocator_type alloc = allocator_type() )
							: parent( parent ), left( left ), right( right ), color( color ), data(_nullptr), alloc( alloc ) { }

			Node( value_type val, color_type color, ptr_node nil, allocator_type alloc = allocator_type() ) 
				: parent( nil ), left( nil ), right( nil ), color( color ), alloc ( alloc ) {
				this->data = this->alloc.allocate(1);
				this->alloc.construct( this->data, val );
			}

			Node( const Node & n ) : parent( n.parent ), left( n.left ), right( n.right ), color( n.color  ),
									alloc( n.alloc ) {
				this->data = this->alloc.allocate(1);
				if (n.data != _nullptr)
					this->alloc.construct(this->data, *n.data);
			}

			Node & operator=( const Node & n ) {
				if (this != &n) {
					if (n.data != _nullptr) {
						if (this->data != _nullptr) {
							this->alloc.destroy(this->data);
							this->alloc.deallocate(this->data, 1);
						}
						this->data = this->alloc.allocate(1);
						this->alloc.construct(this->data, *n.data);
					} else {
						if (this->data != _nullptr) {
							this->alloc.destroy(this->data);
							this->alloc.deallocate(this->data, 1);
						}
						this->data = _nullptr;
					}
					this->parent = n.parent;
					this->left = n.left;
					this->right = n.right;
					this->color = n.color;
				}
				return *this;
			}

			virtual ~Node( void ) {
				if (this->data != _nullptr)
					this->alloc.destroy(this->data);
				this->alloc.deallocate(this->data, 1);
			}
	};

	template< class T >
	class rbt_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {

		public:

			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef ft::bidirectional_iterator_tag	iterator_category;
			typedef std::ptrdiff_t					difference_type;
			typedef rbt_iterator<T>					self;
			typedef typename Node<T>::ptr_node		ptr_node;
			typedef Node<T>*						link_type;
			ptr_node								_node;

			rbt_iterator( void ) : _node( ), _leaf() { }
			rbt_iterator( ptr_node node, ptr_node leaf = _nullptr ) : _node( node), _leaf( leaf ) { }
			rbt_iterator( const rbt_iterator<T> & it ) : _node( it._node ), _leaf( it._leaf ) { }

			self & operator=( const rbt_iterator<T> & it ) {
				this->_node = it._node;
				this->_leaf = it._leaf;
				return *this;
			}

			reference operator*( void ) const { return *this->_node->data; }

			pointer operator->( void ) const { return &(operator*()); }

			ptr_node _minimum( ptr_node node ) {
				while (node->left != this->_leaf)
					node = node->left;
				return node;
			}

			ptr_node _maximum( ptr_node node ) {
				while (node->right != this->_leaf)
					node = node->right;
				return node;
			}

			ptr_node _successor( ptr_node x ) {
				if (x->right != this->_leaf)
					return this->_minimum(x->right);
				ptr_node y = x->parent;
				while (y != this->_leaf && x == y->right) {
					x = y;
					y = y->parent;
				}
				return y;
			}

			ptr_node _predecessor( ptr_node x ) {
				if (x == this->_leaf)
					return this->_leaf->tmp;
				if (x->left != this->_leaf)
					return this->_maximum(x->left);
				ptr_node y = x->parent;
				while (y != this->_leaf && x == y->left) {
					x = y;
					y = y->parent;
				}
				return y;
			}

			self & operator++( void ) {
				this->_node = this->_successor(this->_node);
				return *this;
			}

			self operator++( int ) {
				self tmp = *this;
				++*this;
				return tmp;
			}

			self & operator--( void ) {
				this->_node = this->_predecessor(this->_node);
				return *this;
			}

			self operator--( int ) {
				self tmp = *this;
				--*this;
				return tmp;
			}

			bool operator==( const self & rhs ) const { return this->_node == rhs._node; }

			bool operator!=( const self & rhs ) const { return this->_node != rhs._node; }

			private:

				ptr_node							_leaf;

	};

	template< class T >
	class rbt_const_iterator {

		public:

			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef ft::bidirectional_iterator_tag	iterator_category;
			typedef std::ptrdiff_t					difference_type;
			typedef rbt_const_iterator<T>			self;
			typedef typename Node<T>::ptr_node		ptr_node;
			typedef Node<T>*						link_type;
			ptr_node								_node;

			rbt_const_iterator( void ) : _node( ), _leaf( ) { }

			rbt_const_iterator( ptr_node node, ptr_node leaf = _nullptr ) : _node( node ), _leaf( leaf ) { }

			rbt_const_iterator( const rbt_const_iterator<T> & it ) : _node( it._node ), _leaf( it._leaf ) { }

			self & operator=( const rbt_const_iterator<T> & it ) {
				this->_node = it._node;
				this->_leaf = it._leaf;
				return *this;
			}

			reference operator*( void ) const { return *this->_node->data; }

			pointer operator->( void ) const { return &(operator*()); }

			ptr_node _minimum( ptr_node node ) {
				while (node->left != this->_leaf)
					node = node->left;
				return node;
			}

			ptr_node _maximum( ptr_node node ) {
				while (node->right != this->_leaf)
					node = node->right;
				return node;
			}

			ptr_node _successor( ptr_node x ) {
				if (x->right != this->_leaf)
					return this->_minimum(x->right);
				ptr_node y = x->parent;
				while (y != this->_leaf && x == y->right) {
					x = y;
					y = y->parent;
				}
				return y;
			}

			ptr_node _predecessor( ptr_node x ) {
				if (x == this->_leaf)
					return this->_leaf->tmp;
				if (x->left != this->_leaf)
					return this->_maximum(x->left);
				ptr_node y = x->parent;
				while (y != this->_leaf && x == y->left) {
					x = y;
					y = y->parent;
				}
				return y;
			}

			self & operator++( void ) {
				this->_node = this->_successor(this->_node);
				return *this;
			}

			self operator++( int ) {
				self tmp = *this;
				++*this;
				return tmp;
			}

			self & operator--( void ) {
				this->_node = this->_predecessor(this->_node);
				return *this;
			}

			self operator--( int ) {
				self tmp = *this;
				--*this;
				return tmp;
			}

			bool operator==( const self & rhs ) const { return this->_node == rhs._node; }

			bool operator!=( const self & rhs ) const { return this->_node != rhs._node; }

			private:

				ptr_node							_leaf;

	};

	template<class T>
	inline bool operator==( const rbt_iterator<T> &it1, const rbt_const_iterator<T> &it2 ) {
		return *it1 == *it2;
	}

	template<class T>
	inline bool operator!=( const rbt_iterator<T> &it1, const rbt_const_iterator<T> &it2 ) {
		return *it1 != *it2;
	}
	
} // namespace ft


#endif