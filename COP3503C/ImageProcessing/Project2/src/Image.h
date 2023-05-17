#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Image class is specifically for storing data read in from binary file. Accessors and mutators for modifying the image data.

class Image {
public:
	struct Header;
	struct pixel;

	/************** ACCESSORS **************/
	Header* GetHeader();
	unsigned int& GetHeight();
	unsigned int& GetWidth();
	vector<pixel*>& GetPixels();
	const vector<pixel*>& GetPixels() const;
	const unsigned long& GetSize() const;

	/************** INSERTION **************/
	void AddHeader(ifstream& inFile);
	void AddHeader(Header* head);
	Header* AddHeader();
	void AddBlankPixels(unsigned long size);
	void addPixels(ifstream& inFile);
	void addPixels(vector<pixel*>& p);

	/************** WRITE OUT FUNCTIONS **************/
	void WriteImage(fstream& outFile);

	/************** OPERATORS ************************/
	bool operator==(const Image& rhs);
	bool Compare(const Image& rhs);
	void ClearPixels();
	void Add(const Image* top, int _blue, int _green, int _red);
	void Add(const Image* top, string color);
	void Multiply(const Image* top, const Image* bot);
	void Multiply(const Image* top, int _blue, int _green, int _red);
	pixel* MultiplyPixels(const pixel* a, const pixel* b);
	pixel* MultiplyPixels(const pixel* a, float b);
	vector<Image::pixel*>& Invert(const vector<pixel*> top);
	void Subtract(const Image* top, const Image* bot);
	void Screen(const Image* top, const Image* bot);
	pixel* ScreenPixel(const pixel* a, const pixel* b);
	void Overlay(const Image* top, const Image* bot);
	void Negative(const Image* top);
	bool Gray(const pixel* p) const;
	void Flip(const Image* top);
	void Blue(const Image* top);
	void Green(const Image* top);
	void Red(const Image* top);
	unsigned char clamp(int x, int min, int max);

	/************** CONSTRUCTOR/DESTRUCTOR **************/
	Image();					//default constructor
	Image(const Image& i);		//copy constructor
	~Image();					// Destructor

	//Structs for Header and Pixel:
	struct Header {
		char idLength = 0;
		char colorMapType = 0;
		char dataTypeCode = 2;
		short colorMapOrigin = 0;
		short colorMapLength = 0;
		char colorMapDepth = 0;
		short xOrigin = 0;
		short yOrigin = 0;
		short width = 512;
		short height = 512;
		char bitsPerPixel = 24;
		char imageDescriptor = 0;
		friend class Image;
	};

	struct pixel {
		unsigned char blue;
		unsigned char green;
		unsigned char red;
	};


private: 
	vector<pixel*> pixels;		// Image is a collection of pixels, here is the pixel data
	Header* info;				// Storage of the header info
	unsigned int width;		//default size
	unsigned int height;
	unsigned long size;
	Header* NewHeader(ifstream& inFile);		//Header struct function to create new instance of itself
	pixel* NewPixel(unsigned char blue, unsigned char green, unsigned char red);
};

