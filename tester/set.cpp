#ifdef FT
# include "set.hpp"
# define ns ft
#else
# include <set>
# define ns std
#endif

#include <list>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#define _pair ns::pair


template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "value: " << *iterator;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_SET>
void	printSize(T_SET const &st, bool print_content = 1)
{
	std::cout << "size: " << st.size() << std::endl;
	std::cout << "max_size: " << st.max_size() << std::endl;
	if (print_content)
	{
		typename T_SET::const_iterator it = st.begin(), ite = st.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T1>
void	printReverse(ns::set<T1> &st)
{
	typename ns::set<T1>::iterator it = st.end(), ite = st.begin();

	std::cout << "printReverse:" << std::endl;
	while (it-- != ite)
		std::cout << "-> " << printPair(it, false) << std::endl;
	std::cout << "_______________________________________________" << std::endl;
}
template <class T>
void	is_empty(T const &st)
{
	std::cout << "is_empty: " << st.empty() << std::endl;
}
#define T1 int

typedef ns::set<T1>::iterator ft_iterator;
typedef ns::set<T1>::const_iterator ft_const_iterator;

template <typename set, typename U, typename V>
void	ft_erase(set &st, U param, V param2, int &iter)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	st.erase(param, param2);
	printSize(st);
}

template <typename set, typename U>
void	ft_erase(set &st, U param,int &iter)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	st.erase(param);
	printSize(st);
}

template <class T>
void	print(ns::set<T>& lst)
{
	for (typename ns::set<T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << it->first << " => " << it->second << '\n';
}


int main() {




{
    	std::list<T1> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(lst_size - i);

	ns::set<T1> st(lst.begin(), lst.end());
	ns::set<T1>::iterator it = st.begin(), ite = st.end();

	ns::set<T1> st_range(it, --(--ite));
	for (int i = 0; i < 5; ++i)
		st.insert(i * 5);

	it = st.begin(); ite = --(--st.end());
	ns::set<T1> st_copy(st);
	for (int i = 0; i < 7; ++i)
		st.insert(i * 7);

	std::cout << "\t-- PART ONE --" << std::endl;
	printSize(st);
	printSize(st_range);
	printSize(st_copy);

	st = st_copy;
	st_copy = st_range;
	st_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSize(st);
	printSize(st_range);
	printSize(st_copy);
}


{
	std::list<T1> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back('a' + i);

	ns::set<T1> st(lst.begin(), lst.end()), st2;
	ns::set<T1>::iterator it;

	lst.clear();
	is_empty(st);
	printSize(st);

	is_empty(st2);
	st2 = st;
	is_empty(st2);

	it = st.begin();
	for (unsigned long int i = 3; i < 6; ++i)
		st.insert(i * 7);

	printSize(st);
	printSize(st2);

	st2.clear();
	is_empty(st2);
	printSize(st2);
}

{
	int iter = 0;
	std::list<T1> lst;
	unsigned int lst_size = 6;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(i);
	ns::set<T1> st(lst.begin(), lst.end());
	printSize(st);

	for (int i = 2; i < 4; ++i)
		ft_erase(st, i, iter);

	ft_erase(st, *st.begin(), iter);
	ft_erase(st, *(--st.end()), iter);

	st.insert(-1);
	st.insert(10);
	st.insert(10);
	printSize(st);

	ft_erase(st, 0, iter);
	ft_erase(st, 1, iter);
	printSize(st);

}



{
  ns::set<int> myset;

  myset.insert(20);
  myset.insert(30);
  myset.insert(10);

  std::cout << "myset contains:";
  while (!myset.empty())
  {
     std::cout << ' ' << *myset.begin();
     myset.erase(myset.begin());
  }
  std::cout << '\n';

}

{
  int myints[] = {75,23,65,42,13};
	return (0);
  ns::set<int> myset (myints,myints+5);

  std::cout << "myset contains:";
  for (ns::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

}

{
  ns::set<int> myset;

  for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50

  ns::pair<ns::set<int>::const_iterator,ns::set<int>::const_iterator> ret;
  ret = myset.equal_range(30);

  std::cout << "the lower bound points to: " << *ret.first << '\n';
  std::cout << "the upper bound points to: " << *ret.second << '\n';

}
{
  ns::set<int> myset;
  ns::set<int>::iterator it;

  // ns::set some initial values:
  for (int i=1; i<=5; i++) myset.insert(i*10);    // ns::set: 10 20 30 40 50

  it=myset.find(20);
  myset.erase (it);
  myset.erase (myset.find(40));

  std::cout << "myset contains:";
  for (it=myset.begin(); it!=myset.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

}
{
  ns::set<int> myset;
  ns::set<int>::iterator it;
  ns::pair<ns::set<int>::iterator,bool> ret;

  // ns::set some initial values:
  for (int i=1; i<=5; ++i) myset.insert(i*10);    // ns::set: 10 20 30 40 50

  ret = myset.insert(20);               // no new element inserted

  if (ret.second==false) it=ret.first;  // "it" now points to element 20

  myset.insert (it,25);                 // max efficiency inserting
  myset.insert (it,24);                 // max efficiency inserting
  myset.insert (it,26);                 // no max efficiency inserting

  int myints[]= {5,10,15};              // 10 already in ns::set, not inserted
  myset.insert (myints,myints+3);

  std::cout << "myset contains:";
  for (it=myset.begin(); it!=myset.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

}
{
  ns::set<int> myset;
  ns::set<int>::iterator itlow,itup;

  for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

  itlow=myset.lower_bound (30);                //       ^
  itup=myset.upper_bound (60);                 //                   ^

  myset.erase(itlow,itup);                     // 10 20 70 80 90

  std::cout << "myset contains:";
  for (ns::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

}

{
  int myints[] = {21,64,17,78,49};
  ns::set<int> myset (myints,myints+5);

  ns::set<int>::reverse_iterator rit;

  std::cout << "myset contains:";
  for (rit=myset.rbegin(); rit != myset.rend(); ++rit)
    std::cout << ' ' << *rit;

  std::cout << '\n';

}
{
  ns::set<int> foo,bar;
  foo.insert(10);
  bar.insert(20);
  bar.insert(30);
  foo.insert(40);

  // foo ({10,40}) vs bar ({20,30}):
  if (foo==bar) std::cout << "foo and bar are equal\n";
  if (foo!=bar) std::cout << "foo and bar are not equal\n";
  if (foo< bar) std::cout << "foo is less than bar\n";
  if (foo> bar) std::cout << "foo is greater than bar\n";
  if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  if (foo>=bar) std::cout << "foo is gns::setreater than or equal to bar\n";

}
{
  int myints[] = {21,64,17,78,49};
  ns::set<int> myset (myints,myints+5);

  ns::set<int>::reverse_iterator rit;

  std::cout << "myset contains:";
  for (rit=myset.rbegin(); rit != myset.rend(); ++rit)
    std::cout << ' ' << *rit;

  std::cout << '\n';

}
{
  ns::set<int> myset;
  ns::set<int>::iterator itlow,itup;

  for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

  itlow=myset.lower_bound (30);                //       ^
  itup=myset.upper_bound (60);                 //                   ^

  myset.erase(itlow,itup);                     // 10 20 70 80 90

  std::cout << "myset contains:";
  for (ns::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

}




}
