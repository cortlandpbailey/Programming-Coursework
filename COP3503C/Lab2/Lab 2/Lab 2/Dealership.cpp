#include "Dealership.h"
#include <string>
#include <vector>
#include <iostream>
#include "Showroom.h"
#include "Vehicle.h"
using namespace std;

Dealership::Dealership(string name_, unsigned int capacity_) {
	name = name_;
	capacity = capacity_;

}
vector<Showroom> ShowroomList(0);

void Dealership::AddShowroom(Showroom s) {

	if (ShowroomList.size() < capacity) {
		ShowroomList.push_back(s);
		}
	else {
		cout << "Dealership is full, can't add another showroom!\n";	//If its full, say what you cant add. 
	}
}

float Dealership::GetAveragePrice() {		//return the average price of the cars in the dealership.
	float average = 0.00;
	float moneysum = 0.00;
	float carsum = 0;
	for (unsigned int i = 0; i < ShowroomList.size(); ++i) {
		moneysum = moneysum + ShowroomList.at(i).GetInventoryValue();
		carsum = carsum + ShowroomList.at(i).GetVehicleList().size();
	}
	average = moneysum / carsum;
	return average;
}

void Dealership::ShowInventory() {
	if (ShowroomList.size() != 0) {
		for (unsigned int i = 0; i < ShowroomList.size(); ++i) {
			ShowroomList.at(i).ShowInventory();
			cout << endl;
		}
		cout << "Average car price: $" << GetAveragePrice();

	}
	else {
		cout << name << " is empty!" << endl;
		cout << "Average car price: $0.00";

	}
}