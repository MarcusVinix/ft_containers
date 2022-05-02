#ifndef TYPES_TRAITS_HPP
# define TYPES_TRAITS_HPP

namespace ft
{
	
	/**enable if
	*/
	template<bool, typename T = void>
	struct enable_if { };

	template<typename T>
	struct enable_if<true, T> { typedef T type; };


} // namespace ft


#endif
