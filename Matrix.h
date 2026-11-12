#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <stdexcept>
#include <cstddef>
#include <iostream>

using namespace std;

template <class T>
class Matrix {
public:
    // Constructor
    Matrix(size_t = 0, size_t = 0);

    // Getters
    size_t get_rows() const;
    size_t get_cols() const;

    // Setters
    void set(size_t, size_t, const T&); // Set element at (row, col)

    // Class member functions
    T& at(size_t, size_t); // Access element at (row, col)
    const T& at(size_t, size_t) const; // Access element at (row, col) for const objects

    Matrix<T> operator+(const Matrix<T>&) const; // Matrix addition

    Matrix<T> operator-() const; // Matrix negation
    Matrix<T> operator-(const Matrix<T>&) const; // Matrix subtraction

    Matrix<T> operator*(const Matrix<T>&) const; // Matrix multiplication
    Matrix<T> operator*(const T&) const; // Scalar multiplication

    Matrix<T> power(unsigned int) const; // Raise the matrix to a non-negative integer power

    
private:
    // Data fields
    size_t rows;
    size_t cols;
    vector<vector<T>> data;


};

// Constructors

template <class T>
Matrix<T>::Matrix(size_t rows, size_t columns) : rows(rows), cols(columns), data(rows, vector<T>(columns)) {
    if (rows == 0 || columns == 0) {
        throw invalid_argument("Matrix dimensions must be greater than zero.");
    }
}

// Getters
template <class T>
size_t Matrix<T>::get_rows() const {
    return rows;
}

template <class T>
size_t Matrix<T>::get_cols() const {
    return cols;
}

// Setters
template <class T>
void Matrix<T>::set(size_t row, size_t col, const T& value) {
    data.at(row).at(col) = value;
}

// Class member functions
template <class T>
T& Matrix<T>::at(size_t row, size_t col) {
    return data.at(row).at(col);
}

template <class T>
const T& Matrix<T>::at(size_t row, size_t col) const {
    return data.at(row).at(col);
}

template <class T>
Matrix<T> Matrix<T>::operator + (const Matrix<T>& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw invalid_argument("Matrix dimensions must match for addition.");
    }

    Matrix<T> result(rows, cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.at(i, j) = this->at(i, j) + other.at(i, j);
        }
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator *(const Matrix<T>& other) const {
    if (cols != other.rows) {
        throw invalid_argument("Matrix dimensions are not compatible for multiplication.");
    }

    Matrix<T> result(rows, other.cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < other.cols; ++j) {
            result.at(i, j) = T(); // Initialize to zero
            for (size_t k = 0; k < cols; ++k) {
                result.at(i, j) += this->at(i, k) * other.at(k, j);
            }
        }
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator * (const T& scalar) const {
    Matrix<T> result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.at(i, j) = this->at(i, j) * scalar;
        }
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator - () const {
    return *this * (T)-1;
}

template <class T>
Matrix<T> Matrix<T>::operator - (const Matrix<T>& other) const {
    return *this + (-other);
}

template <class T>
Matrix<T> Matrix<T>::power(unsigned int exponent) const {
    if (rows != cols) {
        throw invalid_argument("Matrix must be square to raise to a power.");
    }

    Matrix<T> result(rows, cols);
    // Initialize result as the identity matrix
    for (size_t i = 0; i < rows; ++i) {
        result.at(i, i) = T(1);
    }

    Matrix<T> base = *this;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = result * base;
        }
        base = base * base;
        exponent /= 2;
    }
    return result;
} // Time complexity: O(log(exponent))

template <class T>
std::ostream& operator << (std::ostream& os, const Matrix<T>& matrix) {
    for (size_t i = 0; i < matrix.get_rows(); ++i) {
        for (size_t j = 0; j < matrix.get_cols(); ++j) {
           if (j > 0) {
                os << " "; // Add space between elements
            }
            os << matrix.at(i, j);
        }
        os << std::endl;
    }
    return os;
}

template <class T>
istream& operator >> (istream& is, Matrix<T>& matrix) {
    for (size_t i = 0; i < matrix.get_rows(); ++i) {
        for (size_t j = 0; j < matrix.get_cols(); ++j) {
            is >> matrix.at(i, j);

            if (!is) { return is; } // If input fails, return the stream
        }
    }
    return is;
}
#endif // MATRIX_H