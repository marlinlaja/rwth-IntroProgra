#include "functions.hpp"
#include "integrals.hpp"


int main() {
    polynom<double> p(2, std::vector<double>{3, 1.2, 0.7});
    exponential<double> e(0.2, 0.8, 2.4);
    montecarlo<double> m(0, 4, 0, 20, 10000);
    riemann<double> r(0, 4, 1000);
    // Riemann and MC for polynomial
    r.print(&p);
    m.print(&p);
    // Riemann and MC for exponential
    r.print(&e);
    m.print(&e);
}