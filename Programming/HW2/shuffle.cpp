using namespace std;
class Node {
public:
int val;
Node *next;
Node() : val(0), next(nullptr) {}
Node(int x) : val(x), next(nullptr) {}
Node(int x, Node *next) : val(x), next(next) {}
};

Node* Tail(Node* head) {
	if (head->next == nullptr) {
		return head;
	}
	else {
        Node *tailptr = head;
        while (tailptr->next != nullptr) {
			tailptr = tailptr->next;
		}
		return tailptr;
	}
}

int ListSize(Node* head) {
    int n = 1;
    if (head->next == nullptr) {
		return n;
	}
	else {
        Node *tailptr = head;
        while (tailptr->next != nullptr) {
            n++;
            tailptr = tailptr->next;
		}
		return n;
	}
}

void shuffle(Node* head) {
    if (head == nullptr){
        return;
    }
    Node *tail = Tail(head); 
    int mid = ListSize(head) / 2;
    
    for (int i = 0; i < mid; i++)
    { 
        Node *temp = head->next;
        head->next = tail;
        tail->next = temp;
        head = temp;
        while (temp->next != tail)
            temp = temp->next;
        temp->next = nullptr;
        tail = temp;
        
    }
}