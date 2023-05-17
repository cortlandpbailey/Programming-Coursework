#include "Node.h";
using namespace std;

Node::Node(string g, Node *l, Node *r, int c = 0){
        this->gate = g;
        this->left = l;
        this->right = r;
        this->cost = c;
}

Node::Node(){
        this->gate = "input";
}

