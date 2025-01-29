#include <iostream>
#include "../include/linalg.hpp"

using namespace linalg;

Vector::Vector(int length) : length(length) {
    data = new double[length];
}

Vector::Vector(linalg::VectorLike const &t_other) : length(t_other.size()) {
    data = new double[length];
    for (size_t i = 0; i < length; i++)
    {
        data[i] = t_other.at(i);
    }
}

Vector::~Vector() {
    if (!this->is_safe_to_destroy()) {
        std::cout << "Destroying a 'Vector' with " << this->live_view_count() << " views still active!" << std::endl;
    }
    delete [] data;
}

int Vector::size() const {
    return length;
}

double Vector::at(int i) const{
    assert(check_bounds(i) && "ERROR: index out of bounds");
    return data[i];
}

double& Vector::at(int i) {
    assert(check_bounds(i) && "ERROR: index out of bounds");
    return data[i];
}

ConstVectorView Vector::cview(int start, int length) const {
    return ConstVectorView(*this, &data[start], length);
}

VectorView Vector::view(int start, int length) {
    return VectorView(*this, &data[start], length);
}