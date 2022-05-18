#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"

namespace ft
{

	template<class T, class Alloc = std::allocator<T>>
	class vector {


		public:

			typedef T														value_type;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef ft::random_access_iterator<pointer>						iterator;
			typedef ft::random_access_iterator<const_pointer>				const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef std::ptrdiff_t											difference_type;
			typedef std::size_t												size_type;

			// default construct
			explicit vector( const allocator_type & alloc = allocator_type() )
							: _size(0), _capacity(0), _alloc(alloc), _vec(NULL) { }

			//fill constructor
			explicit vector( size_type n, const value_type & val = value_type(),
							const allocator_type & alloc = allocator_type())
							: _size(n), _capacity(n), _alloc(alloc), _vec( _alloc.allocate( _size ) ) {
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(this->_vec + i, val);
			}

			//range constructor
			template<class InputIterator>
			vector( typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
					InputIterator last, const allocator_type & alloc = allocator_type() )
				: _size( ft::distance(first, last) ), _capacity( _size ), _alloc( alloc ), _vec( _alloc.allocate(_size) ) {
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.construct(this->_vec + i, *(first + i));
			}

			//copy constructor
			vector( const vector & x ) : _size( x._size ), _capacity( x._capacity ), _alloc( x._alloc ), _vec( _alloc.allocate( _capacity ) ) {
				for(size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(this->_vec + i, x._vec[i]);
			}

			//destructor
			~vector() {
				clear();
				this->_alloc.deallocate(this->_vec, this->_capacity);
			}

			// Copy assignment operator
			vector & operator=( const vector & rhs ) {
				if (this != &rhs) {
					if (this->_size != rhs._size) {
						if (this->_vec != NULL) {
							for (size_type i = 0; i < this->_size; i++)
								this->_alloc.destroy(this->_vec + i);
							this->_alloc.deallocate(this->_vec, _capacity);
						}
						this->_size = rhs._size;
						this->_capacity = rhs._capacity;
						this->_vec = this->_alloc.allocate(this->_capacity);
					}
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.construct(this->_vec + i, rhs._vec[i]);
				}
				return *this;
			}

			iterator begin( void ) {
				return iterator(this->_vec);
			}

			const_iterator begin( void ) const {
				return const_iterator(this->_vec);
			}

			iterator end( void ) {
				return begin() + this->_size;
			}

			const_iterator end( void ) const {
				return begin() + this->_size;
			}

			reverse_iterator rbegin( void ) {
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin( void ) const {
				return const_reverse_iterator(end());
			}

			reverse_iterator rend( void ) {
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend( void ) const {
				return const_reverse_iterator(begin());
			}

			size_type size( void ) const {
				return this->_size;
			}

			size_type max_size( void ) const {
				return this->_alloc.max_size();
			}

			/**
			 * Change the vector size
			 * if n is smaller than size, the content is reduced to its first n elements,
			 * removing those beyond(and destroying them).
			 * if n is greater than size, the content is expanded by inserting at the end
			 * as many elements as needed too reach a size of n.
			 */
			void resize( size_type n, value_type val = value_type() ) {
				if (n > this->_size) {
					reserve(n);
					for (size_type i = this->_size; i < n; i++)
						this->_alloc.construct(this->_vec + i, val);
				}
				else if (n < this->_size) {
					for (size_type i = n; i < this->_size; i++)
						this->_alloc.destroy(this->_vec + i);
				}
				this->_size = n;
			}

			size_type capacity() const {
				return this->_capacity;
			}

			bool empty() const {
				return this->_size == 0;
			}

			/**
			 * Request that the vector capacity be at least enough to contain n elements.
			 * If n is greater than the current vector capacity, the function causes the container to
			 * reallocate its storage increasing its capacity to n ( or greater ).
			 * 
			 * In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
			 * This function has no effect on the vector size and cannot alter its elements.
			 */
			void reserve( size_type n ) {
				if (n > max_size())
					throw std::length_error("ft::vector::reserve:: n is greater then max_size.");
				if (n > _capacity) {
					this->_capacity = n;
					pointer tmp = this->_alloc.allocate(this->_capacity);
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.construct(tmp + i, *(this->_vec + i));
					this->_alloc.deallocate(this->_vec, this->_size);
					this->_vec = tmp;
				}
			}

			reference operator[]( size_type n ) {
				return *(this->_vec + n);
			}

			const_reference operator[]( size_type n ) const {
				return *(this->_vec + n);
			}

			reference at( size_type n ) {
				if (n >= this->_size)
					throw std::out_of_range("ft::vector::at is out of range");
				return *(this->_vec + n);
			}

			const_reference at( size_type n ) const {
				if (n >= this->_size)
					throw std::out_of_range("ft::vector::at is out of range");
				return *(this->_vec + n);
			}

			reference front( void ) {
				return this->_vec[0];
			}

			const_reference front( void ) const {
				return this->_vec[0];
			}

			reference back( void ) {
				return this->_vec[this->_size - 1];
			}

			const_reference back( void ) const {
				return this->_vec[this->_size - 1];
			}

			/**
			 * Assigns new contents to the vector, replacing its current contents, and 
			 * modifying its size accordingly
			 */
			template<class InputIterator>
			void assign( InputIterator first,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last ) {
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_vec + i);
				this->_alloc.deallocate(this->_vec, this->_size);
				this->_size = ft::distance(first, last);
				if (this->_capacity < this->_size)
					this->_capacity = this->_size;
				this->_vec = this->_alloc.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(this->_vec + i, *(first + i));
			}

			void assign( size_type n, const value_type & val ) {
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_vec + i);
				this->_alloc.deallocate(this->_vec, this->_size);
				this->_size = n;
				if (this->_capacity < this->_size)
					this->_capacity = this->_size;
				this->_vec = this->_alloc.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(this->_vec + i, val);
			}

			void push_back( const value_type & val ) {
				if (this->_capacity == this->_size)
					reserve(this->_capacity ? this->_capacity * 2 : 10);
				this->_alloc.construct(&(*this->end()), val);
				this->_size++;
			}

			void pop_back( void ) {
				if (this->_size <= 0)
					return ;
				this->_alloc.destroy(&(*this->end()));
				this->_size--;
			}

			iterator insert( iterator position, const value_type & val ) {
				size_type index = position - this->begin();
				if (this->_size == this->_capacity)
					reserve(this->_capacity ? this->_capacity * 2 : 1);
				for (size_type i = this->_size; i > index; i--)
					this->_alloc.construct(&(*this->begin()) + i, *(begin() + i - 1));
				this->_alloc.construct(&(*this->begin()) + index, val);
				this->_size++;
				return this->begin() + index;
			}

			void insert( iterator position, size_type n, const value_type & val ) {
				if (n) {
					size_type index = position - this->begin();
					if (this->_size + n > this->_capacity)
						reserve(this->_capacity ? (this->_size + n) * 2 : n);
					while (n--)
						insert(this->begin() + index, val);
					this->_size += n;
				}
			}

			template<class InputIterator>
			void insert( iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
						InputIterator last ) {
				size_type index = position - this->begin();
				size_type n = ft::distance(first, last);
				if (this->_size + n > this->_capacity)
					reserve(this->_capacity ? (this->_size + n) * 2 : n);
				for (size_type i = this->_size; i > index; i--)
					this->_alloc.construct(&(*this->begin()) + i + n - 1, *(begin() + i - 1));
				for (size_type  i = 0; i < n; i++)
					this->_alloc.construct(&(*begin()) + index + i, *(first + i));
				this->_size += n;
			}

			iterator erase( iterator position ) {
				this->_alloc.destroy(&(*position));
				iterator iter = position;
				while (iter != (this->end())) {
					this->_alloc.construct(&(*iter), *(iter + 1));
					iter++;
				}
				this->_size--;
				return position;
			}

			iterator erase( iterator first, iterator last ) {
				size_type n = ft::distance(first, last);
				for (size_type i = 0; (last + i) != this->end(); i++)
				{
					this->_alloc.destroy(&(*(first + i)));
					this->_alloc.construct(&(*(first + i)), *(last + i));
				}
				this->_size -= n;
				return first;
			}

			void swap( vector & x ) {
				size_type	tmp_size = x._size;
				size_type	tmp_capacity = x._capacity;
				pointer		tmp_vec = x._vec;

				x._size = this->_size;
				x._capacity = this->_capacity;
				x._vec = this->_vec;

				this->_size = tmp_size;
				this->_capacity = tmp_capacity;
				this->_vec  = tmp_vec;
			}

			void clear( void ) {
				for (iterator it = this->begin(); it != this->end(); it++)
					this->_alloc.destroy(&(*it));
				this->_size = 0;
			}

			allocator_type get_allocator( void ) const {
				return this->_alloc;
			}

		private:

			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;
			pointer			_vec;
	};

	template<class T, class Alloc>
	void swap( vector<T, Alloc> & lhs, vector<T, Alloc> & rhs ) {
		lhs.swap(rhs);
	}

	template<class T, class Alloc>
	bool operator==( const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal( lhs.begin(), lhs.end(), rhs.begin() );
	}

	template<class T, class Alloc>
	bool operator!=( const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs ) {
		return !(lhs == rhs);
	}

	template<class T, class Alloc>
	bool operator<( const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class T, class Alloc>
	bool operator>( const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs ) {
		return rhs < lhs;
	}

	template<class T, class Alloc>
	bool operator<=( const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs ) {
		return !(rhs < lhs);
	}

	template<class T, class Alloc>
	bool operator>=( const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs ) {
		return !(lhs < rhs);
	}

} // namespace ft


#endif