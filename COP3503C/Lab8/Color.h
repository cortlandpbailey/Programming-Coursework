#pragma once
#include <cstdlib>
#include <string>
using namespace std;

class Color
{
private:
	std::string Name;
	string HexValue;
	unsigned char R = 00;
	unsigned char G = 00;
	unsigned char B = 00;
	int value = 0;

public:
	Color();
	Color(const Color& c);
	Color(string n, int h);
	~Color();
	string GetName() const;
	string GetHexValue() const;
	unsigned char GetR() const;
	unsigned char GetG() const;
	unsigned char GetB() const;
	void SetValue(int val);
	void SetName(const char* name);
};

