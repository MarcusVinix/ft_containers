#ifndef SET_HPP
# define SET_HPP

#include <rb_tree.hpp>

namespace ft
{

	template<class T, class Compare = ft::less<T>, class Alloc = std::allocator<T>>
	class set {

		private:

			ft::rb_tree<T, T, ft::_Identity<T>, Compare, Alloc>	_tree_type;
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
	};

} // namespace ft


#endif