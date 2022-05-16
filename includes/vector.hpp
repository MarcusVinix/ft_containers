#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "iterator.hpp"
#include "reverse_iterator.hpp"

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
			typedef ft::random_access_iterator<value_type>					iterator;
			typedef ft::random_access_iterator<const value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef typename std::size_t									size_type;

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
			vector( InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type() )
				: _size( last - first ), _capacity( _size ), _alloc( alloc ), _vec( _alloc.allocate(_size) ) {
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.construct(this->_vec + i, *(first + i));
			}

			//copy constructor
			vector( const vector & x ) : _size( x._size ), _capacity( x._capacity ), _alloc( x._alloc ), _vec( _size ) {
				for(size_type i = 0; i < this->_size; i++)
					this->_alloc.constructor(this->_vec + i, x._vec[i]);
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
				return iterator(this->_vec + this->_size);
			}

			const_iterator end( void ) const {
				return const_iterator(this->_vec + this->_size);
			}

			reverse_iterator rbegin( void ) {
				return reverse_iterator(--this->end());
			}

			const_reverse_iterator rbegin( void ) const {
				return const_reverse_iterator(--this->end());
			}

			reverse_iterator rend( void ) {
				return reverse_iterator(--this->begin());
			}

			const_reverse_iterator rend( void ) const {
				return const_reverse_iterator(--this->begin());
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
				if (n > this->_size)
					insert(this->end(), n - this->_size, val);
				else if (n < this->_size)
					erase(this->begin() + n, this->end());
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
				if (n > this->_capacity) {
					this->_capacity = n;
					pointer tmp = this->_alloc.allocate(this->_capacity);
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.construct(tmp + i, this->_vec[i]);
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_vec + i);
					this->_alloc.deallocate(this->_vec, this->_size);
					this->_vec = tmp;
				}
			}

			reference operator[]( size_type n ) {
				return this->_vec[n];
			}

			const_reference operator[]( size_type n ) const {
				return this->_vec[n];
			}

			reference at( size_type n ) {
				if (n >= this->_size)
					std::out_of_range("ft::vector::at is out of range");
				return this->_vec[n];
			}

			const_reference at( size_type n ) const {
				if (n >= this->_size)
					std::out_of_range("ft::vector::at is out of range");
				return this->_vec[n];
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
			void assign( void ) {

			}

			void clear( void ) {

			}
		private:

			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;
			pointer			_vec;
	};

} // namespace ft


#endif