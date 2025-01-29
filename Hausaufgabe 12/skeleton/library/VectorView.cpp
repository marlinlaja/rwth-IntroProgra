#include "../include/linalg.hpp"

using namespace linalg;


VectorView::VectorView(TrackedViewable const &t_viewed, double *t_start, int t_length, int t_stride)
: viewed(t_viewed) ,view_start(t_start), length(t_length), stride(t_stride)
{
    viewed.increment_live_views();
}

VectorView::VectorView(TrackedViewable const &t_viewed, double *t_start, int t_length)
: viewed(t_viewed) ,view_start(t_start), length(t_length), stride(1)
{
    viewed.increment_live_views();
}

VectorView::~VectorView() {
    viewed.decrement_live_views();
}

int VectorView::size() const {
    return length;
}

double VectorView::at(int i) const {
    assert(check_bounds(i) && "ERROR: index out of bounds");
    return *(view_start + i * stride);
}

double& VectorView::at(int i) {
    assert(check_bounds(i) && "ERROR: index out of bounds");
    return *(view_start + i * stride);
}

ConstVectorView VectorView::cview(int start, int length) const {
    return ConstVectorView(viewed, view_start + start * stride, length);
}

VectorView VectorView::view(int start, int length) {
    return VectorView(viewed, view_start + start * stride, length);
}