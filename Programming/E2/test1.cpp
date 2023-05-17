#include <iostream>
#include <string>
#include <stack>

using namespace std;

// Node structure for the NAND/NOT tree
struct Node {
    string value;
    Node* left;
    Node* right;
};

// Function to create a new node
Node* newNode(string value) {
    Node* node = new Node;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to build the NAND/NOT tree from a logic expression
Node* buildNandNotTree(string expression) {

    stack<Node*> nodeStack;

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        if (c == ' ') {
            continue;
        }
        else if (c == '(') {
            nodeStack.push(newNode("("));
        }
        else if (c == ')') {
            Node* right = nodeStack.top();
            nodeStack.pop();
            Node* op = nodeStack.top();
            nodeStack.pop();
            Node* left = nodeStack.top();
            nodeStack.pop();
            op->left = left;
            op->right = right;
            nodeStack.push(op);
        }
        else if (c == 'N') {
            string nandOp = "NAND";
            if (expression[i + 1] == 'O') {
                nandOp = "NOT";
                i += 2;
            }
            nodeStack.push(newNode(nandOp));
        }
    }

    return nodeStack.top();
}

// Function to generate C++ code for the NAND/NOT tree
void generateCode(Node* root) {
    if (root == NULL) {
        return;
    }

    if (root->value == "NAND") {
        cout << "!(";
        generateCode(root->left);
        cout << " && ";
        generateCode(root->right);
        cout << ")";
    }
    else if (root->value == "NOT") {
        cout << "!(";
        generateCode(root->left);
        cout << ")";
    }
    else {
        cout << "(";
        generateCode(root->left);
        cout << " " << root->value << " ";
        generateCode(root->right);
        cout << ")";
    }
}

int main() {
    string expression = "(((d OR e) AND ((a AND b) OR d)) OR (((f AND g) OR ((a OR (b AND c)) AND (d OR e))) AND h))";
    Node* root = buildNandNotTree(expression);
    generateCode(root);
    return 0;
}



/* Node* createNandNotTree(string logic_expr) {
    stack<Node*> node_stack;
    unordered_map<string, Node*> variable_map;

    for (char c : logic_expr) {
        if (c == ' ')
            continue;
        else if (c == '(')
            node_stack.push(nullptr);
        else if (c == ')') {
            Node* parent_node = node_stack.top();
            node_stack.pop();
            Node* left_node = node_stack.top();
            node_stack.pop();
            if (parent_node == nullptr) {
                // This is a NOT gate
                Node* not_node = newNode("NOT", left_node, nullptr);
                node_stack.push(not_node);
            } 
            else {
                // This is a NAND gate
                Node* nand_node = newNode("NAND", left_node, parent_node);
                node_stack.push(nand_node);
            }
        } 
        else if (c == '!') 
            node_stack.push(nullptr);
        else if (c == '&')
            node_stack.push(nullptr);
        else if (c== '|')
            node_stack.push(nullptr);
        else {
            // This is a variable
            string var_name = "";
            while (c != ' ' && c != ')' && c != '(') {
                var_name += c;
                c = logic_expr[node_stack.size() + var_name.size()];
            }
            if (variable_map.find(var_name) == variable_map.end()) 
                variable_map[var_name] = newNode(var_name, nullptr, nullptr);
            
            node_stack.push(variable_map[var_name]);
        }
    }

    return node_stack.top();
}
 */