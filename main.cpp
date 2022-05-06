#include <reverse_iterator.hpp>     // std::reverse_iterator
#include <iterator.hpp>
#include <types_traits.hpp>
#include <algorithm.hpp>



// pair relational operators
#include <utility.hpp>      // std::pair
#include <iostream>     // std::cout

int main ()
{
  ft::pair<int,char> foo (10,'z');
  ft::pair<int,char> bar (90,'a');

  if (foo==bar) std::cout << "foo and bar are equal\n";
  if (foo!=bar) std::cout << "foo and bar are not equal\n";
  if (foo< bar) std::cout << "foo is less than bar\n";
  if (foo> bar) std::cout << "foo is greater than bar\n";
  if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

  ft::pair <std::string,double> product1;                     // default constructor
  ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
  // ft::pair <std::string,double> product3 (product2);          // copy constructor

  product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

  product2.first = "shoes";                  // the type of first is string
  product2.second = 39.90;                   // the type of second is double

  std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
  std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
  // std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';
  return 0;

  return 0;
}