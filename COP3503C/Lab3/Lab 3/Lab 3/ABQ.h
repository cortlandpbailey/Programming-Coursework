#pragma once
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

template <typename T>
class ABQ
{
private:
	float maxCapacity;
	unsigned int size;
	T* queue = nullptr;
	// Increasing or decreasing size of stack is a factor of 2.0f. 
	//Must throw runtime_error  - no need for try/catch, thats in the test code
	// Methods:
public:
	ABQ();
	ABQ(int capacity);
	ABQ(const ABQ& d);
	ABQ<T>& operator=(const ABQ& d);
	~ABQ();
	void enqueue(T data);
	T dequeue();
	T peek();
	unsigned int getSize();
	float getMaxCapacity();
	T* getData();

};


//************************* END CLASS DEFINITION ***************************************************************
	// Default constructor
template <typename T>
ABQ<T>::ABQ() {
	maxCapacity = 1;
	size = 0;
	queue = new T[(int)maxCapacity];
}

// Constructor with specified starting capacity
template <typename T>
ABQ<T>::ABQ(int capacity) {
	maxCapacity = capacity;
	size = 0;
	queue = new T[(int)maxCapacity];
}

// Copy constructor
template <typename T>
ABQ<T>::ABQ(const ABQ& d) {
	this->maxCapacity = d.maxCapacity;
	this->size = d.size;
	this->queue = d.queue;
}

// Assignment operator
template <typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ& d) {
	delete[] queue;
	maxCapacity = d.maxCapacity;
	size = d.size;
	queue = d.queue;	
	return *this;
}


// Destructor
template <typename T>
ABQ<T>::~ABQ() {
	delete[] queue;   //delete all dynamic data
}

// void enqueue(T data)     enqueue a new item on the queue - resize as needed
template <typename T>
void ABQ<T>::enqueue(T data) {
	if (size == maxCapacity) {
		maxCapacity = maxCapacity * 2.0f;			// double size of capacity
		T* tempArray = new T[(int)maxCapacity];		//new holding array for data in stack
		for (unsigned int i = 0; i < size; i++)
			tempArray[i] = queue[i];				//iterate through and store values in the new array
		delete[] queue;								//delete the stack array
		queue = tempArray;							//make a new stack array with the new size
	}
	queue[size] = data;
	size++;
	return;
}

// T dequeue()     dequeue the bottom item off the queue - resizing as needed
template <typename T>
T ABQ<T>::dequeue() {
	T _temp;
	if (size == 0) {
		throw runtime_error("Stack is Empty.");
	}
	else {
		_temp = queue[0];			//store value at bottom of queue
		size--;
		if (size < maxCapacity / 2.0f) {
			maxCapacity = floorf(maxCapacity / 2);
		}
		T* tempArray = new T[(int)maxCapacity];
		for (unsigned int i = size; i > 0; i--)
			tempArray[i-1] = queue[i];
		delete[] queue;
		queue = tempArray;
	}
	return _temp;
}

// T Peek()    Return the bottom item off the queue without removing it 
template <typename T>
T ABQ<T>::peek() {
	if (size == 0) {
		throw runtime_error("Stack is empty.");
	}
	T _temp = queue[0];			//Store value at the bottom
	return _temp;				//Return value at bottom
}

// unsigned int getSize()      get the current number of items in the queue
template <typename T>
unsigned int ABQ<T>::getSize() {
	return size;
}
// unsigned int getMaxCapacity()       get the capacity of the queue
template <typename T>
float ABQ<T>::getMaxCapacity() {
	return maxCapacity;
}
// T* GetData()         return the array representing the queue ie: return the whole queue by pointer
template <typename T>
T* ABQ<T>::getData() {
	return queue;
}
