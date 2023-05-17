#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Ships.h"
using namespace std;

//Function Dec
vector<Ships*> AddShips(ifstream& inFile);
void Display(Ships* ship);

int main()
{
	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;
	vector<Ships*> Friendly;			//Storage for all of the Friendly ships we take in. 
	vector<Ships*> Enemy;			//Storage for all enemy ships

	/* Load files here */
	if (option == 1) {
		ifstream inFile("friendlyships.shp", ios_base::binary);				//Open File
		Friendly = AddShips(inFile);
		inFile.close();

	}
	else if (option == 2) {
		ifstream inFile("enemyships.shp", ios_base::binary);
		Enemy = AddShips(inFile);
		inFile.close();
	}

	else if (option == 3) {
		ifstream inFile("friendlyships.shp", ios_base::binary);				//Open File
		Friendly = AddShips(inFile);
		inFile.close();

		ifstream EnemyFile("enemyships.shp", ios_base::binary);
		Enemy = AddShips(EnemyFile);
		EnemyFile.close();
	}
	
	cout << "1. Print all ships" << endl;							//Cout each attribute
	cout << "2. Starship with the strongest weapon" << endl;		//Functions to compare each: 
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;

	cin >> option;

	//Display all ships loaded from files
	if (option == 1) {
		for (unsigned int i = 0; i < Friendly.size(); i++) {
			Display(Friendly.at(i));
		}
		for (unsigned int i = 0; i < Enemy.size(); i++) {
			Display(Enemy.at(i));
		}
	}

	// Find the ship with the strongest weapon
	else if (option == 2) {
		Ships* strong = new Ships();
		for (unsigned int i = 0; i < Friendly.size(); i++) {
			Ships* temp = Friendly.at(i);
			if (temp->bestweapon > strong->bestweapon) {
				strong = temp;
			}
		}
		for (unsigned int i = 0; i < Enemy.size(); i++) {
			Ships* temp = Enemy.at(i);
			if (temp->bestweapon > strong->bestweapon) {
				strong = temp;
			}
		}
		//Display the Strong ship here:
		Display(strong);
		delete strong;
	}

	//Find the strongest overall ship (total firepower)
	else if (option == 3) {
		Ships* strongest = new Ships();
		for (unsigned int i = 0; i < Friendly.size(); i++) {
			Ships* temp = Friendly.at(i);
			if (temp->firepower > strongest->firepower) {
				strongest = temp;
			}
		}
		for (unsigned int i = 0; i < Enemy.size(); i++) {
			Ships* temp = Enemy.at(i);
			if (temp->firepower > strongest->firepower) {
				strongest = temp;
			}
		}
		//Display the Strongest ship here:
		Display(strongest);
		delete strongest;
	}

	//find the weakest ship with wpncount > 0
	else if (option == 4) {
		Ships* weakest = new Ships();
		weakest->firepower = 1000;
		for (unsigned int i = 0; i < Friendly.size(); i++) {
			Ships* temp = Friendly.at(i);
			if (temp->WpnCount != 0) {
				if (temp->firepower < weakest->firepower) {
					weakest = temp;
				}
			}
		}
		for (unsigned int i = 0; i < Enemy.size(); i++) {
			Ships* temp = Enemy.at(i);
			if (temp->WpnCount != 0) {
				if (temp->firepower < weakest->firepower) {
					weakest = temp;
				}
			}
		}
		Display(weakest);
		delete weakest;
	}

	//List out ships with wpncount = 0
	else if (option == 5) {
		vector<Ships*> unarmed;
		for (unsigned int i = 0; i < Friendly.size(); i++) {
			if (Friendly.at(i)->WpnCount == 0) {
				Ships* temp = Friendly.at(i);
				unarmed.push_back(temp);
			}
		}

		for (unsigned int i = 0; i < Enemy.size(); i++) {
			if (Enemy.at(i)->WpnCount == 0) {
				Ships* temp = Enemy.at(i);
				unarmed.push_back(temp);
			}
		}
		for (unsigned int i = 0; i < unarmed.size(); i++) {
			Display(unarmed.at(i));
		}
	}
	return 0;
}

//Function Definitions:
vector<Ships*> AddShips(ifstream &inFile) {
	vector<Ships*> newships;

	unsigned int shipcount;												//Start by getting the number of ships to read
	inFile.read((char*)&shipcount, sizeof(shipcount));
	for (unsigned int i = 0; i < shipcount; i++) {						//For each ship in the file, grab the relevant data
		//Obtain how long the name is
		unsigned int namelength;
		inFile.read((char*)&namelength, sizeof(namelength));
		//Read in and convert the name to a string. 
		char* tempname = new char[namelength];
		inFile.read(tempname, namelength);
		string Name = tempname;
		delete[] tempname;

		unsigned int classlength;
		inFile.read((char*)&classlength, sizeof(classlength));
		//Read in and convert the name to a string. 
		tempname = new char[classlength];
		inFile.read(tempname, classlength);
		string shipclass = tempname;
		delete[] tempname;

		//Read in the length of the ship
		short length;
		inFile.read((char*)&length, sizeof(length));

		//Read in and store the Capacity of the shield
		unsigned int shieldcap;
		inFile.read((char*)&shieldcap, sizeof(shieldcap));

		//Read in and store Max warpspeed of the ship			
		float warp;
		inFile.read((char*)&warp, sizeof(warp));

		newships.push_back(new Ships(Name, shipclass, length, shieldcap, warp));

		//Get the amount of weapons on the ship
		unsigned int wpncount;
		inFile.read((char*)&wpncount, sizeof(wpncount));
		for (unsigned int j = 0; j < wpncount; j++) {
			//Read in and store the length of the name of the weapon
			unsigned int wpnnamelength;
			inFile.read((char*)&wpnnamelength, sizeof(wpnnamelength));

			//Read in and convert the name to a string. 
			char* tempname = new char[wpnnamelength];
			inFile.read(tempname, wpnnamelength);
			string wpnname = tempname;
			delete[] tempname;

			//read in and store the Strength of the weapon
			unsigned int wpnstr;
			inFile.read((char*)&wpnstr, sizeof(wpnstr));

			//Read in and store the power consumption of the weapon
			float wpnpower;
			inFile.read((char*)&wpnpower, sizeof(wpnpower));
			newships.at(i)->NewWeapon(wpnname, wpnstr, wpnpower);
		}



	}


	return newships;
}

void Display(Ships* ship) {

	cout << "Name: " << ship->ShipName << endl;
	cout << "Class: " << ship->ShipClass << endl;
	cout << "Length: " << ship->ShipLength << endl;
	cout << "Shield capacity: " << ship->ShieldCapacity << endl;
	cout << "Maximum Warp: " << ship->MaxSpeed << endl;
	cout << "Armaments: " << endl;
	if (ship->WpnCount == 0)
		cout << "Unarmed";
	else {
		for (unsigned int i = 0; i < ship->WpnCount; i++) {
			cout << ship->ThisShipsWeapons.at(i)->WeaponName << ", ";
			cout << ship->ThisShipsWeapons.at(i)->WeaponStrength << ", ";
			cout << ship->ThisShipsWeapons.at(i)->PowerUsage << endl;

		}
		cout << "Total firepower: " << ship->firepower << endl << endl;
	}

}