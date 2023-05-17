#include <iostream>
#include <string>
#include <cmath>
using namespace std;


class CircularQueue
{
private:
	int maxCapacity;
	unsigned int size;
	float* queue = nullptr;
	// Methods:
public:
	CircularQueue();
	CircularQueue(int n);
	CircularQueue(const CircularQueue& d);
	~CircularQueue();
	void enQueue(float data);
	float deQueue();
	float getLast();
    float getFront();
    bool isFull();
    bool isEmpty();
};


//************************* END CLASS DEFINITION ***************************************************************

// Default constructor
CircularQueue::CircularQueue() {
	maxCapacity = 1;
	size = 0;
	queue = new float[maxCapacity];
}

// Constructor with specified starting capacity
CircularQueue::CircularQueue(int n) {
	maxCapacity = n;
	size = 0;
	queue = new float[maxCapacity];
}

// Copy constructor
CircularQueue::CircularQueue(const CircularQueue& d) {
	this->maxCapacity = d.maxCapacity;
	this->size = d.size;
    this->queue = new float[d.maxCapacity];
    for (int i = 0; i <= d.size; i++){
        this->queue[i] = d.queue[i];
    }
}

// Destructor
CircularQueue::~CircularQueue() {
	delete[] queue;   //delete all dynamic data
}

// void enqueue(float data)     enqueue a new item on the queue - resize as needed
void CircularQueue::enQueue(float data) {
	if (CircularQueue::isFull()) {
		throw logic_error("Stack is Full.");
	}
    else {
	    queue[size] = data;
	    size++;
    }
	return;
}

// float dequeue()     dequeue the bottom item off the queue - resizing as needed
float CircularQueue::deQueue() {
	float _temp;
	if (size == 0) {
		throw logic_error("Stack is Empty.");
	}
	else {
		_temp = queue[0];			//store value at bottom of queue
        for (int i = 1; i<size; i++){
            queue[i-1] = queue[i];
        }
        size--;
        return _temp;
	}

}

// float getLast()    Return the bottom item off the queue without removing it 
float CircularQueue::getFront() {
	if (size == 0) {
		throw logic_error("Stack is empty.");
	}
	return queue[0];				        //Return value at bottom
}


float CircularQueue::getLast(){
    if (size == 0) {
		throw logic_error("Stack is empty.");
	}
	return queue[size-1];				            //Return value at top
}

bool CircularQueue::isFull(){
    if (size == maxCapacity)
        return true;
    else
        return false;
}
bool CircularQueue::isEmpty(){
    if (size == 0)
        return true;
    else
        return false;
}