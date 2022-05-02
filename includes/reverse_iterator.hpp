#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{

	template<typename Iterator>
	class reverse_iterator
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
			 * Reverse Iterator 
			 * Members Functions and overloads
			 * Constructors, base, operator( *, +, ++,, +=, -, --, -=, ->, [])
			 */
			reverse_iterator( void ) : current( ) { }
			explicit reverse_iterator( iterator_type it ) : current( it ) { }
			template<typename Iter>
			reverse_iterator( const reverse_iterator<Iter> & rev_it ) : current( rev_it.current ) { }

			iterator_type base( void ) const { return current; }

			reference operator*( void ) const {
				Iterator tmp = current;
				return *--tmp;
			}
	
			pointer operator->( void ) const {
				return &(operator*());
			}

			reverse_iterator& operator++( void ) {
				--current;
				return *this;
			}

			reverse_iterator operator++( int ) {
				reverse_iterator tmp = *this;
				--current;
				return tmp;
			}

			reverse_iterator& operator--( void ) {
				++current;
				return *this;
			}

			reverse_iterator operator--( int ) {
				reverse_iterator tmp = *this;
				++current;
				return tmp;
			}

			reverse_iterator operator+( difference_type n ) const {
				return reverse_iterator( current - n);
			}

			reverse_iterator& operator+=( difference_type n ) {
				current -= n;
				return *this;
			}

			reverse_iterator operator-( difference_type n ) const {
				return reverse_iterator( current + n );
			}

			reverse_iterator& operator-=( difference_type n ) {
				current += n;
				return *this;
			}

			reference operator[]( difference_type n ) const {
				return *( *this + n );
			}

	};

	/**
	 * Reverse Iterator
	 * Non members functions and relational operatorsoverload
	 * (+, -, ==, !=, <, <=,, > >=)
	 */
	template<typename Iterator>
	reverse_iterator<Iterator> operator+( typename reverse_iterator<Iterator>::difference_type n,
											const reverse_iterator<Iterator>& rev_it ) {
		return reverse_iterator<Iterator>(rev_it.base() - n);
	}

	template<typename Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& lhs,
																	const reverse_iterator<Iterator>& rhs) {
		return ( rhs.base() - lhs.base() );
	}

	template<typename Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return ( lhs.base() == rhs.base() );
	}

	template<typename Iterator>
	bool operator!=( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs ) {
		return ( lhs.base() != rhs.base() );
	}

	template<typename Iterator>
	bool operator<( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs ) {
		return ( lhs.base() < rhs.base() );
	}
	
	template<typename Iterator>
	bool operator<=( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs ) {
		return ( lhs.base() <= rhs.base() );
	}

	template<typename Iterator>
	bool operator>( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs ) {
		return ( lhs.base() > rhs.base() );
	}

	template<typename Iterator>
	bool operator>=( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs ) {
		return ( lhs.base() >= rhs.base() );
	}

} // namespace ft

#endif
