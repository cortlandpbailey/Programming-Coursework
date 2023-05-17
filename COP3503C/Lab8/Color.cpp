#include "Color.h"
#include <string>

using namespace std;
const int tff = 255;
string hexconv(unsigned char r) {
	string hexname;
	
	int temp = (int)r / 16;
	if (temp < 10) 
		hexname += to_string(temp);

	else if (temp == 10)
		hexname += 'A';
	else if (temp == 11)
		hexname += 'B';
	else if (temp == 12)
		hexname += 'C';
	else if (temp == 13)
		hexname += 'D';
	else if (temp == 14)
		hexname += 'E';
	else if (temp == 15)
		hexname += 'F';
	else
		hexname += 'X';

	temp = (int)r % 16;
	if (temp < 10)
		hexname  += to_string(temp);
	else if (temp == 10)
		hexname += 'A';
	else if (temp == 11)
		hexname += 'B';
	else if (temp == 12)
		hexname += 'C';
	else if (temp == 13)
		hexname += 'D';
	else if (temp == 14)
		hexname += 'E';
	else if (temp == 15)
		hexname += 'F';
	else
		hexname += 'X';


	return hexname;
}


Color::Color() {
	Name = "Empty Color";
	HexValue = "000000";
}

Color::Color(const Color& c) {
	Name = c.Name;
	HexValue = c.HexValue;
	R = c.R;
	G = c.G;
	B = c.B;
	value = c.value;
}

Color::Color(string n, int h) {
	Name = n;
	value = h;
	B = (unsigned char)(h & tff);	// lowest 8 bits correspond to blue value
	G = (unsigned char)(h >> 8) & tff;	//shift right 8 bits to get the green value
	R = (unsigned char)(h >> 16) & tff;	// shift right 8 more, total of 16 to get the red value
	HexValue = hexconv(R) + hexconv(G) + hexconv(B);
}

Color::~Color() {

}

string Color::GetName() const {
	return Name;
}

string Color::GetHexValue() const {
	return HexValue;
}

unsigned char Color::GetR() const {
	return R;
}

unsigned char Color::GetG() const {
	return G;
}

unsigned char Color::GetB() const {
	return B;
}

void Color::SetValue(int val) {
	value = val;
	B = (unsigned char)(val & tff);	// lowest 8 bits correspond to blue value
	G = (unsigned char)(val >> 8) & tff;	//shift right 8 bits to get the green value
	R = (unsigned char)(val >> 16) & tff;	// shift right 8 more, total of 16 to get the red value
	HexValue = hexconv(R) + hexconv(G) + hexconv(B);
}

void Color::SetName(const char* name) {
	Name = name;
}