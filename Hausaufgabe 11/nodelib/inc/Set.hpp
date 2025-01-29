#include "Node.hpp"

class Set {
    Node* root = nullptr;
    Node values_unordered[1000];
    std::size_t counter = 0;

public:
    
    Set() {}

    void insert(int value);

    void print();

    int max_height();

    void to_dot();

};