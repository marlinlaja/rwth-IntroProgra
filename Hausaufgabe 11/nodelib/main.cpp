#include <iostream>
#include "inc/Set.hpp"
#include "inc/Node.hpp"


int main() {
    Set s;
    s.insert(10);
    s.insert(7);
    s.insert(1);
    s.insert(8);
    s.insert(42);
    s.insert(15);
    s.insert(2);

    s.print();
    s.to_dot();
    std::cout << "max height: " << s.max_height() << std::endl;
}