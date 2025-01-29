#include "../include/linalg.hpp"

using namespace linalg;


Vector linalg::add(VectorLike const &u, VectorLike const &v) {
    Vector vec(u);
    vec.add_assign_other(v);
    return vec;
}

Matrix linalg::add(Matrix const &A, Matrix const &B) {
    Matrix M(A);
    M.add_assign_other(B);
    return M;
}

Vector linalg::subtract(VectorLike const &u, VectorLike const &v) {
    Vector vec(u);
    vec.subtract_assign_other(v);
    return vec;
}

Matrix linalg::subtract(Matrix const &A, Matrix const &B) {
    Matrix M(A);
    M.subtract_assign_other(B);
    return M;
}

double linalg::scalar_product(VectorLike const &u, VectorLike const &v) {
    double result = 0;
    for (size_t i = 0; i < u.size(); i++)
    {
        result += u.at(i) * v.at(i);
    }
    return result;
}

Vector linalg::scalar_multiply(VectorLike const &u, double s) {
    Vector vec(u);
    vec.assign_scalar_multiply(s);
    return vec;
}

Matrix linalg::scalar_multiply(Matrix const &A, double s) {
    Matrix M(A);
    M.assign_scalar_multiply(s);
    return M;
}

Vector linalg::matrix_vector_prod(Matrix const &A, VectorLike const &b) {
    Vector vec(A.size().second);
    for (size_t i = 0; i < A.size().second; i++)
    {
        double result = 0;
        for (size_t j = 0; j < A.size().first; j++)
        {
            result += A.at(i, j) * b.at(j);
        }
        vec.at(i) = result;
    }
    return vec;
}

Matrix linalg::matrix_matrix_prod(Matrix const &A, Matrix const &B) {
    Matrix M(A.size().first, B.size().second);
    for (size_t i = 0; i < M.size().first; i++) {
        for (size_t k = 0; k < M.size().second; k++) {
            M.at(i, k) = 0;
            for (size_t j = 0; j < A.size().second; j++) {
                M.at(i, k) += A.at(i, j) * B.at(j, k);
            }
        }
    }
    return M;
}


void linalg::print_vectorlike_to(VectorLike const &v, std::ostream &out) {
    for (size_t i = 0; i < v.size(); i++) {
        out << v.at(i) << " ";
    }
    out << "\n";
}

void linalg::print_matrix_to(Matrix const &m, std::ostream &out) {
    for (size_t row = 0; row < m.size().second; ++row) {
        for (size_t col = 0; col < m.size().first; ++col) {
            out << m.at(row, col) << " ";
        }
        out << "\n";
    }
}