#include <iostream>
#include "../include/linalg.hpp"

using namespace linalg;


bool Matrix::check_row_bounds(int i) const {
    if (0 <= i && i < dims.first) {
        return true;
    } else {
        return false;
    }
}

bool Matrix::check_col_bounds(int j) const {
    if (0 <= j && j < dims.second) {
        return true;
    } else {
        return false;
    }
}

bool Matrix::check_bounds(int i, int j) const {
    return (check_row_bounds(i) && check_col_bounds(j));
}

Matrix::Matrix(std::pair<int, int> dims) : dims(dims) {
    data = new double[dims.first*dims.second];
}

Matrix::Matrix(int M, int N) : dims(std::pair<int, int> {M, N}) {
    data = new double[dims.first*dims.second];
}

Matrix::Matrix(Matrix const &t_other) : dims(t_other.size()) {
    data = new double[dims.first*dims.second];
    assign_other(t_other);
}

Matrix::~Matrix(){
    if (!this->is_safe_to_destroy()) {
        std::cout << "WARNING: not safe to delete!" << std::endl;
    }
    delete [] data;
}

std::pair<int, int> Matrix::size() const {
    return dims;
}

double Matrix::at(int i, int j) const {
    assert(check_bounds(i, j) && "ERROR: index out of bounds");
    return data[i * dims.second + j];
}

double& Matrix::at(int i, int j){
    assert(check_bounds(i, j) && "ERROR: index out of bounds");
    return data[i * dims.second + j];
}

ConstVectorView Matrix::crowview(int i) const {
    return ConstVectorView(*this, &data[i * dims.first], dims.first);
}

VectorView Matrix::rowview(int i){
    return VectorView(*this, &data[i * dims.first], dims.first);
}

ConstVectorView Matrix::ccolview(int j) const {
    return ConstVectorView(*this, &data[j], dims.second, dims.first);
}

VectorView Matrix::colview(int j){
    return VectorView(*this, &data[j], dims.second, dims.first);
}

void Matrix::assign_other(Matrix const &B){
    for (size_t i = 0; i < dims.second; i++)
    {
        for (size_t j = 0; j < dims.first; j++)
        {
            this->at(i, j) = B.at(i, j);
        }
    }
}

void Matrix::add_assign_other(Matrix const &B){
    for (size_t i = 0; i < dims.second; i++)
    {
        for (size_t j = 0; j < dims.first; j++)
        {
            this->at(i, j) += B.at(i, j);
        }
    }
}

void Matrix::subtract_assign_other(Matrix const &B){
    for (size_t i = 0; i < dims.second; i++)
    {
        for (size_t j = 0; j < dims.first; j++)
        {
            this->at(i, j) -= B.at(i, j);
        }
    }
}

void Matrix::assign_scalar_multiply(double a){
    for (size_t i = 0; i < dims.second; i++)
    {
        for (size_t j = 0; j < dims.first; j++)
        {
            this->at(i, j) *= a;
        }
    }
}