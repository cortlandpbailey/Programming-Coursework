#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

// Define the gates in the Technology Library
unordered_map<string, int> tech_lib = {
    {"NOT", 2},
    {"NAND2", 3},
    {"AND2", 4},
    {"NOR2", 6},
    {"OR2", 4},
    {"AOI21", 7},
    {"AOI22", 7}
};

struct Node {
    string gate;  // Gate type ("NOT", "NAND2", etc) or Input/Output
    Node* left = nullptr;  // left input node
    Node *right = nullptr; // right input node
    int cost = 0;  // Minimal cost of this node
};
Node* newNode(){
    Node *node = new Node;
    node->gate = "INPUT";
    return node;
    };

Node* newNode(string g, Node *l, Node *r, int c = 0){
        Node* node = new Node;
        node->gate = g;
        node->left = l;
        node->right = r;
        node->cost = c;
        return node;
    };

// Gate structure for the logic expression
struct Gate {
    string type; // Type of the gate (e.g., "AND", "OR", "NOT")
    vector<string> inputs; // Input signals
};

unordered_map<string, Gate> netlist;

string readNetlist(string filename) {
    ifstream infile(filename);
    string line;
    string output_start;
    while (getline(infile, line)) {
        if (line.empty()) 
            continue;
        
        stringstream ss(line);
        string name;
        string type;
        ss >> name;
        ss >> type;
        if (type == "INPUT") 
            netlist[name] = {"INPUT", {}};
        else if (type == "OUTPUT") {
            netlist[name] = {"OUTPUT", {}};
            output_start = name;
        }
        else {
            ss >> type;
            //Replace word of the function with the character representation
            if (type == "NOT")
                type = "!";
            else if (type == "AND")
                type = "&";
            else if (type == "OR")
                type = "|";
            else if (netlist.find(type) != netlist.end()) {
                netlist[name] =  netlist[type];
                continue;
            }
            string input1, input2;
            ss >> input1;
            ss >> input2;
            netlist[name] = {type, {input1, input2}};
        }
    }
    return output_start;
}

string createLogicExpr(string output_node) {
    Gate output_gate = netlist[output_node];
    if (output_gate.type == "INPUT")
        return output_node;
    else if (output_gate.type == "!") 
        return "NOT " + output_gate.inputs[0];
     
    else {
        string input1_expr = createLogicExpr(output_gate.inputs[0]);
        if (output_gate.inputs.size() == 1) 
            return input1_expr + " " + output_gate.type;
        else {
            string input2_expr = createLogicExpr(output_gate.inputs[1]);
            return "(" + input1_expr + " " + output_gate.type + " " + input2_expr + ")";
        }
    }
}

Node* createNandNotTree(string output_node) {
    Gate output_gate = netlist[output_node];
    if (output_gate.type == "INPUT") {
        Node* input_node = newNode("INPUT", nullptr, nullptr);
        return input_node;
    }
    else if (output_gate.type == "!") {
        string input_name = output_gate.inputs[0];
        Node* input_node = createNandNotTree(input_name);
        return newNode("NOT", input_node, nullptr, 2);
    }
    else if (output_gate.type == "&") {
        string input1_name = output_gate.inputs[0];
        string input2_name = output_gate.inputs[1];
        Node* input1_node = createNandNotTree(input1_name);
        Node* input2_node = createNandNotTree(input2_name);
        Node* nand_node = newNode("NAND2", input1_node, input2_node, 3);
        return newNode("NOT", nand_node, nullptr, 2);
    }
    else if (output_gate.type == "|") {
        string input1_name = output_gate.inputs[0];
        string input2_name = output_gate.inputs[1];
        Node* input1_node = createNandNotTree(input1_name);
        Node* input2_node = createNandNotTree(input2_name);
        Node* not1_node = newNode("NOT", input1_node, nullptr, 2);
        Node* not2_node = newNode("NOT", input2_node, nullptr, 2);
        Node* nand_node = newNode("NAND2", not1_node, not2_node, 3);
        return nand_node;
    }
    else 
        return newNode("INPUT", nullptr, nullptr);
}


void writeOutput(int cost) {
    ofstream outfile("C:/Users/baile/Dropbox (Personal)/Programming/E2/output.txt");
    outfile << cost;
    outfile.close();
}


int calculateMinCost(Node *node) {
    vector<int> costs;

    if (node->gate == "INPUT") 
        return 0;

    if (node->gate == "NOT"){
        costs.push_back(2 + calculateMinCost(node->left));      // NOT Gate + its input costs
        if (node->left->gate == "NAND2") {          // If the tree begins with a NOT to NAND check if its one of these 4 structures and continue calculating based on each sub tree's inputs
            costs.push_back(4 + calculateMinCost(node->left->left) + calculateMinCost(node->left->right));      // AND2 Gate + its input costs
            if (node->left->left->gate == "NAND2" && node->left->right->gate == "NAND2") 
                costs.push_back(7 + calculateMinCost(node->left->left->left) + calculateMinCost(node->left->left->right) + calculateMinCost(node->left->right->left) + calculateMinCost(node->left->right->right)); // AOI22 Gate+ its input costs
            
            if (node->left->left->gate == "NAND2" && node->left->right->gate == "NOT")
                costs.push_back(7 + calculateMinCost(node->left->left->left) + calculateMinCost(node->left->left->right) + calculateMinCost(node->left->right->left)); // AOI21 Gate + its input costs

            if (node->left->left->gate == "NOT" && node->left->right->gate == "NOT")
                costs.push_back(6 + calculateMinCost(node->left->left->left) + calculateMinCost(node->left->right->left)); // NOR2 Gate + its input costs
        }
  
    }
    else if (node->gate == "NAND2") {       // if the tree begins with a NAND2 gate check if its inputs are both not gates, otherwise its just a nand and continue
        costs.push_back(3 + calculateMinCost(node->left) + calculateMinCost(node->right));      // NAND2 Gate + its input costs
        if (node->left->gate == "NOT" && node->right->gate == "NOT") 
            costs.push_back(4 + calculateMinCost(node->left->left) + calculateMinCost(node->right->left)); // OR2 Gate + its input costs 
    }

    return *min_element(costs.begin(), costs.end());
}



int main() {
    Node *a = newNode();
    Node *b = newNode();
    Node *c = newNode();
    Node *d = newNode();
    Node *p = newNode("NOT", a, nullptr);
    Node *q = newNode("NAND2", b, c);
    Node *r = newNode("NAND2", p, q);
    Node *s = newNode("NOT", d, nullptr);
    Node *t = newNode("NAND2", r, s);
    Node *test = newNode("NOT", t, nullptr);
    string start = readNetlist("C:/Users/baile/Dropbox (Personal)/Programming/E2/input.txt");
    cout << createLogicExpr(start);
    Node* output_node = createNandNotTree(start);
    int cost = calculateMinCost(output_node);
    writeOutput(cost);

    return 0;
}