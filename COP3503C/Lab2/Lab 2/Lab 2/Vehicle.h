#pragma once
#include <iostream>
#ifndef VEHICLE_H
#define VEHICLE_H



using namespace std;


class Vehicle
{
public:
	//Constructors
	Vehicle();
	Vehicle(string _make, string _model, unsigned int _year, float _price, unsigned int _mileage);

	//Accessors
	void Display();
	string GetYearMakeModel();
	float GetPrice();
private:
	string make;
	string model;
	unsigned int year;
	float price;
	unsigned int mileage;


};

#endif // !VEHICLE_H
