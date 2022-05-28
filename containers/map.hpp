#ifndef MAP_HPP
# define MAP_HPP

#include <rb_tree.hpp>
#include <iterator.hpp>

namespace ft
{

	template< class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map {

		public:

			//member types
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const key_type, mapped_type>	value_type;
			typedef Compare									key_compare;
			typedef Alloc									allocator_type;

			//nested class value_compare
			class value_compare : ft::binary_function<value_type, value_type, bool> {
			
				friend class map;

				protected:

					Compare	comp;
					value_compare( Compare c ) : comp( c ) { }

				public:

					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					bool operator()( const value_type & x, const value_type & y ) const {
						return comp(x.first, y.first);
					}

			};

		private:

			typedef ft::rb_tree<Key, T, ft::select1st<value_type>, Compare, Alloc>	_tree_type;
			_tree_type																_tree;

		public:

			//member types
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename _tree_type::iterator					iterator;
			typedef typename _tree_type::const_iterator				const_iterator;
			typedef typename _tree_type::reverse_iterator			reverse_iterator;
			typedef typename _tree_type::const_reverse_iterator		const_reverse_iterator;
			typedef typename _tree_type::difference_type			difference_type;
			typedef typename _tree_type::size_type					size_type;

			//constructs
			explicit map( const key_compare & comp = key_compare(), const allocator_type alloc = allocator_type() )
							: _tree( comp, alloc ) { }

			template<class InputIterator>
			map( InputIterator first, InputIterator last, const key_compare & comp = key_compare(),
				const allocator_type alloc = allocator_type() ) : _tree( comp, alloc ) {
				this->_tree.insert_unique(first, last);
			}

			map( const map & x ) : _tree( x._tree ) { }

			~map( void ) { }

			map & operator=( const map & x ) {
				this->_tree = x._tree;
				return *this;
			}

			//iterators

			iterator begin( void ) { return this->_tree.begin(); }

			const_iterator begin( void ) const { return this->_tree.begin(); }

			iterator end( void ) { return this->_tree.end(); }

			const_iterator end( void ) const { return this->_tree.end(); }

			reverse_iterator rbegin( void ) { return this->_tree.rbegin(); }

			const_reverse_iterator rbegin( void ) const { return this->_tree.rbegin(); }

			reverse_iterator rend( void ) { return this->_tree.rend(); }

			const_reverse_iterator rend( void ) const { return this->_tree.rend(); }

			//capacity

			bool empty( void ) const { return this->_tree.empty(); }

			size_type size( void ) const { return this->_tree.size(); }

			size_type max_size( void ) const { return this->_tree.max_size(); }

			//Element access

			mapped_type & operator[]( const key_type & k ) {
				return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
			}

			//Modifiers

			ft::pair<iterator, bool> insert( const value_type & val ) {
				return this->_tree.insert_unique(val);
			}

			iterator insert( iterator position, const value_type & val ) {
				return this->_tree.insert_unique(position, val);
			}

			template<class InputIterator>
			void insert( InputIterator first, InputIterator last ) {
				return this->_tree.insert_unique(first, last);
			}

			void erase( iterator position ) {
				this->_tree.erase(position);
			}

			size_type erase( const key_type & k ) {
				return this->_tree.erase(k);
			}

			void erase( iterator first, iterator last ) {
				this->_tree.erase(first, last);
			}

			void swap( map & x ) {
				this->_tree.swap(x._tree);
			}

			void clear( void ) {
				this->_tree.clear();
			}

			//observers

			key_compare key_comp( void ) const {
				return this->_tree.key_comp();
			}

			value_compare value_comp( void ) const {
				return value_compare(this->_tree.key_comp());
			}

			//operations

			iterator find( const key_type & k ) {
				return this->_tree.find(k);
			}

			const_iterator find( const key_type & k ) const {
				return this->_tree.find(k);
			}

			size_type count( const key_type & k ) const {
				return this->_tree.find(k) == this->_tree.end() ? 0 : 1;
			}

			iterator lower_bound( const key_type & k ) {
				return this->_tree.lower_bound(k);
			}

			const_iterator lower_bound( const key_type & k ) const {
				return this->_tree.lower_bound(k);
			}

			iterator upper_bound( const key_type & k ) {
				return this->_tree.upper_bound(k);
			}

			const_iterator upper_bound( const key_type & k ) const {
				return this->_tree.upper_bound(k);
			}

			ft::pair<const_iterator, const_iterator> equal_range( const key_type & k ) const {
				return this->_tree.equal_range(k);
			}

			ft::pair<iterator, iterator> equal_range( const key_type & k ) {
				return this->_tree.equal_range(k);
			}

			//allocator

			allocator_type get_allocator( void ) const {
				return this->_tree.get_allocator();
			}

	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator==( const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs ) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	
	template<class Key, class T, class Compare, class Alloc>
	bool operator!=( const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs ) {
		return !(lhs == rhs);
	}
	
	template<class Key, class T, class Compare, class Alloc>
	bool operator<( const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template<class Key, class T, class Compare, class Alloc>
	bool operator>( const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs ) {
		return rhs < lhs;
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=( const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs ) {
		return !(rhs < lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=( const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs ) {
		return !(lhs < rhs);
	}
	
	template<class Key, class T, class Compare, class Alloc>
	void swap( ft::map<Key, T, Compare, Alloc> & lhs, ft::map<Key, T, Compare, Alloc> & rhs ) {
		lhs.swap(rhs);
	}

} // namespace ft

#endif
