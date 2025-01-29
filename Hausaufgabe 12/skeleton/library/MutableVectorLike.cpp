#include "../include/linalg.hpp"

using namespace linalg;

void MutableVectorLike::assign_other(VectorLike const &u) {
    for (size_t i = 0; i < this->size(); i++)
    {
        this->at(i) = u.at(i);
    }
}

void MutableVectorLike::add_assign_other(VectorLike const &u) {
    for (size_t i = 0; i < this->size(); i++)
    {
        this->at(i) += u.at(i);
    }
}

void MutableVectorLike::subtract_assign_other(VectorLike const &u) {
    for (size_t i = 0; i < this->size(); i++)
    {
        this->at(i) -= u.at(i);
    }
}

void MutableVectorLike::assign_scalar_multiply(double a) {
    for (size_t i = 0; i < this->size(); i++)
    {
        this->at(i) *= a;
    }
}