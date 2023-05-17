#pragma once
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

template <typename T>
class ABS
{
private:
	float maxCapacity;
	unsigned int size;
	T* stack;
	// Increasing or decreasing size of stack is a factor of 2.0f. 
	//Must throw runtime_error  - no need for try/catch, thats in the test code
	// Methods:
public:
	ABS();
	ABS(float capacity);
	ABS(const ABS& d);
	ABS<T> &operator=(const ABS& d);
	~ABS();
	void push(T data);
	T pop();
	T peek();
	unsigned int getSize();
	float getMaxCapacity();
	T* getData();
};

//************************* END CLASS DEFINITION ***************************************************************
	// Default constructor
	template <typename T>
	ABS<T>::ABS() {
		maxCapacity = 1;
		size = 0;
		stack = new T[(int)maxCapacity];
	}
	 
	// Constructor with specified starting capacity
	template <typename T>
	ABS<T>::ABS(float capacity) {
		maxCapacity = capacity;
		size = 0;
		stack = new T[(int)maxCapacity];
	}

	// Copy constructor
	template <typename T>
	ABS<T>::ABS(const ABS& d) {
		this->maxCapacity = d.maxCapacity;
		this->size = d.size;
		this->stack = d.stack;
	}

	// Assignment operator
	template <typename T>
	ABS<T>& ABS<T>::operator=(const ABS& d) {
		delete[] stack;
		maxCapacity = d.maxCapacity;
		size = d.size;
		stack = d.stack;

		return *this;
	}
	

	// Destructor
	template <typename T>
	ABS<T>::~ABS() {
		delete[] stack;   //delete all dynamic data
	}

	// void Push(T data)     Push a new item on the stack - resize as needed
	template <typename T>
	void ABS<T>::push(T data) {
		if (size == 0) {
			//maxCapacity = 2;
			stack[size] = data;
		}

		else if (size == maxCapacity) {
			maxCapacity = maxCapacity * 2.0f;				// double size of capacity
			T* tempArray = new T[(int)maxCapacity];				//new holding array for data in stack
			for (unsigned int i = 0; i < size; i++)		
				tempArray[i] = stack[i];					//iterate through and store values in the new array
			
			tempArray[size] = data;							//add new data to the top of the stack
			delete[] stack;									//delete the memory at the old address			
			stack = tempArray;								//move the stack pointer to the new address

		}
		else if (size < maxCapacity) {

			stack[size] = data;
			/*
			T* tempArray = new T[size+1];			//new holding array for data in stack
			for (unsigned int i = 0; i < size; i++) {
				tempArray[i] = stack[i];			//iterate through and store values in the new array
			}
			delete[] stack;						//delete the stack array
			stack = tempArray;			//make a new stack array with the new size			
			stack[size] = data;				//add the new data on top of the stack
			stackptr = &stack[size];				//move the pointer up to the top
			*/
		}
		size++;
		return;

	}

	// T Pop()     pop the top item off the stack - resizing as needed
	template <typename T>
	T ABS<T>::pop() {
		T _temp;
		if (size == 0) {
			throw runtime_error("Stack is empty.");		//If stack is empty throw error
		}
		else {
			_temp = stack[size - 1];
			size--;
			if (size < maxCapacity / 2.0f) {
				maxCapacity = floorf(maxCapacity/2.0f);			//If stack is less than half full, downsize the stack
				T* tempArray = new T[(int)maxCapacity];			//new holding array for data in stack
				for (unsigned int i = 0; i < size; i++)
					tempArray[i] = stack[i];					//iterate through and store values in the new array
				delete[] stack;									//delete the memory at the old address			
				stack = tempArray;								//move the stack pointer to the new address
			}
		}
		return _temp;
	}

	// T Peek()    Return the top item off the stack without removing it 
	template <typename T>
	T ABS<T>::peek() {
		if (size == 0) {
			throw runtime_error("Stack is empty.");
		}
		T _temp = stack[size-1];			//Store value at pointer
		return _temp;				//Return value at pointer
		}

	// unsigned int getSize()      get the current number of items in the stack
	template <typename T>
	unsigned int ABS<T>::getSize() {
		return size;
	}
	// unsigned int getMaxCapacity()       get the capacity of the stack
	template <typename T>
	float ABS<T>::getMaxCapacity() {
		return maxCapacity;
	}
	// T* GetData()         return the array representing the stack ie: return the whole stack by pointer
	template <typename T>
	T* ABS<T>::getData() {
		return stack;
	}