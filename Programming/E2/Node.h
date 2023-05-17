#pragma once
#include <string>
using namespace std;

// Define the node structure for the NAND-NOT tree
class Node {

public:
    Node();
    Node(string g, Node *l, Node *r, int c = 0);
    string gate;  // Gate type ("NOT", "NAND2", etc) or Input/Output
    Node* left = nullptr;  // left input node
    Node *right = nullptr; // right input node
    int cost = 0;  // Minimal cost of this node
};