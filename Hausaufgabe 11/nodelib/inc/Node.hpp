#pragma once
class Node {
    Node *rightChild = nullptr;
    Node *leftChild = nullptr;
    int value;
public:

    Node() {}
    Node(const int& value);

    void insert(Node* n);

    void print();

    int max_height();

    std::string to_dot();
};