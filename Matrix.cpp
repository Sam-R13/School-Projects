/**
 * Copyright rabesj 2021
 * This program performs operations on matrices
 */
#ifndef MATRIX_CPP
#define MATRIX_CPP

#include <cassert>
#include <vector>
#include "Matrix.h"
#include <assert.h>

Matrix::Matrix(const size_t row, const size_t col, const Val initVal) :
    std::vector<std::vector<Val>>(row, std::vector<Val>(col, initVal)) {
}

// Operator to write the matrix to a given output stream
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    // Print the number of rows and columns to ease reading
    os << matrix.height() << " " << matrix.width() << '\n';
    // Print each entry to the output stream.
    for (auto& row : matrix) {
        for (auto& val : row) {
            os << val << " ";
        }
        // Print a new line at the end of each row just to format the
        // output a bit nicely.
        os << '\n';
    }
    return os;
}

/**
 * Stream extraction operator
 * This method reads in a Matrix from an input stream
 * @param is, the input stream
 * @param matrix, the matrix we are writing to
 * @return istream, the input stream used for the matrix
 */
std::istream& operator>>(std::istream& is, Matrix& matrix) {
    int row, col;
    is >> row >> col;
    Matrix tmp(row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            is >> tmp[i][j];
        }
    }
    matrix = tmp;
    return is;
}

/**
 * Addition operator
 * This method defines the addition operation for two Matrix objects
 * @param rhs, the Matrix object we are adding to the implicit parameter
 * @return Matrix, the sum of the implicit parameter and rhs Matrix
 */
Matrix Matrix::operator+(const Matrix& rhs) const {
    assert((*this).height() == rhs.height());
    assert((*this).width() == rhs.width());
    Matrix ret((*this).height(), (*this).width());
    for (int i = 0; i < (*this).height(); i++) {
        for (int j = 0; j < (*this).width(); j++) {
            ret[i][j] = (*this)[i][j] + rhs[i][j];
        }
    }
    return ret;
}

/**
 * Multiplication operator
 * This method defines the multiplication operation for two Matrix objects
 * @param rhs, the Matrix object we are multiplying to the implicit Matrix
 * @return Matrix, the product of the implicit and rhs Matrix
 */
Matrix Matrix::operator*(const Matrix& rhs) const {
    assert((*this).height() == rhs.height());
    assert((*this).width() == rhs.width());
    Matrix ret((*this).height(), (*this).width());
    for (int i = 0; i < (*this).height(); i++) {
        for (int j = 0; j < (*this).width(); j++) {
            ret[i][j] = (*this)[i][j] * rhs[i][j];
        }
    }
    return ret;
}

/**
 * Scalar multiplication operator
 * This method performs scalar multiplication on a Matrix
 * @param val, the value we are multiplying the implicit Matrix by
 * @return Matrix, the modified Matrix object
 */
Matrix Matrix::operator*(const Val val) const {
    Matrix ret = (*this);
    for (int i = 0; i < ret.height(); i++) {
        for (int j = 0; j < ret.width(); j++) {
            ret[i][j] = ret[i][j] * val;
        }
    }
    return ret;
}

/**
 * Subtraction operator
 * This method subtracts two Matrix objects
 * @param rhs, the Matrix we are subtracting from the implicit Matrix
 * @return Matrix, the difference of the two Matrix objects
 */
Matrix Matrix::operator-(const Matrix& rhs) const {
    assert((*this).height() == rhs.height());
    assert((*this).width() == rhs.width());
    Matrix ret((*this).height(), (*this).width());
    for (int i = 0; i < (*this).height(); i++) {
        for (int j = 0; j < (*this).width(); j++) {
            ret[i][j] = (*this)[i][j] - rhs[i][j];
        }
    }
    return ret;
}

/**
 * Dot product
 * This method computes the dot product of two matrices
 * @param rhs, the Matrix we are dot multiplying with implicit Matrix
 * @return Matrix, the dot product of the implicit Matrix and the rhs parameter
 */
Matrix Matrix::dot(const Matrix& rhs) const {
    assert((*this).width() == rhs.height());
    Matrix ret((*this).height(), rhs.width());
    for (int i = 0; i < ret.height(); i++) {
        for (int j = 0; j < ret.width(); j++) {
            for (int k = 0; k < rhs.height(); k++) {
                ret[i][j] = ret[i][j] + ((*this)[i][k] * rhs[k][j]);
            }
        }
    }
    return ret;
}

/**
 * Transpose of Matrix
 * This function returns the transpose of a Matrix
 * @return Matrix, the transpose of the implicit Matrix parameter
 */
Matrix Matrix::transpose() const {
    Matrix ret((*this).width(), (*this).height());
    for (int i = 0; i < ret.width(); i++) {
        for (int j = 0; j < ret.height(); j++) {
            ret[j][i] = (*this)[i][j];
        }
    }
    return ret;
}
#endif
