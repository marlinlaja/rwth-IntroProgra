#include "../include/linalg.hpp"

using namespace linalg;

ConstVectorView::ConstVectorView(TrackedViewable const &t_viewed, double const *t_start, int t_length, int t_stride)
: viewed(t_viewed) ,view_start(t_start), length(t_length), stride(t_stride) {
    viewed.increment_live_views();
}

ConstVectorView::ConstVectorView(TrackedViewable const &t_viewed, double const *t_start, int t_length)
: viewed(t_viewed) ,view_start(t_start), length(t_length), stride(1) {
    viewed.increment_live_views();
}

ConstVectorView::~ConstVectorView() {
    viewed.decrement_live_views();
}

int ConstVectorView::size() const {
    return length;
}

double ConstVectorView::at(int i) const {
    assert(check_bounds(i) && "ERROR: index out of bounds");
    return *(view_start + i * stride);
}

ConstVectorView const ConstVectorView::cview(int start, int length) const {
    return ConstVectorView(viewed, view_start + start * stride, length);
};