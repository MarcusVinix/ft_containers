#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{

	template< class T, class Container = ft::vector<T> >
	class stack {

		private:
			Container c;
		
		public:
			typedef typename Container::value_type		value_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;
			typedef typename Container::size_type		size_type;
			typedef Container							container_type;

			template<typename T1, typename Container1>
			friend bool operator==( const stack<T1, Container1> & lhs, const stack<T1, Container1> & rhs );

			template<typename T1, typename Container1>
			friend bool operator<( const stack<T1, Container1> & lhs, const stack<T1, Container1> & rhs );

			explicit stack( const container_type & ctnr = container_type() ) : c( ctnr ) { }

			bool empty( void ) const {
				return c.empty();
			}

			size_type size( void ) const {
				return c.size();
			}

			reference top( void ) {
				return c.back();
			}

			const_reference top( void ) const {
				return c.back();
			}

			void push( const value_type & val ) {
				c.push_back(val);
			}

			void pop( void ) {
				c.pop_back();
			}

	};

	template<class T, class Container>
	bool operator==( const stack<T, Container> & lhs, const stack<T, Container> & rhs ) {
		return lhs.c == rhs.c;
	}

	template<class T, class Container>
	bool operator!=( const stack<T, Container> & lhs, const stack<T, Container> & rhs ) {
		return !( rhs == lhs );
	}

	template<class T, class Container>
	bool operator<( const stack<T, Container> & lhs, const stack<T, Container> & rhs ) {
		return lhs.c < rhs.c;
	}
	template<class T, class Container>
	bool operator<=( const stack<T, Container> & lhs, const stack<T, Container> & rhs ) {
		return !(rhs < lhs);
	}
	template<class T, class Container>
	bool operator>( const stack<T, Container> & lhs, const stack<T, Container> & rhs ) {
		return rhs < lhs;
	}
	template<class T, class Container>
	bool operator>=( const stack<T, Container> & lhs, const stack<T, Container> & rhs ) {
		return !(lhs < rhs);
	}

} // namespace ft

#endif