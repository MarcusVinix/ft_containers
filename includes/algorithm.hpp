#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{

	/**
	 *  Function template Equal.
	 *  Test whether the elements in two ranges are equal
	 * https://www.cplusplus.com/reference/algorithm/equal/
	 */
	template<class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		while (first1 != last1) {
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	template<class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred ) {
		while (first1 != last1) {
			if (!pred(*first1, *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	/**
	 * Function template Lexicographical_compare
	 * Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
	 * A lexicographical comparison is the kind of comparison generally used to sort words alphabetically in dictionaries
	 * https://www.cplusplus.com/reference/algorithm/lexicographical_compare/
	 * return true if the first range is lexicographically less than the second
	 * 
	 */
	template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2 ) {
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	/**
	 * https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
	 * The signature of the comparison function should be equivalent to the following:
	 * bool cmp(const Type1 &a, const Type2 &b);
	 */
	template<class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp ) {
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

} // namespace ft


#endif
