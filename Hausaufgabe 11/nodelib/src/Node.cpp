#include <iostream>
#include <cmath>
#include "../inc/Node.hpp"


Node::Node(const int& value) : value(value) {
    // TODO 1.1): Konstruktor mit einem Argument
}

void Node::insert(Node* n) {
    // TODO 1.2): Einfügen von Zeiger auf n an der richtigen Stelle
    if (n->value < value) {
        if (leftChild) {
            leftChild->insert(n);
        } else {
            leftChild = n;
        }
    } else if (n->value > value) {
        if (rightChild) {
            rightChild->insert(n);
        } else {
            rightChild = n;
        }
    }
}


void Node::print() {
    // TODO: 1.3)
    if(leftChild) {
        leftChild->print();
    }
    std::cout << value << std::endl;
    if(rightChild) {
        rightChild->print();
    }
}

int Node::max_height() {
    // TODO 1.4)
    int left_height = 0;
    int right_height = 0;
    if (leftChild) {
        left_height = 1 + leftChild->max_height();
    }
    if (rightChild) {
        right_height = 1 + rightChild->max_height();
    }
    return std::max(left_height, right_height);
}

std::string Node::to_dot() {
    std::string result = "";
    if(leftChild) { 
        result += std::to_string(value) + "->" + std::to_string(leftChild->value) +";";
        result += leftChild->to_dot(); 
    } else {
        std::string unn = "l"+std::to_string(value);
        result += "\""+unn +"\""+ "[label=\"r\" style=invis];";
        result += std::to_string(value) + "-> "+"\""+unn +"\""+" ;";
    }

    if(rightChild) { 
        result += std::to_string(value) + "->" + std::to_string(rightChild->value) +";" + rightChild->to_dot();
    } else {
        std::string unn = "r"+std::to_string(value);
        result += "\""+unn +"\"" + "[label=\"l\" style=invis];";
        result += std::to_string(value) + "-> "+"\""+unn +"\""+" ;";
    }
    return result;
}