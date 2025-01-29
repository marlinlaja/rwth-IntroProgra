#include <iostream>
#include <fstream>
#include <string>
#include "../inc/Set.hpp"


void Set::insert(int value) {
    // TODO 2.1)
    values_unordered[counter] = Node(value);
    if(root) {
        root->insert(&values_unordered[counter]);
    } else {
        root = &values_unordered[counter];
    }
    counter++;
}


void Set::print() { 
    // TODO 2.2)
    if(root) {
        root->print();
    } else {
        std::cout << "Set ist leer!" << std::endl;
    }
}

int Set::max_height() {
    // TODO 2.3)
    if(root) {
        return root->max_height();
    } else {
        std::cout << "Set ist leer!" << std::endl;
        return 0;
    }
}

void Set::to_dot() {
    if(!root) return;
    std::ofstream o("graph.dot");
    std::string result = "digraph finite_state_machine { " + root->to_dot() + "}";
    o << result;
}