#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

mt19937 random_mt;

int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}
void RollDice(int numberOfRolls, int numberOfSides) {
// Create map obj
	map<int, int> DieRolls;
	//Create map items related to the number of sides:
	for (int i = 1; i <= numberOfSides; i++) {
		DieRolls.emplace(i, 0);
	}
	//Roll dice set number of times and store that data 
	for (int i = 0; i < numberOfRolls; i++) {
		int roll = Random(1, numberOfSides);
		int temp = DieRolls[roll];
		DieRolls[roll] = temp+1;
	}

	//print out the results
	for (int i = 1; i <= numberOfSides; i++) {
		cout << i << ": " << DieRolls[i] << endl;
	}
}
class State {
public:
	string name;
	string percapincome;
	string population;
	string medianincome;
	string households;
	State(string n, string pincome, string pop, string mincome, string houses) {
		name = n;
		percapincome = pincome;
		population = pop;
		medianincome = mincome;
		households = houses;
	}
	~State() {}

};
int main()
{
	cout << "1. Random Numbers\n";
	cout << "2. State Info\n";

	int option;
	cin >> option;

	if (option == 1)
	{
		int randomSeed;
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);			//used for testing

		int dieroll;
		cout << "Number of times to roll the die: ";
		// user input
		cin >> dieroll;

		int diesides;
		cout << "Number of sides on this die: ";
		// user input
		cin >> diesides;
		cout << endl;

		  // Roll Dice
		RollDice(dieroll, diesides);
	}
	else if (option == 2)
	{
		// Load the states
		ifstream file("states.csv");
		map<string, State> states;
		if (file.is_open()) {
			string n;
			string pincome; 
			string pop;
			string mincome;
			string hhlds;
			string label;
			getline(file, label, ',');
			getline(file, label, ',');
			getline(file, label, ',');
			getline(file, label, ',');
			getline(file, label);

			while (getline(file, n, ',')) {
				//getline(file, n, ',');
				getline(file, pincome, ',');
				getline(file, pop, ',');
				getline(file, mincome, ',');
				getline(file, hhlds);
				states.emplace(n, State(n, pincome, pop, mincome, hhlds));
			}
		}
		

		int sel;
		// Get input for option 1 (show all states) or 2 (do a search for a particular state)
		cout << "1. Print all states" << endl;
		cout << "2. Search for a state" << endl;
		cin >> sel;
		if (sel == 1) {
			//Display all states
			auto iter = states.begin();
			for (; iter != states.end(); iter++) {
				cout << iter->first << endl;
				cout << "Population: " << iter->second.population << endl;
				cout << "Per Capita Income: " << iter->second.percapincome << endl;
				cout << "Median Household Income: " << iter->second.medianincome << endl;
				cout << "Number of Households: " << iter->second.households << endl;
			}

		}
		else if (sel == 2) {
			//Display chosen state
			string s;
			cin >> s;
			auto iter = states.find(s);
			if (iter != states.end()) {
				cout << iter->first << endl;
				cout << "Population: " << iter->second.population << endl;
				cout << "Per Capita Income: " << iter->second.percapincome << endl;
				cout << "Median Household Income: " << iter->second.medianincome << endl;
				cout << "Number of Households: " << iter->second.households << endl;
			}
			else {
				cout << "No match found for " << s;
			}
		}
	}

	return 0;
}
