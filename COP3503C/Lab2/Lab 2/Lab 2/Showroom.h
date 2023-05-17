#pragma once
#include <string>
#include <vector>
#include "Vehicle.h"
using namespace std;
#ifndef SHOWROOM_H
#define SHOWROOM_H
class Showroom
{
public:	
	//Default constructor

	Showroom(string name = "Unnamed Showroom", unsigned int capacity = 0);
	//
	//Accessor
	vector<Vehicle> GetVehicleList();

	//Behaviors
	void AddVehicle(Vehicle v);
	void ShowInventory();
	float GetInventoryValue();

private:
	string name;
	unsigned int capacity;
	vector<Vehicle> VehicleList;
};
#endif
