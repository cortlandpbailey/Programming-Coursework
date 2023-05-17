#pragma once
#include <string>
#include <vector>
#include "Showroom.h"
using namespace std;
#ifndef DEALERSHIP_H
#define DEALERSHIP_H


class Dealership
{
public:
	Dealership(string name = "Generic Dealership", unsigned int capacity = 0);			//Default constructor
	void AddShowroom(Showroom s);
	float GetAveragePrice();
	void ShowInventory();


private:
	string name;
	unsigned int capacity;
	vector<Showroom> ShowroomList;
};

#endif