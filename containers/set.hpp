#ifndef SET_HPP
# define SET_HPP

#include <rb_tree.hpp>

namespace ft
{

	template<class T, class Compare = ft::less<T>, class Alloc = std::allocator<T>>
	class set {

		private:

			typedef ft::rb_tree<T, T, ft::_Identity<T>, Compare, Alloc>	_tree_type;
			_tree_type											_tree;

		public:

			//members types
			typedef T											key_type;
			typedef T											value_type;
			typedef Compare										key_compare;
			typedef Compare										value_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename _tree_type::iterator				iterator;
			typedef typename _tree_type::const_iterator			const_iterator;
			typedef typename _tree_type::reverse_iterator		reverse_iterator;
			typedef typename _tree_type::const_reverse_iterator	const_reverse_iterator;
			typedef typename _tree_type::difference_type		difference_type;
			typedef typename _tree_type::size_type				size_type;

			//constructors

			explicit set( const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type() ) : _tree( comp, alloc ) { }

			template<class InputIterator>
			set( InputIterator first, InputIterator last,
					const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type() ) : _tree( comp, alloc ) {
						this->_tree.insert_unique(first, last);
					}

			set( const set & x ) : _tree( x._tree ) { }

			~set( void ) { }

			set & operator=( const set & x ) {
				this->_tree = x._tree;
				return *this;
			}

			//Iterators

			iterator begin( void ) {
				return this->_tree.begin();
			}
			
			const_iterator begin( void ) const {
				return this->_tree.begin();
			}

			iterator end( void ) {
				return this->_tree.end();
			}

			const_iterator end( void ) const {
				return this->_tree.end();
			}

			reverse_iterator rbegin( void ) {
				return this->_tree.rbegin();
			}

			const_reverse_iterator rbegin( void ) const {
				return this->_tree.rbegin();
			}

			reverse_iterator rend( void ) {
				return this->_tree.rend();
			}

			const_reverse_iterator rend( void ) const {
				return this->_tree.rend();
			}

			//Capacity

			bool empty( void ) const {
				return this->_tree.empty();
			}

			size_type size( void ) const {
				return this->_tree.size();
			}

			size_type max_size( void ) const {
				return this->_tree.max_size();
			}

			//modifiers

			ft::pair<iterator, bool> insert( const value_type & val ) {
				return this->_tree.insert_unique(val);
			}

			iterator insert( iterator position, const value_type & val ) {
				return this->_tree.insert_unique(position, val);
			}

			template<class InputIterator>
			void insert( InputIterator first, InputIterator last ) {
				this->_tree.insert_unique(first, last);
			}

			void erase( iterator position ) {
				this->_tree.erase(position);
			}

			size_type erase( const value_type & val ) {
				return this->_tree.erase(val);
			}

			void erase( iterator first, iterator last ) {
				this->_tree.erase(first, last);
			}

			void swap( set & x ) {
				this->_tree.swap(x._tree);
			}

			void clear( void ) {
				this->_tree.clear();
			}

			//Observers

			key_compare key_comp( void ) const {
				return this->_tree.key_comp();
			}

			value_compare value_comp( void ) const {
				return this->_tree.key_comp();
			}

			//operations

			iterator find( const value_type & val ) {
				return this->_tree.find(val);
			}

			const_iterator find( const value_type & val ) const {
				return this->_tree.find(val);
			}

			size_type count( const value_type & val ) const {
				return this->_tree.count(val);
			}

			iterator lower_bound( const value_type & val ) {
				return this->_tree.lower_bound(val);
			}

			const_iterator lower_bound( const value_type & val ) const {
				return this->_tree.lower_bound(val);
			}

			iterator upper_bound( const value_type & val ) {
				return this->_tree.upper_bound(val);
			}

			const_iterator upper_bound( const value_type & val ) const {
				return this->_tree.upper_bound(val);
			}

			ft::pair<iterator, iterator> equal_range( const value_type & val ) {
				return this->_tree.equal_range(val);
			}

			ft::pair<const_iterator, const_iterator> equal_range( const value_type & val ) const {
				return this->_tree.equal_range(val);
			}

			//Allocator

			allocator_type get_allocator( void ) const {
				return  this->_tree.get_allocator();
			}
	};

	template<class Key, class Compare, class Alloc>
	bool operator==( const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs ) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<class Key, class Compare, class Alloc>
	bool operator!=( const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs ) {
		return !(lhs == rhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator<( const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), Compare());
	}

	template<class Key, class Compare, class Alloc>
	bool operator<=( const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs ) {
		return !(rhs < lhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator>( const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs ) {
		return rhs < lhs;
	}

	template<class Key, class Compare, class Alloc>
	bool operator>=( const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs ) {
		return !(lhs < rhs);
	}

	template<class Key, class Compare, class Alloc>
	void swap( ft::set<Key, Compare, Alloc> & lhs, ft::set<Key, Compare, Alloc> & rhs ) {
		lhs.swap(rhs);
	}

} // namespace ft


#endif