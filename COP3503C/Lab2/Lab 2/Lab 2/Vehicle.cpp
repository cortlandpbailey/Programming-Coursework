#include "Vehicle.h"
#include <iostream>
#include <string>
using namespace std;

	
Vehicle::Vehicle() {			//default constructor
	make = "COP3503";
	model = "Rust Bucket";
	year = 1900;
	price = 0;
	mileage = 0;
};
Vehicle::Vehicle(string _make, string _model,unsigned int _year, float _price,unsigned int _mileage) {		//User input constructor
	make = _make;
	model = _model;
	year = _year;
	price = _price;
	mileage = _mileage;
};
	
//Accessors
void Vehicle::Display() {
	
	cout << year << " " << make << " " << model << " $" << price << " " << mileage << endl; // print out the info

};
string Vehicle::GetYearMakeModel() {
	string y = to_string(year);

	string ymm = y + " " + make + " " + model;
	return ymm;


};

float Vehicle::GetPrice() {

	return price;

};