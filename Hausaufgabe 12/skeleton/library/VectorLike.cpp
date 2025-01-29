#include "../include/linalg.hpp"

using namespace linalg;

bool VectorLike::check_bounds(int i) const {
    if (0 <= i && i < this->size()) {
        return true;
    } else {
        return false;
    }
}

VectorLike::~VectorLike() {};