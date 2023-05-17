#include "Ships.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;



void Ships::NewWeapon(string Name, unsigned int Strength, float Power) {
	Weapon* wpn = new Weapon;
	wpn->WeaponName = Name;
	wpn->WeaponStrength = Strength;
	wpn->PowerUsage = Power;
	WpnCount++;
	firepower += Strength;
	if (Strength > this->bestweapon) {
		bestweapon = Strength;
	}
	ThisShipsWeapons.push_back(wpn);
}

Ships::Ships() {
	ShipName = "Default";
	ShipClass = "SHIP";
	ShipLength = 0;
	ShieldCapacity = 0;
	MaxSpeed = 0.0;
	firepower = 0;
	bestweapon = 0;
	WpnCount = 0;
}

Ships::~Ships() {
//	Weapon* ptr = &ThisShipsWeapons.at(0);
//	for (int i = 0; i < ThisShipsWeapons.size(); i++) {
//		delete ThisShipsWeapons.at(i);
//	}
	ThisShipsWeapons.clear();
}

Ships::Ships(string Name, string vesselclass, short Length, int Shield, float Speed) {
	ShipName = Name;
	ShipClass = vesselclass;
	ShipLength = Length;
	ShieldCapacity = Shield;
	MaxSpeed = Speed;
	firepower = 0;
	bestweapon = 0;
	WpnCount = 0;
}

/**************** ACCESSORS ******************/
string& Ships::GetName() {
	return ShipName;
}

string& Ships::GetClass() {
	return ShipClass;
}

short& Ships::GetLength() {
	return ShipLength;
}
int& Ships::GetShieldCapacity() {
	return ShieldCapacity;
}
float& Ships::GetMaxSpeed() {
	return MaxSpeed;
}

// Vector Return
vector<Ships::Weapon*>& Ships::GetWeapons() {
	return this->ThisShipsWeapons;
}


