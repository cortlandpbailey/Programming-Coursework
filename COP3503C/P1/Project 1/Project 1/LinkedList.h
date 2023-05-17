#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class LinkedList
{
public:
	struct Node;
	/************* BEHVAOIRS ***********/
	void PrintForward() const;											//done
	void PrintReverse() const;											//done
	void PrintForwardRecursive(const Node* node) const;					//done
	void PrintReverseRecursive(const Node* node) const;					//done

	/************* ACCESSORS ***********/
	unsigned int NodeCount() const;										//done
	void FindAll(vector<Node*>& outData, const T& value) const;			//done
	const Node* Find(const T& data) const;								//done
	Node* Find(const T& data);											//done
	const Node* GetNode(unsigned int index) const;						//done
	Node* GetNode(unsigned int index);									//done
	Node* Head();														//done
	const Node* Head() const;											//done
	Node* Tail();														//done
	const Node* Tail() const;											//done

	/************* INSERTION ***********/
	void AddHead(const T& data);										//done
	void AddTail(const T& data);										//done
	void AddNodesHead(const T* data, unsigned int count);				//done
	void AddNodesTail(const T* data, unsigned int count);				//done
	void InsertAfter(Node* node, const T& data);						//done
	void InsertBefore(Node* node, const T& data);						//done
	void InsertAt(const T& data, unsigned int index);					//done

	/************* Removal ***********/
	bool RemoveHead();													//done
	bool RemoveTail();													//done
	unsigned int Remove(const T& data);									//done
	bool RemoveAt(unsigned int index);									//done
	void Clear();														//done

	/************* Operators ***********/
	const T& operator[](unsigned int index) const;						//done
	T& operator[](unsigned int index);									//done	
	bool operator==(const LinkedList<T>& rhs) const;					//done
	LinkedList<T>& operator=(const LinkedList<T>& rhs);					//done

	/************* Construction/Destruction ***********/
	LinkedList();														//done
	LinkedList(const LinkedList<T>& list);								//done
	~LinkedList();														//done

	struct Node {				//nested node
		T data;
		Node* next = nullptr;
		Node* prev = nullptr;
		friend class LinkedList;
	};

private:
	Node* head = nullptr;
	Node* tail = head;
	unsigned int qty = 0;
	Node* NewNode(T data, Node* _next, Node* _prev);
};	
/* ------------------------ END DECLARATIONS -----------------------------*/
//New node constructor
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::NewNode(T _data, Node* _next, Node* _prev) {			//create a new node
	Node* nodeptr = new Node;
	nodeptr->data = _data;
	nodeptr->next = _next;
	nodeptr->prev = _prev;
	qty++;

	return nodeptr;
}

//create an empty linked list 
template <typename T>
LinkedList<T>::LinkedList() {
	LinkedList<T>::head = nullptr;
	LinkedList<T>::tail = nullptr;
	qty = 0;
}

//copy constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
	head = NewNode(list[0], nullptr, nullptr);
	tail = head;
	for (unsigned int i = 1; i < list.qty; i++) {
		this->LinkedList<T>::AddTail(list[i]);
	}
}

//destructor, deletes all nodes from the list
template <typename T>
LinkedList<T>::~LinkedList() {
	Node* nodeptr = head;
	while (nodeptr != nullptr) {
		Node* n = nodeptr->next;
		delete nodeptr;
		nodeptr = n;
	}
}

//clear all nodes from the list, bringing it down to empty.
template <typename T>
void LinkedList<T>::Clear() {
	if (head == nullptr) return;
	Node* nodeptr = this->head;
	for (unsigned int i = 0; i < qty; i++) {
		Node* temp = nodeptr;
		nodeptr = nodeptr->next;
		delete temp;
	}
	qty = LinkedList<T>::NodeCount();
}

//print list forward order
template <typename T>
void LinkedList<T>::PrintForward() const {			//print the linked list in foward order
	
	const Node* nodereader = head;

	while (nodereader != nullptr) {
		cout << nodereader->data << endl;
		nodereader = nodereader->next;
	}
	return;
}		

//print list in reverse order
template <typename T>
void LinkedList<T>::PrintReverse() const {			//print the linked list in reverse order
	const Node* nodereader = tail;
	while (nodereader != nullptr) {
		cout << nodereader->data << endl;
		nodereader = nodereader->prev;
	}
	return;
}	

//define what the "[]" operator does between LinkedLists
template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
	const Node* nodeptr = this->GetNode(index);		//use getnode function to get the Node at the index requested
	return nodeptr->data;						//return the data in the node given
}

//define what the "[]" operator does between LinkedLists
template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
	Node* nodeptr = this->GetNode(index);
	return nodeptr->data;
}

//define what the "==" operator does between LinkedLists
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
	bool _equal = true;
	Node* nodeptr = head;
	LinkedList<T> _inputlist(rhs);
	Node* _inputnodeptr = _inputlist.head;
	if (qty != _inputlist.qty) {
		_equal = false;
		return _equal;
	}
	while (_equal == true) {
		if (nodeptr != nullptr) {
			if (nodeptr->data == _inputnodeptr->data) {
				_equal = true;
				nodeptr = nodeptr->next;
				_inputnodeptr = _inputnodeptr->next;
			}
			else {
				_equal = false;
			}
		}
		else {
			return _equal;
		}
	}
	return _equal;
}

//define what the "=" operator does between LinkedLists -- COPY ASSIGNMENT OPERATOR
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	LinkedList<T> _new(rhs);
	swap(_new.head, head);
	return *this;
}

//return the size of the list
template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
	unsigned int count = 0;
	Node* nodeptr = head;
	while (nodeptr != nullptr) {
		count++;
		nodeptr = nodeptr->next;
	}
	return count;
}

//return the head pointer
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
	return head;		//return a pointer to the head node
}

//return the head pointer
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
	return head;		//return a pointer to the head node thats not changeable
}

//return the tail pointer
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
	if (head->next == nullptr) {
		return head;
	}
	else {
		Node* tailptr = Head();
		while (tailptr->next != nullptr) {
			tailptr = tailptr->next;
		}
		return tailptr;
	}
}

//return the tail pointer
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
	if (head == nullptr) {
		return nullptr;
	}

	else if (head->next == nullptr) {
		return head;
	}
	else {
		const Node* tailptr = head;
		while (tailptr->next != nullptr) {
			tailptr = tailptr->next;
		}
		return tailptr;
	}
}

//add to the top of the list
template <typename T>
void LinkedList<T>::AddHead(const T& data) {
		Node* newnode = LinkedList<T>::NewNode(data, nullptr, nullptr);
		if (qty == 1) {
			head = newnode;
			tail = newnode;
		}
		else {
			head->prev = newnode;
			newnode->next = head;
			head = newnode;
			tail = Tail();
		}
		
		return;

}

//add to the bottom
template <typename T>
void LinkedList <T>::AddTail(const T& data) {
	Node* newnode = LinkedList<T>::NewNode(data, nullptr, nullptr);

	if (qty == 1) {
		head = newnode;
		tail = newnode;
	}
	else {
		tail->next = newnode;
		newnode->prev = tail;
		tail = newnode;
	}
	return;
}

//add to front of list
template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
		Node* oldhead = head;								// store the location of the previous head
		head = NewNode(*data, nullptr, nullptr);			//create the new head, first data point of the array with no next/prev locations yet.
		data++;												//increment the data address
		Node* _prev = head;									//create a new store for holding the last node created to be given to the next one. 
		
	for (unsigned int i = 1; i < count; i++) {				//iterate and create the remaining new nodes
		if (i == count-1) {								//for the final value of the array
			Node* n = NewNode(*data, oldhead, _prev);		//set the last of the new nodes to be made with the next set to the oldhead
			n->prev->next = n;								//access the previous node through prev, and update it's next with the address of the node just created.
			oldhead->prev = n;
		}
		else {												
			Node* n = NewNode(*data, nullptr, _prev);		// make a new node. 1st iteration is nullptr for next, prev is the new head.
			data++;											// increment data address
			n->prev->next = n;								//access the last node through prev, and update it's next with the address of the node just created.
			_prev = n;										//update _prev with the address of the node that was just created to be used in the next Node
		}
	}
	return;
}

//add to bottom of list
template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {	
	for (unsigned int i = 0; i < count; i++) {
		LinkedList<T>::AddTail(*data);
		data++;											//increment the data address
	}
	tail = Tail();										//update tail pointer		
	return;
}

// Find first occurance of a particular data item
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
	Node* nodeptr = head;			//start the nodepointer at the front of the list
	for (unsigned int i = 0; i < qty; i++) {
		if (nodeptr->data != data) {
			nodeptr = nodeptr->next;
			if (nodeptr == nullptr) {	//if the data doesn't exist in the List, return nullptr
				return nodeptr;
			}
		}
		else {
			return nodeptr;
		}
	}
	throw out_of_range("No such Node");
}

// Find first occurance of a particular data item
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
	Node* nodeptr = head;			//start the nodepointer at the front of the list
	for (unsigned int i = 0; i < qty; i++) {
		if (nodeptr->data != data) {
			nodeptr = nodeptr->next;
			if (nodeptr == nullptr) {	//if the data doesn't exist in the List, return nullptr
				return nodeptr;
			}
		}
		else {
			return nodeptr;
		}
	}
	throw out_of_range("No such Node");
}

// Find all occurances of a particular data item
template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
	Node* nodeptr = head;			//start the nodepointer at the front of the list
	for (unsigned int i = 0; i < qty; i++) {
		if (nodeptr->data == value) {;
			outData.push_back(nodeptr);
		}
		else if (nodeptr == nullptr) {					//if the data doesn't exist in the List, throw exception
			throw out_of_range("No such data");
		}
		nodeptr = nodeptr->next;
	}
	return;
}

//Return a node at a given index
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
	if (index >= qty) {
		throw out_of_range("No such index");
	}
	Node* nodeptr = head;
	for (unsigned int i = 0; i < index; i++) {
		nodeptr = nodeptr->next;
	}
	return nodeptr;

}

//Return a node at a given index
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
	if (index >= qty) {
		throw out_of_range("No such index");
	}
	Node* get_nodeptr = head;
	for (unsigned int i = 0; i < index; i++) {
		get_nodeptr = get_nodeptr->next;
	}
	return get_nodeptr;
}

//Insert after a given pointer to a node
template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
	Node* _nodeptr = node;
	Node* _newnode = LinkedList<T>::NewNode(data, _nodeptr->next, _nodeptr);
	if (_nodeptr->next != nullptr) {
		_nodeptr->next->prev = _newnode;
		_nodeptr->next = _newnode;
	}
	else {
		_nodeptr->next = _newnode;
	}
}

//insert before a given pointer to an existing node
template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
	Node* nodeptr = node;
	Node* newnode = LinkedList<T>::NewNode(data, nodeptr, nodeptr->prev);
	nodeptr->prev->next = newnode;
	nodeptr->prev = newnode;
}

//insert at a given index, redirecting the nodes around it
template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
	if (index == 0) {
		LinkedList<T>::AddHead(data);
	}
	else {
		Node* ptr = LinkedList<T>::GetNode(index-1);
		LinkedList<T>::InsertAfter(ptr, data);
	}
}

//Remove Head node
template <typename T>
bool  LinkedList<T>::RemoveHead() {
	Node* nodeptr = head;
	if (head != nullptr) {
		if (head->next != nullptr) {
			head->next->prev = nullptr;		//untie the head from the next element
			head = head->next;				//Move the head pointer to the next element
			delete nodeptr;					//delete the old head
			qty--;							//decrement size
			return true;
		}
		else {
			head = nullptr;
			tail = nullptr;
			delete nodeptr;
			qty--;
			return true;
		}
	}
	return false;					//if head is nullptr, cant remove that, so return false. 
}

//Remove tail node
template <typename T>
bool  LinkedList<T>::RemoveTail() {
	Node* nodeptr = tail;			// LinkedList<T>::Tail();
	if (nodeptr != nullptr) {
		if (tail->prev != nullptr) {
			tail->prev->next = nullptr;	//untie tail from the previous node
			tail = tail->prev;			//move tail pointer back to previous node;
			delete nodeptr;				//delete old tail
			qty--;						//decrement size of list
			return true;
		}
		else {
			tail = nullptr;
			head = nullptr;
			delete nodeptr;
			qty--;
			return true;
		}
	}
	return false;					
}

//Remove a node with the given data value
template <typename T>
unsigned int  LinkedList<T>::Remove(const T& data) {
	unsigned int count = 0;
	Node* nodeptr = head;
	Node* temp = nodeptr;
	for (unsigned int i = 0; i < qty; i++) {
		if (nodeptr->data == data) {
			if (nodeptr == head) {
				LinkedList<T>::RemoveHead();
				count++;
				nodeptr = head;
			}
			else if (nodeptr == tail) {
				LinkedList<T>::RemoveTail();
				count++;
			}
			else {
				temp = nodeptr->next;
				nodeptr->prev->next = nodeptr->next;		//reassign the pointers in the adjacent nodes to each other, jumping over the Node we're deleting
				nodeptr->next->prev = nodeptr->prev;
				delete  nodeptr;
				count++;
				nodeptr = temp;
			}
		}
		else {
			nodeptr = nodeptr->next;
		}
	}
	qty = qty - count;
	return count;
}

//Remove node at the given index
template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
	if (index >= qty) {									//if index is out of range, return false
		return false;
	}
	Node* nodeptr = head;								//start at the Head node
	if (nodeptr != nullptr) {
		for (unsigned int i = 0; i < index; i++) {
			nodeptr = nodeptr->next;					//iterate to the node at Index
		}
		if (nodeptr == head) {
			LinkedList<T>::RemoveHead();
			return true;
		}
		else if (nodeptr == tail) {
			LinkedList<T>::RemoveTail();
			return true;
		}
		nodeptr->prev->next = nodeptr->next;			//Reassign node pointers around the node being removed. 
		nodeptr->next->prev = nodeptr->prev;
		delete nodeptr;									//delete node
		qty--;											//decrement size of the list
		return true;
	}
	return false;
}

//recursive forward print
template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
	if (node != nullptr) {
		cout << node->data << endl;
		if (node->next != nullptr) {
			LinkedList<T>::PrintForwardRecursive(node->next);
		}
	}
}

//Recursive reverse print
template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
	if (node != nullptr) {
		cout << node->data << endl;
		if (node->prev != nullptr) {
			LinkedList<T>::PrintReverseRecursive(node->prev);
		}

	}
}
