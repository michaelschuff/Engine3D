//
//  matrix.hpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/18/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>
#include <vector>
#include <boost/type_index.hpp>
#include <algorithm>
#include <math.h>
#include "vector2.hpp"
#include "vector3.hpp"



template <typename T>
class matrix {
public:
    static matrix<T> identity(const unsigned int& n);
    
    
private:
    unsigned long m_rows, m_columns;
    std::vector<std::vector<T>> data;
    
public:
    matrix(const unsigned int& t_rows = 0,
           const unsigned int& t_columns = 0);
    matrix(const unsigned int& t_rows,
           const unsigned int& t_columns,
           const T& k);
    matrix(const std::vector<std::vector<T>>&);
    matrix(const std::vector<T>&);
    
    
    unsigned int rows() const;
    unsigned int columns() const;
    unsigned int deep_rows() const;
    unsigned int deep_columns() const;
    
    
    void set_row(const std::vector<T>&, unsigned int&);
    template<typename T1>
    void set_row(const std::vector<T1>&, unsigned int&);
    void set_column(const std::vector<T>&, unsigned int&);
    template<typename T1>
    void set_column(const std::vector<T1>&, unsigned int&);
    void set_submatrix(const matrix<T>&, unsigned int&, unsigned int&);
    template<typename T1>
    void set_submatrix(const matrix<T1>&, unsigned int&, unsigned int&);
    
    void clear();
    void fill(const T&);
    template<typename T1>
    void fill(const T1&);
    
    
    void transpose();
    void raise_to(const T& k);
    template<typename T1>
    void raise_to(const T1& k);
    
    matrix<T> transposed() const;
    matrix<T> raised_to(const T& k) const;
    template<typename T1>
    matrix<T> raised_to(const T1& k) const;
    
    T determinant() const;
    matrix<T> submatrix(const unsigned int& excluded_row,
                        const unsigned int& excluded_column);
    matrix<T> submatrix(const std::vector<unsigned int>& excluded_rows,
                        const std::vector<unsigned int>& excluded_columns);
    
    std::string to_string() const;
    void print() const;
    
    
    
    T& operator()(const unsigned int& i, const unsigned int& j);
    const T& operator()(const unsigned int& i, const unsigned int& j) const;
    
    matrix<T>& operator+=(const matrix<T>& m);
    template<typename T1>
    matrix<T>& operator+=(const matrix<T1>& m);
    matrix<T>& operator+=(const T& k);
    template<typename T1>
    matrix<T>& operator+=(const T1& k);
    
    matrix<T>& operator-=(const matrix<T>& m);
    template<typename T1>
    matrix<T>& operator-=(const matrix<T1>& m);
    matrix<T>& operator-=(const T& k);
    template<typename T1>
    matrix<T>& operator-=(const T1& k);
    
    matrix<T>& operator*=(const matrix<T>& m);
    template<typename T1>
    matrix<T>& operator*=(const matrix<T1>& m);
    matrix<T>& operator*=(const T& k);
    template<typename T1>
    matrix<T>& operator*=(const T1& k);
    
    matrix<T>& operator/=(const T& k);
    template<typename T1>
    matrix<T>& operator/=(const T1& k);
    
    matrix<T>& operator%=(const matrix<T>& m);
    template<typename T1>
    matrix<T>& operator%=(const matrix<T1>& m);
    matrix<T>& operator%=(const T& k);
    template<typename T1>
    matrix<T>& operator%=(const T1& k);
    
    matrix<T>& operator=(const matrix<T>& m);
    
    operator float() const;
};

template <typename T>
matrix<T> operator+(const matrix<T>& m1, const matrix<T>& m2);
template <typename T1, typename T2>
matrix<T1> operator+(const matrix<T1>& m1, const matrix<T2>& m2);


template <typename T>
matrix<T> operator+(const matrix<T>& m, const T& k);
template <typename T1, typename T2>
matrix<T1> operator+(const matrix<T1>& m, const T2& k);
template <typename T>
matrix<T> operator+(const T& k, const matrix<T>& m);
template <typename T1, typename T2>
matrix<T1> operator+(const T1& k, const matrix<T2>& m);


template <typename T>
matrix<T> operator-(const matrix<T>& m);

template <typename T>
matrix<T> operator-(const matrix<T>& m1, const matrix<T>& m2);
template <typename T1, typename T2>
matrix<T1> operator-(const matrix<T1>& m1, const matrix<T2>& m2);
template <typename T>
matrix<T> operator-(const matrix<T>& m, const T& k);
template <typename T1, typename T2>
matrix<T1> operator-(const matrix<T1>& m, const T2& k);
template <typename T>
matrix<T> operator-(const T& k, const matrix<T>& m);
template <typename T1, typename T2>
matrix<T1> operator-(const T1& k, const matrix<T2>& m);


template <typename T>
matrix<T> operator*(const T& k, const matrix<T>& m);
template <typename T1, typename T2>
matrix<T1> operator*(const T1& k, const matrix<T2>& m);
template <typename T>
matrix<T> operator*(const matrix<T>& m, const T& k);
template <typename T1, typename T2>
matrix<T1> operator*(const matrix<T1>& m, const T2& k);
template <typename T>
matrix<T> operator*(const matrix<T>& m1, const matrix<T>& m2);
template <typename T1, typename T2>
matrix<T1> operator*(const matrix<T1>& m1, const matrix<T2>& m2);

template <typename T>
matrix<T> operator/(const matrix<T>& m, const T& k);
template <typename T1, typename T2>
matrix<T1> operator/(const matrix<T1>& m, const T2& k);
template <typename T>
matrix<T> operator/(const T& k, const matrix<T>& m);
template <typename T1, typename T2>
matrix<T1> operator/(const T2& k, const matrix<T1>& m);

template <typename T>
matrix<T> operator%(const matrix<T>& m, const T& k);
template <typename T1, typename T2>
matrix<T1> operator%(const matrix<T1>& m, const T2& k);
template <typename T>
matrix<T> operator%(const matrix<T>& m1, const matrix<T>& m2);
template <typename T1, typename T2>
matrix<T1> operator%(const matrix<T1>& m1, const matrix<T2>& m2);
template <typename T>
bool operator==(const matrix<T>& m1, const matrix<T>& m2);
template <typename T1, typename T2>
bool operator==(const matrix<T1>& m1, const matrix<T2>& m2);
template <typename T>
bool operator!=(const matrix<T>& m1, const matrix<T>& m2);
template <typename T1, typename T2>
bool operator!=(const matrix<T1>& m1, const matrix<T2>& m2);

template <typename T>
matrix<T> pow(const matrix<T>& m, const T& k);
template <typename T1, typename T2>
matrix<T1> pow(const matrix<T1>& m, const T2& k);


template <typename T>
T modulo(const T&, const T&);
template <typename T1, typename T2>
T1 modulo(const T1&, const T2&);

template <typename T>
matrix<T> modulo(const matrix<T>&, const T&);
template <typename T1, typename T2>
matrix<T1> modulo(const matrix<T1>&, const T2&);

template <typename T>
matrix<T> modulo(const matrix<T>&, const matrix<T>&);
template <typename T1, typename T2>
matrix<T1> modulo(const matrix<T1>&, const matrix<T2>&);

template<typename T>
struct mat_val_type : public std::false_type {
    static T type;
};

template<typename T>
struct mat_val_type<matrix<T>> : public std::true_type {
    static T type;
};


#include "matrix.cpp"

#endif /* matrix_hpp */
