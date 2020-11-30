//
//  matrix.cpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/18/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "matrix.hpp"

template <typename T>
matrix<T> matrix<T>::identity(const unsigned int& n) {
    T value;
    std::string s = boost::typeindex::type_id<T>().pretty_name();
    if (s.substr(0, 6) == "matrix") {
        value = matrix<T>::identity(1);
    } else {
        value = 1;
    }
    
    
    matrix<T> m(n, n);
    for (int i = 0; i < n; i++) {
        m(i, i) = value;
    }
    return m;
}


template <typename T>
matrix<T>::matrix(const unsigned int& t_rows,
                  const unsigned int& t_columns) :
                    m_rows(t_rows),
                    m_columns(t_columns),
                    data(std::vector<std::vector<T>>(m_rows, std::vector<T>(m_columns))) {
    
}

template <typename T>
matrix<T>::matrix(const unsigned int& t_rows,
                  const unsigned int& t_columns,
                  const T& k) :
                    m_rows(t_rows),
                    m_columns(t_columns),
                    data(std::vector<std::vector<T>>(m_rows, std::vector<T>(m_columns, k))) {
    
}

template <typename T>
matrix<T>::matrix(const std::vector<std::vector<T>>& t_data) :
                    data(t_data),
                    m_rows(t_data.size()),
                    m_columns(m_rows == 0 ? 0 : t_data[0].size()) {
    
}

template <typename T>
matrix<T>::matrix(const std::vector<T>& t_data) :
                    data(std::vector<T>(1, t_data)),
                    m_rows(1),
                    m_columns(t_data.size()) {
    
}

template <typename T>
void matrix<T>::transpose() {
    matrix<T> m(columns(), rows());
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            m(j, i) = (*this)(i, j);
        }
    }
    *this = m;
}

template <typename T>
matrix<T> matrix<T>::transposed() const {
    matrix<T> m(columns(), rows());
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            m(j, i) = (*this)(i, j);
        }
    }
    return m;
}

template <typename T>
T matrix<T>::determinant() const {
    if (m_rows != m_columns) {
        std::cerr << "Cannot determine determinant of a non-square matrix." << std::endl;
    }
    if (m_rows == 1) {
        return data[0][0];
    }
    T det = T();
    for (int i = 0; i < m_columns; i++) {
        if (i%2 == 0) {
            det += data[0][i] * submatrix(0, i).determinant();
        } else {
            det -= data[0][i] * submatrix(0, i).determinant();
        }
    }
    return det;
}

template <typename T>
matrix<T> matrix<T>::submatrix(const unsigned int& excluded_row,
                               const unsigned int& excluded_column) {
    std::vector<std::vector<T>> v;
    for (int i = 0; i < m_rows; i++) {
        if (i != excluded_row) {
            v.push_back(std::vector<T>());
            for (int j = 0; j < m_columns; j++) {
                if (j != excluded_column) {
                    v[v.size() - 1].push_back(data[i][j]);
                }
            }
        }
        
    }
    return matrix<T>(v);
}

template <typename T>
matrix<T> matrix<T>::submatrix(const std::vector<unsigned int>& excluded_rows,
                               const std::vector<unsigned int>& excluded_columns) {
    for (int i = 0; i < excluded_rows.size(); i++) {
        if (excluded_rows[i] >= rows()) {
            std::cerr << "Invalid index for submatrix" << std::endl;
        }
    }
    for (int i = 0; i < excluded_columns.size(); i++) {
        if (excluded_columns[i] >= columns()) {
            std::cerr << "Invalid index for submatrix" << std::endl;
        }
    }
    std::vector<std::vector<T>> v(0, std::vector<T>(0));
    for (int i = 0; i < rows(); i++) {
        if (std::find(excluded_rows.begin(), excluded_rows.end(), i) == excluded_rows.end()) {
            v.push_back(std::vector<T>());
            for (int j = 0; j < columns(); j++) {
                if (std::find(excluded_columns.begin(), excluded_columns.end(), j) == excluded_columns.end()) {
                    v[v.size() - 1].push_back(data[i][j]);
                }
            }
        }
        
    }
    return matrix<T>(v);
}

template <typename T>
void matrix<T>::raise_to(const T& k) {
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            data[i][j] = pow(data[i][j], k);
        }
    }
}

template <typename T>
template <typename T1>
void matrix<T>::raise_to(const T1& k) {
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            data[i][j] = pow(data[i][j], k);
        }
    }
}

template <typename T>
matrix<T> matrix<T>::raised_to(const T& k) const {
    matrix<T> m(*this);
    return pow(m, k);
}


template <typename T>
template <typename T1>
matrix<T> matrix<T>::raised_to(const T1& k) const {
    matrix<T> m(*this);
    return pow(m, k);
}

template <typename T>
unsigned int matrix<T>::columns() const {
    return m_columns;
}

template <typename T>
unsigned int matrix<T>::rows() const {
    return m_rows;
}

template <typename T>
unsigned int matrix<T>::deep_columns() const {
    if (m_columns == 0) {
        return m_columns;
    }
    if (mat_val_type<T>::value) {
        unsigned int sum = 0;
        for (int i = 0; i < m_columns; i++) {
            sum += matrix<decltype(mat_val_type<T>::type)>(data[i][0]).columns();
        }
        return sum;
    } else {
        return m_columns;
    }
}

template <typename T>
unsigned int matrix<T>::deep_rows() const {
    if (m_rows == 0) {
        return m_rows;
    }
    if (mat_val_type<T>::value) {
        unsigned int sum = 0;
        for (int i = 0; i < m_rows; i++) {
            sum += matrix<decltype(mat_val_type<T>::type)>(data[i][0]).rows();
        }
        return sum;
    } else {
        return m_rows;
    }
}

template <typename T>
void matrix<T>::set_row(const std::vector<T>& row, unsigned int& i) {
    for (int j = 0; j < data[i].size(); j++) {
        if (j < row.size()) {
            data[i][j] = row[j];
        } else {
            T val;
            data[i][j] = val;
        }
    }
}

template <typename T>
template <typename T1>
void matrix<T>::set_row(const std::vector<T1>& row, unsigned int& i) {
    for (int j = 0; j < data[i].size(); j++) {
        if (j < row.size()) {
            data[i][j] = row[j];
        } else {
            T val;
            data[i][j] = val;
        }
    }
}

template <typename T>
void matrix<T>::set_column(const std::vector<T>& column, unsigned int& j) {
    for (int i = 0; i < data.size(); i++) {
        if (i < column.size()) {
            data[i][j] = column[i];
        } else {
            T val;
            data[i][j] = val;
        }
    }
}

template <typename T>
template <typename T1>
void matrix<T>::set_column(const std::vector<T1>& column, unsigned int& j) {
    for (int i = 0; i < data.size(); i++) {
        if (i < column.size()) {
            data[i][j] = column[i];
        } else {
            T val;
            data[i][j] = val;
        }
    }
}

template <typename T>
void matrix<T>::set_submatrix(const matrix<T>& submatrix, unsigned int& i_start, unsigned int& j_start) {
    for (int i = 0; i < submatrix.rows(); i++) {
        for (int j = 0; j < submatrix.columns(); j++) {
            if (i < rows() && j < columns()) {
                data[i_start+i][j_start+j] = submatrix[i][j];
            }
        }
    }
}

template <typename T>
template <typename T1>
void matrix<T>::set_submatrix(const matrix<T1>& submatrix, unsigned int& i_start, unsigned int& j_start) {
    for (int i = 0; i < submatrix.rows(); i++) {
        for (int j = 0; j < submatrix.columns(); j++) {
            if (i < rows() && j < columns()) {
                data[i_start+i][j_start+j] = submatrix[i][j];
            }
        }
    }
}

template <typename T>
void matrix<T>::clear() {
    T val;
    if (data.size() > 0) {
        fill(data.begin(), data.end(), vector<T>(data[0].size(), val));
    }
}

template <typename T>
void matrix<T>::fill(const T& val) {
    if (data.size() > 0) {
        fill(data.begin(), data.end(), vector<T>(data[0].size(), val));
    }
}

template <typename T>
template <typename T1>
void matrix<T>::fill(const T1& val) {
    if (data.size() > 0) {
        fill(data.begin(), data.end(), vector<T>(data[0].size(), val));
    }
}

static inline std::vector<std::string> split(const std::string& str, char delim) {
    std::vector<std::string> strings;
    size_t start;
    size_t end = 0;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
        end = str.find(delim, start);
        strings.push_back(str.substr(start, end - start));
    }
    return strings;
}


static inline std::string prettify_num(std::string str) {
    while (str.find('.') != std::string::npos) {
        str.erase(str.size() - 1, 1);
    }
    return str;
}

template <typename T>
std::string matrix<T>::to_string() const {
    std::string str_mat = "";
    
    if (mat_val_type<T>::value) {
        std::vector<std::vector<std::string>> strs;
        for (int i = 0; i < rows(); i++) {
            std::vector<std::vector<std::string>> splits;
            matrix<decltype(mat_val_type<T>::type)> dat;
            for (int j = 0; j < columns(); j++) {
                dat = data[i][j];
                splits.push_back(split(dat.to_string(), '\n'));
            }
            
            if (splits.size() > 0) {
                for (int j = 0; j < splits[0].size(); j++) {
                    strs.push_back(std::vector<std::string>());
                    for (int k = 0; k < splits.size(); k++) {
                        std::vector<std::string> a = split(splits[k][j], ' ');
                        for (int l = 0; l < a.size(); l++) {
                            if (l != 0) {
                                strs[strs.size() - 1].push_back(" ");
                            }
                            strs[strs.size() - 1].push_back(a[l]);
                        }
                        if (k != splits.size() - 1) {
                            strs[strs.size() - 1].push_back("|");
                        }
                    }
                }
            }
            if (i != rows() - 1) {
                strs.push_back(std::vector<std::string>());
            }
        }
        size_t max_size = 0;
        for (int i = 0; i < strs.size(); i++) {
            for (int j = 0; j < strs[i].size(); j++) {
                if (strs[i][j].size() > max_size) {
                    max_size = strs[i][j].size();
                }
            }
        }
        
        for (int i = 0; i < strs.size(); i++) {
            for (int j = 0; j < strs[i].size(); j++) {
                if (strs[i][j] != "|" && strs[i][j] != " ") {
                    size_t diff = max_size - strs[i][j].size();
                    for (int k = 0; k < diff; k++) {
                        strs[i][j] = " " + strs[i][j];
                    }
                }
                str_mat += strs[i][j];
            }
            if (strs[i].size() == 0) {
                for (int j = 0; j < strs[i-1].size(); j++) {
                    for (int k = 0; k < strs[i-1][j].size(); k++) {
                        if (strs[i-1][j] == "|") {
                            str_mat += "+";
                        } else {
                            str_mat += "-";
                        }
                    }
                }
            }
            str_mat += "\n";
        }
    } else {
        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data[i].size(); j++) {
                str_mat += prettify_num(std::to_string(data[i][j]));
                if (j != data[i].size() - 1) {
                    str_mat += " ";
                }
            }
            str_mat += "\n";
        }
    }
    return str_mat;
}

template <typename T>
void matrix<T>::print() const {
    std::cout << to_string() << std::endl;
}

template <typename T>
T& matrix<T>::operator()(const unsigned int& row,
                         const unsigned int& column) {
    return data[row][column];
}

template <typename T>
const T& matrix<T>::operator()(const unsigned int& row,
                               const unsigned int& column) const {
    return data[row][column];
}

template <typename T>
matrix<T>& matrix<T>::operator+=(const matrix<T>& m) {
    if (rows() != m.rows() || columns() != m.columns()) {
        std::cerr << "Cannot add matricies of differing size." << std::endl;
        return *this;
    }
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            data[i][j] += m(i, j);
        }
    }
    return *this;
}

template <typename T>
template <typename T1>
matrix<T>& matrix<T>::operator+=(const matrix<T1>& m) {
    if (rows() != m.rows() || columns() != m.columns()) {
        std::cerr << "Cannot add matricies of differing size." << std::endl;
        return *this;
    }
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            data[i][j] += m(i, j);
        }
    }
    return *this;
}

template <typename T>
matrix<T>& matrix<T>::operator+=(const T& k) {
    if (rows() != columns()) {
        std::cerr << "Cannot add value T to non-square matrix<T>." << std::endl;
        return *this;
    }
    for (int i = 0; i < rows(); i++) {
        data[i][i] += k;
    }
    return *this;
}

template <typename T>
template <typename T1>
matrix<T>& matrix<T>::operator+=(const T1& k) {
    if (rows() != columns()) {
        std::cerr << "Cannot add value T to non-square matrix<T>." << std::endl;
        return *this;
    }
    for (int i = 0; i < rows(); i++) {
        data[i][i] += k;
    }
    return *this;
}

template <typename T>
matrix<T>& matrix<T>::operator-=(const matrix<T>& m) {
    if (rows() != m.rows() || columns() != m.columns()) {
        std::cerr << "Cannot subtract matricies of differing size." << std::endl;
        return *this;
    }
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            data[i][j] -= m(i, j);
        }
    }
    return *this;
}

template <typename T>
template <typename T1>
matrix<T>& matrix<T>::operator-=(const matrix<T1>& m) {
    if (rows() != m.rows() || columns() != m.columns()) {
        std::cerr << "Cannot add matricies of differing size." << std::endl;
        return *this;
    }
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            data[i][j] -= m(i, j);
        }
    }
    return *this;
}

template <typename T>
matrix<T>& matrix<T>::operator-=(const T& k) {
    if (rows() != columns()) {
        std::cerr << "Cannot subtract value T from non-square matrix<T>." << std::endl;
        return *this;
    }
    for (int i = 0; i < rows(); i++) {
        data[i][i] -= k;
    }
    return *this;
}

template <typename T>
matrix<T>& matrix<T>::operator*=(const matrix<T>& m) {
    matrix<T> m1(rows(), m.columns());
    if (columns() != m.rows()) {
        std::cerr << "Cannot perform matrix m * matrix n when m.columns() != n.rows()" << std::endl;
        return m1;
    }
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            m1(i, j) = data[i][0] * m(0, j);
            for (int k = 1; k < m.rows(); k++) {
                m1(i, j) += data[i][k] * m(k, j);
            }
        }
    }
    *this = m1;
    return *this;
}

template <typename T>
template <typename T1>
matrix<T>& matrix<T>::operator*=(const matrix<T1>& m) {
    matrix<T> m1(rows(), m.columns());
    if (columns() != m.rows()) {
        std::cerr << "Cannot perform matrix m * matrix n when m.columns() != n.rows()" << std::endl;
        return m1;
    }
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            m1(i, j) = data[i][0] * m(0, j);
            for (int k = 1; k < m.rows(); k++) {
                m1(i, j) += data[i][k] * m(k, j);
            }
        }
    }
    *this = m1;
    return *this;
}

template <typename T>
matrix<T>& matrix<T>::operator*=(const T& k) {
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            data[i][j] *= k;
        }
    }
    return *this;
}

template <typename T>
template <typename T1>
matrix<T>& matrix<T>::operator*=(const T1& k) {
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            data[i][j] *= k;
        }
    }
    return *this;
}

template <typename T>
matrix<T>& matrix<T>::operator/=(const T& k) {
    if (k == 0) {
        std::cerr << "Cannot divide matrix by 0" << std::endl;
        return *this;
    }
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            data[i][j] /= k;
        }
    }
    return *this;
}

template <typename T>
template <typename T1>
matrix<T>& matrix<T>::operator/=(const T1& k) {
    if (k == 0) {
        std::cerr << "Cannot divide matrix by 0" << std::endl;
        return *this;
    }
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            data[i][j] /= k;
        }
    }
    return *this;
}

template <typename T>
matrix<T>& matrix<T>::operator%=(const matrix<T>& m) {
    if (rows() != m.rows() || columns() != m.columns()) {
        std::cerr << "Cannot modulo matricies of differing size." << std::endl;
        return *this;
    }
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            data[i][j] = modulo(data[i][j], m(i, j));
        }
    }
    return *this;
}

template <typename T>
template <typename T1>
matrix<T>& matrix<T>::operator%=(const matrix<T1>& m) {
    if (rows() != m.rows() || columns() != m.columns()) {
        std::cerr << "Cannot modulo matricies of differing size." << std::endl;
        return *this;
    }
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            data[i][j] = modulo(data[i][j], m(i, j));
        }
    }
    return *this;
}

template <typename T>
matrix<T>& matrix<T>::operator%=(const T& k) {
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            data[i][j] = modulo(data[i][j], k);
        }
    }
    return *this;
}

template <typename T>
template <typename T1>
matrix<T>& matrix<T>::operator%=(const T1& k) {
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++) {
            data[i][j] = modulo(data[i][j], k);
        }
    }
    return *this;
}

template <typename T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m) {
    m_rows = m.m_rows;
    m_columns = m.m_columns;
    data = m.data;
    return *this;
}

template <typename T>
matrix<T>::operator float() const {
    if (!mat_val_type<T>::value) {
        if (deep_columns() != 0 && deep_rows() != 0) {
            return data[0][0];
        } else {
            return 0;
        }
    } else {
        if (deep_columns() != 0 && deep_rows() != 0) {
            return (float) data[0][0];
        } else {
            return 0;
        }
    }
}

template <typename T1, typename T2>
matrix<T1> operator+(const matrix<T1>& m1, const matrix<T2>& m2) {
    if (m1.rows() != m2.rows() || m1.columns() != m2.columns()) {
        std::cerr << "Cannot add matricies of differing size." << std::endl;
        return matrix<T1>::identity(3);
    }
    
    matrix<T1> m3(m1.rows(), m1.columns());
    
    for (int i = 0; i < m3.rows(); i++) {
        for (int j = 0; j < m3.columns(); j++) {
            m3(i, j) = m1(i, j) + m2(i, j);
        }
    }
    return m3;
}

template <typename T>
matrix<T> operator+(const matrix<T>& m1, const matrix<T>& m2) {
    if (m1.rows() != m2.rows() || m1.columns() != m2.columns()) {
        std::cerr << "Cannot add matricies of differing size." << std::endl;
        return matrix<T>::Identity(3);
    }
    
    matrix<T> m3(m1.rows(), m1.columns());
    
    for (int i = 0; i < m3.rows(); i++) {
        for (int j = 0; j < m3.columns(); j++) {
            m3(i, j) = m1(i, j) + m2(i, j);
        }
    }
    return m3;
}

template <typename T1, typename T2>
matrix<T1> operator+(const matrix<T1>& m, const T2& k) {
    if (m.rows() != m.columns()) {
        std::cerr << "Cannot subtract value T from non-square matrix<T>." << std::endl;
    }
    matrix<T1> m1(m);
    
    for (int i = 0; i < m1.rows(); i++) {
        m1(i, i) += k;
    }
    return m1;
}

template <typename T>
matrix<T> operator+(const matrix<T>& m, const T& k) {
    if (m.rows() != m.columns()) {
        std::cerr << "Cannot subtract value T from non-square matrix<T>." << std::endl;
    }
    matrix<T> m1(m);
    
    for (int i = 0; i < m1.rows(); i++) {
        m1(i, i) += k;
    }
    return m1;
}

template <typename T1, typename T2>
matrix<T1> operator+(const T1& k, const matrix<T2>& m) {
    matrix<T1> m1(m);
    
    for (int i = 0; i < m1.rows(); i++) {
        m1(i, i) = k;
    }
    return m1;
}

template <typename T>
matrix<T> operator+(const T& k, const matrix<T>& m) {
    matrix<T> m1(m);
    
    for (int i = 0; i < m1.rows(); i++) {
        m1(i, i) += k;
    }
    return m1;
}

template <typename T1, typename T2>
matrix<T1> operator-(const matrix<T1>& m1, const matrix<T2>& m2) {
    if (m1.rows() != m2.rows() || m1.columns() != m2.columns()) {
        std::cerr << "Cannot subtract matricies of differing size." << std::endl;
        return matrix<T1>::Identity(3);
    }
    matrix<T1> m3(m1.rows(), m1.columns());
    
    for (int i = 0; i < m3.rows(); i++) {
        for (int j = 0; j < m3.columns(); j++) {
            m3(i, j) = m1(i, j) + m2(i, j);
        }
    }
    return m3;
}

template <typename T>
matrix<T> operator-(const matrix<T>& m1, const matrix<T>& m2) {
    if (m1.rows() != m2.rows() || m1.columns() != m2.columns()) {
        std::cerr << "Cannot subtract matricies of differing size." << std::endl;
        return matrix<T>::Identity(3);
    }
    matrix<T> m3(m1.rows(), m1.columns());
    
    for (int i = 0; i < m1.rows(); i++) {
        for (int j = 0; j < m1.columns(); j++) {
            m3(i, j) = m1(i, j) + m2(i, j);
        }
    }
    return m3;
}

template <typename T>
matrix<T> operator-(const matrix<T>& m) {
    matrix<T> m1(m.rows(), m.columns());
    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.columns(); j++) {
            m1(i, j) = -m(i, j);
        }
    }
    return m1;
}

template <typename T1, typename T2>
matrix<T1> operator-(const matrix<T1>& m, const T2& k) {
    if (m.rows() != m.columns()) {
        std::cerr << "Cannot subtract value T from non-square matrix<T>." << std::endl;
        return matrix<T1>::Identity(3);
    }
    matrix<T1> m1(m);
    for (int i = 0; i < m1.rows(); i++) {
        m1(i, i) -= k;
    }
    return m1;
}

template <typename T>
matrix<T> operator-(const matrix<T>& m, const T& k) {
    if (m.rows() != m.columns()) {
        std::cerr << "Cannot subtract value T from non-square matrix<T>." << std::endl;
        return matrix<T>::Identity(3);
    }
    matrix<T> m1(m);
    for (int i = 0; i < m.rows(); i++) {
        m1(i, i) = m(i, i) - k;
    }
    return m1;
}

template <typename T1, typename T2>
matrix<T1> operator-(const T1& k, const matrix<T2>& m) {
    if (m.rows() != m.columns()) {
        std::cerr << "Cannot subtract non-square matrix<T> from value T." << std::endl;
        return matrix<T1>::Identity(3);
    }
    matrix<T1> m1(m.rows(), m.columns);
    for (int i = 0; i < m1.rows(); i++) {
        m1(i, i) = k - m(i, i);
    }
    return m1;
}

template <typename T>
matrix<T> operator-(const T& k, const matrix<T>& m) {
    if (m.rows() != m.columns()) {
        std::cerr << "Cannot subtract non-square matrix<T> from value T." << std::endl;
        return matrix<T>::Identity(3);
    }
    matrix<T> m1(m);
    for (int i = 0; i < m.rows(); i++) {
        m1(i, i) = k - m(i, i);
    }
    return m1;
}

template <typename T1, typename T2>
matrix<T1> operator*(const T1& k, const matrix<T2>& m) {
    matrix<T1> m1(m);
    for (int i = 0; i < m1.rows(); i++) {
        for (int j = 0; j < m1.columns(); j++) {
            m1(i, j) *= k;
        }
    }
    return m1;
}

template <typename T>
matrix<T> operator*(const T& k, const matrix<T>& m) {
    matrix<T> m1(m);
    for (int i = 0; i < m1.rows(); i++) {
        for (int j = 0; j < m1.columns(); j++) {
            m1(i, j) *= k;
        }
    }
    return m1;
}

template <typename T1, typename T2>
matrix<T1> operator*(const matrix<T1>& m, const T2& k) {
    matrix<T1> m1(m);
    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.columns(); j++) {
            m1(i, j) *= k;
        }
    }
    return m1;
}

template <typename T>
matrix<T> operator*(const matrix<T>& m, const T& k) {
    matrix<T> m1(m.rows(), m.columns());
    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.columns(); j++) {
            m1(i, j) = k * m(i, j);
        }
    }
    return m1;
}

template <typename T1, typename T2>
matrix<T1> operator*(const matrix<T1>& m1, const matrix<T2>& m2) {
    matrix<T1> m3(m1.rows(), m2.columns());
    if (m1.columns() != m2.rows()) {
        std::cerr << "Cannot perform matrix m * matrix n when m.columns() != n.rows()" << std::endl;
        return m3;
    }
    for (int i = 0; i < m3.rows(); i++) {
        for (int j = 0; j < m3.columns(); j++) {
            m3(i, j) = m1(i, 0) * m2(0, j);
            for (int k = 1; k < m2.rows(); k++) {
                m3(i, j) += m1(i, k) * m2(k, j);
            }
        }
    }
    return m3;
}

template <typename T>
matrix<T> operator*(const matrix<T>& m1, const matrix<T>& m2) {
    matrix<T> m3(m1.rows(), m2.columns());
    if (m1.columns() != m2.rows()) {
        std::cerr << "Cannot perform matrix m * matrix n when m.columns() != n.rows()" << std::endl;
        return m3;
    }
    for (int i = 0; i < m3.rows(); i++) {
        for (int j = 0; j < m3.columns(); j++) {
            m3(i, j) = m1(i, 0) * m2(0, j);
            for (int k = 1; k < m2.rows(); k++) {
                m3(i, j) += m1(i, k) * m2(k, j);
            }
        }
    }
    return m3;
}

template <typename T1, typename T2>
matrix<T1> operator/(const matrix<T1>& m, const T2& k) {
    matrix<T1> m1(m);
    for (int i = 0; i < m1.rows(); i++) {
        for (int j = 0; j < m1.columns(); j++) {
            m1(i, j) /= k;
        }
    }
    return m1;
}

template <typename T>
matrix<T> operator/(const matrix<T>& m, const T& k) {
    matrix<T> m1(m);
    for (int i = 0; i < m1.rows(); i++) {
        for (int j = 0; j < m1.columns(); j++) {
            m1(i, j) /= k;
        }
    }
    return m1;
}

template <typename T1, typename T2>
matrix<T1> operator/(const T2& k, const matrix<T1>& m) {
    matrix<T1> m1(m.rows(), m.columns());
    for (int i = 0; i < m1.rows(); i++) {
        for (int j = 0; j < m1.columns(); j++) {
            m1(i, j) = k / m(i, j);
        }
    }
    return m1;
}

template <typename T>
matrix<T> operator/(const T& k, const matrix<T>& m) {
    matrix<T> m1(m.rows(), m.columns());
    for (int i = 0; i < m1.rows(); i++) {
        for (int j = 0; j < m1.columns(); j++) {
            m1(i, j) = k / m(i, j);
        }
    }
    return m1;
}

template <typename T>
matrix<T> operator%(const matrix<T>& m, const T& k) {
    matrix<T> m1(m);
    for (int i = 0; i < m1.rows(); i++) {
        for (int j = 0; j < m1.columns(); j++) {
            m1(i, j) = modulo(m1(i, j), k);
        }
    }
    return m1;
}

template <typename T1, typename T2>
matrix<T1> operator%(const matrix<T1>& m, const T2& k) {
    matrix<T1> m1(m);
    for (int i = 0; i < m1.rows(); i++) {
        for (int j = 0; j < m1.columns(); j++) {
            m1(i, j) = modulo(m1(i, j), k);
        }
    }
    return m1;
}

template <typename T>
matrix<T> operator%(const matrix<T>& m1, const matrix<T>& m2) {
    matrix<T> m3(m1.rows(), m1.columns());
    if (m1.columns() != m2.columns() || m1.rows() != m2.rows()) {
        std::cerr << "Cannot modulo matricies of differing sizes." << std::endl;
        return m3;
    }
    for (int i = 0; i < m3.rows(); i++) {
        for (int j = 0; j < m3.columns(); j++) {
            m3(i, j) = modulo(m1(i, j), m2(i, j));
        }
    }
    return m3;
}

template <typename T1, typename T2>
matrix<T1> operator%(const matrix<T1>& m1, const matrix<T2>& m2) {
    matrix<T1> m3(m1.rows(), m1.columns());
    if (m1.columns() != m2.columns() || m1.rows() != m2.rows()) {
        std::cerr << "Cannot modulo matricies of differing sizes." << std::endl;
        return m3;
    }
    for (int i = 0; i < m3.rows(); i++) {
        for (int j = 0; j < m3.columns(); j++) {
            m3(i, j) = modulo(m1(i, j), m2(i, j));
        }
    }
    return m3;
}

template <typename T>
bool operator==(const matrix<T>& m1, const matrix<T>& m2) {
    if (m1.rows() != m2.rows() || m1.columns() != m2.columns()) {
        std::cerr << "Cannot compare matricies of differing size." << std::endl;
        return false;
    }
    
    for (int i = 0; i < m1.rows(); i++) {
        for (int j = 0; j < m1.columns(); j++) {
            if (m1(i, j) != m2(i, j)) {
                return false;
            }
        }
    }
    return true;
}

template <typename T1, typename T2>
bool operator==(const matrix<T1>& m1, const matrix<T2>& m2) {
    if (m1.rows() != m2.rows() || m1.columns() != m2.columns()) {
        std::cerr << "Cannot compare matricies of differing size." << std::endl;
        return false;
    }
    
    for (int i = 0; i < m1.rows(); i++) {
        for (int j = 0; j < m1.columns(); j++) {
            if (m1(i, j) != m2(i, j)) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool operator!=(const matrix<T>& m1, const matrix<T>& m2) {
    if (m1.rows() != m2.rows() || m1.columns() != m2.columns()) {
        std::cerr << "Cannot compare matricies of differing size." << std::endl;
        return false;
    }
    
    for (int i = 0; i < m1.rows(); i++) {
        for (int j = 0; j < m1.columns(); j++) {
            if (m1(i, j) != m2(i, j)) {
                return true;
            }
        }
    }
    return false;
}

template <typename T1, typename T2>
bool operator!=(const matrix<T1>& m1, const matrix<T2>& m2) {
    if (m1.rows() != m2.rows() || m1.columns() != m2.columns()) {
        std::cerr << "Cannot compare matricies of differing size." << std::endl;
        return false;
    }
    
    for (int i = 0; i < m1.rows(); i++) {
        for (int j = 0; j < m1.columns(); j++) {
            if (m1(i, j) != m2(i, j)) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
matrix<T> pow(const matrix<T>& m1, const T& k) {
    matrix<float> m2(m1);
    for (int i = 0; i < m1.rows(); i++) {
        for (int j = 0; j < m1.columns(); j++) {
            m2(i, j) = pow(m1(i, j), k);
        }
    }
    return m2;
}

template <typename T1, typename T2>
matrix<T1> pow(const matrix<T1>& m1, const T2& k) {
    matrix<T1> m2(m1.rows(), m1.columns());
    for (int i = 0; i < m2.rows(); i++) {
        for (int j = 0; j < m2.columns(); j++) {
            m2(i, j) = pow(m1(i, j), k);
        }
    }
    return m2;
}

template <typename T>
T modulo(const T& n1, const T& n2) {
    T ret = n1;
    while (ret >= n2) {
        ret -= n2;
    }

    while (ret < 0) {
        ret += n2;
    }
    return ret;
}

template <typename T1, typename T2>
T1 modulo(const T1& n1, const T2& n2) {
    T1 ret = n1;
    while (ret >= n2) {
        ret -= n2;
    }

    while (ret < 0) {
        ret += n2;
    }
    return ret;
}

template <typename T>
matrix<T> modulo(const matrix<T>& m, const T& k) {
    matrix<T> m1(m.rows(), m.columns());
    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.columns(); j++) {
            m1(i, j) = modulo(m1(i, j), k);
        }
    }
    return m1;
}

template <typename T1, typename T2>
matrix<T1> modulo(const matrix<T1>& m, const T2& k) {
    matrix<T1> m1(m);
    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.columns(); j++) {
            m1(i, j) = modulo(m1(i, j), k);
        }
    }
    return m1;
}

template <typename T>
matrix<T> modulo(const matrix<T>& m1, const matrix<T>& m2) {
    matrix<T> m3(m1.rows(), m1.columns());
    if (m1.rows() != m2.rows() || m1.columns() != m2.columns()) {
        std::cerr << "Cannot modulo matricies of differing size." << std::endl;
        return m3;
    }
    for (int i = 0; i < m3.rows(); i++) {
        for (int j = 0; j < m3.columns(); j++) {
            m3(i, j) = modulo(m1(i, j), m2(i, j));
        }
    }
    return m3;
}

template <typename T1, typename T2>
matrix<T1> modulo(const matrix<T1>& m1, const matrix<T2>& m2) {
    matrix<T1> m3(m1.rows(), m1.columns());
    if (m1.rows() != m2.rows() || m1.columns() != m2.columns()) {
        std::cerr << "Cannot modulo matricies of differing size." << std::endl;
        return m3;
    }
    for (int i = 0; i < m3.rows(); i++) {
        for (int j = 0; j < m3.columns(); j++) {
            m3(i, j) = modulo(m1(i, j), m2(i, j));
        }
    }
    return m3;
}
