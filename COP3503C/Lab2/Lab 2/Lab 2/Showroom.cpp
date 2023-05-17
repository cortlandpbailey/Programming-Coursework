#include "Showroom.h"
#include "Vehicle.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Showroom::Showroom(string name_, unsigned int capacity_) {
	name = name_;
	capacity = capacity_;
	vector<Vehicle> VehicleList;
}

//vector<Vehicle> VehicleList(0);				//Establish the vector which holds the vehicles.

vector<Vehicle> Showroom::GetVehicleList() {			//Function to return the vector
	
	return VehicleList;
}

void Showroom::AddVehicle(Vehicle v) {				//Add to the vector of Vehicles
	if (VehicleList.size() < capacity) {
		VehicleList.push_back(v);
		
	}
	else {
		cout << "Showroom is full! Cannot add ";	//If its full, say what you cant add. 
		string _error = v.GetYearMakeModel();
		cout <<_error << endl;
	}
}

void Showroom::ShowInventory() {			//Use Display() to show the details of every Vehicle in the vector
	
	if (VehicleList.size() > 0) {
		cout << "Vehicles in " << name << endl;
		for (int i = 0; i < VehicleList.size(); ++i) {
			Vehicle v = VehicleList.at(i);
			v.Display();
		}
	}
	
	else {
		cout << name << " is empty!" << endl;
	}
}

float Showroom::GetInventoryValue() {			//Sum up prices of all Vehicles in vector and show that value.
	float sum = 0;
	for (int i = 0; i < VehicleList.size(); ++i) {
		Vehicle v = VehicleList.at(i);
		sum = sum + v.GetPrice();
	}

	return sum;
}
