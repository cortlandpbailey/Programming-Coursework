#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

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

// Function to read the netlist file
string readNetlist(string filename, unordered_map<string, Gate>& netlist) {
    ifstream infile(filename);
    string line;
    string output_start;
    while (getline(infile, line)) {     // read the file line by line until its empty
        if (line.empty()) 
            continue;
        
        stringstream ss(line);          // using stringstream pull out each element of the line and determine its type
        string name;
        string type;
        ss >> name;         // Since the first thing on the document is the name of the node that is the first thing saved
        ss >> type;         
        if (type == "INPUT")        // If the type is INPUT create that inside our logic expression map called netlist
            netlist[name] = {"INPUT", {}};
        else if (type == "OUTPUT") {        // If the type is OUTPUT create that inside our logic expression map called netlist
            netlist[name] = {"OUTPUT", {}};
            output_start = name;
        }
        else {          // If it isnt an output or input its an = sign, so we have a logic expression. Move forward to determine what it is:
            ss >> type; // Read the expression
            if (netlist.find(type) != netlist.end()) {      // if there is no expression and instead this is a node we've already read its just an equals. Set the current gate to be equal to the one its referencing
                netlist[name] =  netlist[type];
                continue;
            }
            string input1, input2;      // If its not an equals expression, create a new location in the netlist map for this expression
            ss >> input1;
            ss >> input2;
            netlist[name] = {type, {input1, input2}};
        }
    }
    return output_start;        // return the first value in the map
}

// Function to take the netlist and the root (output node) and compute the equivalent expression in terms of only NANDs and NOTs. This is then stored in a tree structure. 
Node* createNandNotTree(string output_node, unordered_map<string, Gate>& netlist) {
    Gate output_gate = netlist[output_node];
    if (output_gate.type == "INPUT") {          // If our output is just an input there is nothing to do. Return this node as an input. 
        return newNode("INPUT", nullptr, nullptr);
    }
    else if (output_gate.type == "NOT") {               // if this node is a NOT, create a NOT node in the tree and its leaf should point to its input
        string input_name = output_gate.inputs[0];  
        Node* input_node = createNandNotTree(input_name, netlist);
        return newNode("NOT", input_node, nullptr, 2);
    }
    else if (output_gate.type == "AND") {               // If this is an AND we equate it to a not gate whos input is a NAND. Create those nodes and recursively call this on the inputs to the NAND
        string input1_name = output_gate.inputs[0];
        string input2_name = output_gate.inputs[1];
        Node* input1_node = createNandNotTree(input1_name, netlist);
        Node* input2_node = createNandNotTree(input2_name, netlist);
        Node* nand_node = newNode("NAND2", input1_node, input2_node, 3);
        return newNode("NOT", nand_node, nullptr, 2);
    }
    else if (output_gate.type == "OR") {            // If this is an OR we equat it to a NAND whos inputs are NOTs of the actual inputs, recursively calling this function on those inputs
        string input1_name = output_gate.inputs[0];
        string input2_name = output_gate.inputs[1];
        Node* input1_node = createNandNotTree(input1_name, netlist);
        Node* input2_node = createNandNotTree(input2_name, netlist);
        Node* not1_node = newNode("NOT", input1_node, nullptr, 2);
        Node* not2_node = newNode("NOT", input2_node, nullptr, 2);
        return newNode("NAND2", not1_node, not2_node, 3);
    }
    else                                    // Failsafe, if its none of these, return it as if its an input.
        return newNode("INPUT", nullptr, nullptr);
}


void writeOutput(int cost) {        // use ofstream to write to a .txt file the final output
    ofstream outfile("output.txt");
    outfile << cost;
    outfile.close();
}


int calculateMinCost(Node *node) {
// The basic functionality of this is to check all possible combinations of gates that could combine to create the given tree. The comparisons are based on the tech library given in the 
// assignment and their costs are calculated here. As each possible option is found its value is saved in a vector. At the end we return the smallest value in the vector as its the minimum. 

    vector<int> costs;
    // If the passed in Node is an input, its cost is 0.
    if (node->gate == "INPUT") 
        return 0;
    // Next we check if the node is a NOT
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
    unordered_map<string, Gate> netlist;                // I chose to use an unordered map for this because its easy to keep track of the expressions and has a low-overhead for the memory
    string start = readNetlist("input.txt", netlist);
    Node* output_node = createNandNotTree(start, netlist);
    int cost = calculateMinCost(output_node);
    writeOutput(cost);

    return 0;
}