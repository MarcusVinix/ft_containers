#ifndef FUNCTIONAL_HPP
# define FUNCTIONAL_HPP

namespace ft {

	template <class Arg, class Result>
	struct unary_function {
		typedef Arg argument_type;
		typedef Result result_type;
	};

	template <class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	template <class T>
	struct less : binary_function<T, T, bool> {
		bool operator()( const T &x, const T &y ) const {
			return x < y;
		}
	};

	template <class Pair>
	struct select1st : public unary_function<Pair, typename Pair::first_type> {
		typename Pair::first_type &operator()(Pair &x) const {
			return x.first;
		}
		const typename Pair::first_type &operator()(const Pair &x) const {
			return x.first;
		}
	};



}

#endif