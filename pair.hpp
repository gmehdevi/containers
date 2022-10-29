#ifndef PAIR_H
#define PAIR_H
namespace ft
{
    template <class T1 , class T2>
    struct pair
    {
        T1 first;
        T2 second;

        pair()
        : first(T1()), second(T2()) {}
		
        pair(const T1 &a, const T2 &b)
        : first(a), second(b) {}
		
        template<typename U1, typename U2>
		pair(const pair<U1,U2> &other)
        :first((other.first)), second((other.second)) {}

		pair &operator=(const pair &other) {
			first = other.first;
			second = other.second;
			return *this;
		}
        
        operator pair<const T1, const T2>() const {
			return pair<const T1,const T2> (first, second);
		}
    };

    template <typename T1, typename T2>
    bool operator == (const pair<T1, T2> l, const pair<T1, T2> r)
    {
        return ((l.fisrt == r.first && l.second == r.second));
    }
    template <typename T1, typename T2>
    bool operator != (const pair<T1, T2> l, const pair<T1, T2> r)
    {
        return ((l.fisrt != r.first || l.second != r.second));
    }
    template <typename T1, typename T2>
    bool operator <  (const pair<T1, T2> l, const pair<T1, T2> r)
    {
        if (l.fisrt == r.first)
            return ((l.second < r.second));
        return ((l.fisrt < r.first));
    }
    template <typename T1, typename T2>
    bool operator <= (const pair<T1, T2> l, const pair<T1, T2> r)
    {
        if (l.fisrt == r.first)
            return ((l.second <= r.second));
        return ((l.fisrt <= r.first));
    }
    template <typename T1, typename T2>
    bool operator >  (const pair<T1, T2> l, const pair<T1, T2> r)
    {
        if (l.fisrt == r.first)
            return ((l.second > r.second));
        return ((l.fisrt > r.first));
    }
    template <typename T1, typename T2>
    bool operator >= (const pair<T1, T2> l, const pair<T1, T2> r)
    {
        if (l.fisrt == r.first)
            return ((l.second >= r.second));
        return ((l.fisrt >= r.first));
    }
	template<typename T1, typename T2>
	void swap(pair<T1,T2> &x, pair<T1,T2> &y) {
		swap(x.first, y.first);
		swap(x.second, y.second);
	}

	template<typename T1, typename T2>
	pair<T1, T2> make_pair(T1 x, T2 y) {
		return pair<T1, T2>(x, y);
	}
}

#endif 