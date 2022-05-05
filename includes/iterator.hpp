#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

namespace ft {

	/**
	 * Iterator Tags
	 */
	/// Marking input iterators.
	struct input_iterator_tag { };

	/// Marking output iterators.
	struct output_iterator_tag { };

	/// Forward iterators support a superset of input iterator operations.
	struct forward_iterator_tag : public input_iterator_tag { };

	/// Bidirectional iterators support a superset of forward iterator operations.
	struct bidirectional_iterator_tag : public forward_iterator_tag { };

	/// Ramdom-access iterators support a superset of bidirectional iterator operations.
	struct random_access_iterator_tag : public bidirectional_iterator_tag { }; 

	/**
	 * Iterator base class 
	 */
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	/**
	 * Iterator Traits
	 */
	template <typename Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;

	};

	/**
	 * Iterator Traits specialization for pointer types.
	 */
	template <typename T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	/**
	 * Iterator Traits specialization for const pointer types.
	 */
	template <typename T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
	};

	/**
	 * Random Access Iterator implementation
	 */

	template<typename Iterator>
	class random_access_iterator
	: public iterator<  typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iterator_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference>
	{
		protected:
			Iterator				current;

			typedef iterator_traits<Iterator>	_traits_type;
		
		public:

			typedef Iterator									iterator_type;
			typedef typename _traits_type::iterator_category	iterator_category;
			typedef typename _traits_type::value_type			value_type;
			typedef typename _traits_type::difference_type		difference_type;
			typedef typename _traits_type::pointer				pointer;
			typedef typename _traits_type::reference			reference;

			/**
			 * Random Access Iterator 
			 * Members Functions and overloads
			 * Constructors, base, operator( *, +, ++,, +=, -, --, -=, ->, [])
			 */
			random_access_iterator( void ) : current( ) { }
			explicit random_access_iterator( iterator_type it ) : current( it ) { }
			template<typename Iter>
			random_access_iterator( const random_access_iterator<Iter> & it ) : current( it.current ) { }

			iterator_type base( void ) const { return current; }

			reference operator*( void ) const {
				return *current;
			}

			pointer operator->( void ) const {
				return &(operator*());
			}

			random_access_iterator & operator++( void ) {
				current++;
				return *this;
			}

			random_access_iterator & operator++( int ) {
				current++;
				return *this;
			}

			random_access_iterator & operator--( void ) {
				current--;
				return *this;
			}

			random_access_iterator & operator--( int ) {
				current--;
				return *this;
			}

			random_access_iterator operator+( difference_type n ) const {
				return random_access_iterator( current + n );
			}

			random_access_iterator & operator+=( difference_type n ) {
				current += n;
				return *this;
			}

			random_access_iterator operator-( difference_type n ) const {
				return random_access_iterator( current - n );
			}

			random_access_iterator & operator-=( difference_type n ) const {
				current -= n;
				return *this;
			}

			reference operator[]( difference_type n ) const {
				return current[n];
			}
	};

	/**
	 * Random access Iterator
	 * Non members functions and relational operatorsoverload
	 * (+, -, ==, !=, <, <=,, > >=)
	 */

	template<typename Iterator>
	random_access_iterator<Iterator> operator+( typename random_access_iterator<Iterator>::difference_type n,
											const random_access_iterator<Iterator>& it ) {
		return random_access_iterator<Iterator>( it.base() - n );
	}

	template<typename Iterator>
	typename random_access_iterator<Iterator>::difference_type operator-( const random_access_iterator<Iterator>& lhs,
											const random_access_iterator<Iterator>& rhs ) {
		return ( rhs.base() - lhs.base() );
	}

	template<typename Iterator>
	bool operator==( const random_access_iterator<Iterator> & lhs, const random_access_iterator<Iterator> & rhs ) {
		return ( lhs.base() == rhs.base() );
	}

	template<typename Iterator>
	bool operator!=( const random_access_iterator<Iterator> & lhs, const random_access_iterator<Iterator> & rhs ) {
		return ( lhs.base() != rhs.base() );
	}

	template<typename Iterator>
	bool operator<( const random_access_iterator<Iterator> & lhs, const random_access_iterator<Iterator> & rhs ) {
		return ( lhs.base() < rhs.base() );
	}

	template<typename Iterator>
	bool operator<=( const random_access_iterator<Iterator> & lhs, const random_access_iterator<Iterator> & rhs ) {
		return ( lhs.base() <= rhs.base() );
	}

	template<typename Iterator>
	bool operator>( const random_access_iterator<Iterator> & lhs, const random_access_iterator<Iterator> & rhs ) {
		return ( lhs.base() > rhs.base() );
	}

	template<typename Iterator>
	bool operator>=( const random_access_iterator<Iterator> & lhs, const random_access_iterator<Iterator> & rhs ) {
		return ( lhs.base() >= rhs.base() );
	}

} // namespace ft

#endif
