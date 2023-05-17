#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class Ships
{
	// Need constructor, only default 
	//Need load function to decode binary file
	//Need Accessors to return attributes

public:
	struct Weapon {
		string WeaponName;
		unsigned int WeaponStrength;
		float PowerUsage;
		friend class Ships;
	};
	/**************** Constructors/Destructors ******************/
	Ships();
	~Ships();
	Ships(string Name, string vesselclass, short Length, int Shield, float Speed);

	/**************** ACCESSORS ******************/
	string& GetName();
	string& GetClass();
	short& GetLength();
	int& GetShieldCapacity();
	float& GetMaxSpeed();
	// Vector Return
	vector<Weapon*>& GetWeapons();


	/****************** INSERTION ********************/
	void NewWeapon(string Name, unsigned int Strength, float Power);


	string ShipName;
	string ShipClass;
	short ShipLength;
	int ShieldCapacity;
	float MaxSpeed;
	vector<Weapon*> ThisShipsWeapons;
	unsigned int WpnCount;
	unsigned int firepower;
	unsigned int bestweapon;
};

