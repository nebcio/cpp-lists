#pragma once
#include <iostream>
#include <vector>

#ifndef wektor_h
#define wektor_h
template<typename T, size_t size, T val = 0>
class wektor {
    std::vector<T> c;
public:

    typedef T value_type;
    wektor() {
        for (int i = 0; i < size; i++) {
            c.push_back(val);                 
        }
    }

    T& operator[] (int value) {
        return c[value];
    }
    // dla T jest napisayny operator =
    wektor& operator= (wektor& rhs) {
        *this = rhs;
        return this;
    }

    friend std::ostream& operator<<(std::ostream& out, wektor<T, size, val>& wektor) {
        for (const auto& e : wektor.c) out << e << " ";
        return out;
    }
};

template<typename T, size_t size, T val = 0>
T operator* (wektor<T, size, val>& lhs, std::vector<T>& rhs) {
    T sum = 0;
    if (rhs.size() >= size)
        for (size_t i = 0; i < size; i++)
            sum += lhs[i] * rhs[i];
    else if (size >= rhs.size())
        for (size_t i = 0; i < rhs.size(); i++)
            sum += lhs[i] * rhs[i];

    return sum;
}

template<typename T, size_t size, T val = 0, typename T2>
auto operator* (wektor<T, size, val>& lhs, std::vector<T2>& rhs) {
    decltype(lhs[0] * rhs[0]) sum = 0;
    if (rhs.size() >= size)
        for (size_t i = 0; i < size; i++)
            sum += lhs[i] * rhs[i];
    else if (size >= rhs.size())
        for (size_t i = 0; i < rhs.size(); i++)
            sum += lhs[i] * rhs[i];

    return sum;
}
#endif // !