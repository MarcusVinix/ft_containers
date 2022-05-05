#ifndef TYPES_TRAITS_HPP
# define TYPES_TRAITS_HPP

namespace ft
{
	// SFINAE - Substitution Failure Is Not An Error
	// https://en.cppreference.com/w/cpp/language/sfinae
	// https://stackoverflow.com/questions/982808/c-sfinae-examples
	
	/**enable if
	*/
	template<bool, typename T = void>
	struct enable_if { };

	template<typename T>
	struct enable_if<true, T> { typedef T type; };

	/**
	 * is_integral
	 * integral_constat
	 * https://www.cplusplus.com/reference/type_traits/integral_constant/
	 */
	template <class T, T v>
	struct integral_constant {
		static const T					value = v;
		typedef T						value_type;
		typedef integral_constant<T, v>	type;

		operator const T() { return v; }
	};

	template<typename T>
	struct is_integral : public integral_constant<bool, false> { };

	// bool, char, char16_t, char32_t, wchar_t, signed char, short int, 
	// int, long int, long long int, unsigned char, unsigned short int, 
	// unsigned int, unsigned long int, unsigned long long int
	// http://www.cplusplus.com/reference/type_traits/is_integral/?kw=is_integral
	template<>
	struct is_integral<bool> : public integral_constant<bool, true> { };

	template<>
	struct is_integral<char> : public integral_constant<bool, true> { };

	// Can't compile with the flag -std=c++98
	// template<>
	// struct is_integral<char16_t> : public integral_constant<bool, true> { };
	//
	// template<>
	// struct is_integral<char32_t> : public integral_constant<bool, true> { };

	template<>
	struct is_integral<wchar_t> : public integral_constant<bool, true> { };

	template<>
	struct is_integral<signed char> : public integral_constant<bool, true> { };

	template<>
	struct is_integral<short int> : public integral_constant<bool, true> { };

	template<>
	struct is_integral<int> : public integral_constant<bool, true> { };

	template<>
	struct is_integral<long int> : public integral_constant<bool, true> { };

	template<>
	struct is_integral<long long int> : public integral_constant<bool, true> { };

	template<>
	struct is_integral<unsigned char> : public integral_constant<bool, true> { };

	template<>
	struct is_integral<unsigned short int> : public integral_constant<bool, true> { };

	template<>
	struct is_integral<unsigned int> : public integral_constant<bool, true> { };

	template<>
	struct is_integral<unsigned long int> : public integral_constant<bool, true> { };

	template<>
	struct is_integral<unsigned long long int> : public integral_constant<bool, true> { };

} // namespace ft


#endif
