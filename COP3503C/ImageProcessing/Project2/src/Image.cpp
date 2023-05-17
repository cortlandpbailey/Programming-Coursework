#include "Image.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Struct Header instantiator:
Image::Header* Image::NewHeader(ifstream& inFile) {
	//Get header data from Infile here:
	Header* info = new Header;
	inFile.read(&info->idLength, sizeof(info->idLength));
	inFile.read(&info->colorMapType, sizeof(info->colorMapType));
	inFile.read((char*)& info->dataTypeCode, sizeof(info->dataTypeCode));
	inFile.read((char*)&info->colorMapOrigin, sizeof(info->colorMapOrigin));
	inFile.read((char*)&info->colorMapLength, sizeof(info->colorMapLength));
	inFile.read(&info->colorMapDepth, sizeof(info->colorMapDepth));
	inFile.read((char*)&info->xOrigin, sizeof(info->xOrigin));
	inFile.read((char*)&info->yOrigin, sizeof(info->yOrigin));
	inFile.read((char*)&info->width, sizeof(info->width));
	inFile.read((char*)&info->height, sizeof(info->height));
	inFile.read(&info->bitsPerPixel, sizeof(info->bitsPerPixel));
	inFile.read(&info->imageDescriptor, sizeof(info->imageDescriptor));
	return info;
}

Image::pixel* Image::NewPixel(unsigned char blue, unsigned char green, unsigned char red) {
	pixel* pix = new pixel;
	pix->blue = blue;
	pix->red = red;
	pix->green = green;
	return pix;
}

//Read in pixels from file and return vector
void Image::addPixels(ifstream& inFile) {
	//loop through file to store all the pixel data
	unsigned long size = this->width * this->height;
	vector<pixel*> data;
	for (unsigned long i = 0; i < size; i++) {
		pixel* p = new pixel;
		inFile.read((char*)&p->blue, sizeof(p->blue));
		inFile.read((char*)&p->green, sizeof(p->green));
		inFile.read((char*)&p->red, sizeof(p->red));
		data.push_back(p);
	}
	this->pixels = data;
}

//Image class method of returning header:
Image::Header* Image::GetHeader() {
	return info;
}

unsigned int& Image::GetHeight() {
	return height;
}

unsigned int& Image::GetWidth() {
	return width;
}

const unsigned long& Image::GetSize() const {
	return size;
}

vector<Image::pixel*>& Image::GetPixels() {
	return pixels;
}

const vector<Image::pixel*>& Image::GetPixels() const{
	return pixels;
}

//Image class function to add header:
void Image::AddHeader(ifstream& inFile) {
	this->info = Image::NewHeader(inFile);		//Create a new instance of the struct with passed in info;
	this->width = info->width;
	this->height = info->height;
	//cout << "width : " << info->width << endl;
	//cout << "height:" << info->height << endl;
}

void Image::WriteImage(fstream& outFile) {
	outFile.write(&info->idLength, sizeof(info->idLength));
	outFile.write(&info->colorMapType, sizeof(info->colorMapType));
	outFile.write(&info->dataTypeCode, sizeof(info->dataTypeCode));
	outFile.write((char*)&info->colorMapOrigin, sizeof(info->colorMapOrigin));
	outFile.write((char*)&info->colorMapLength, sizeof(info->colorMapLength));
	outFile.write(&info->colorMapDepth, sizeof(info->colorMapDepth));
	outFile.write((char*)&info->xOrigin, sizeof(info->xOrigin));
	outFile.write((char*)&info->yOrigin, sizeof(info->yOrigin));
	outFile.write((char*)&info->width, sizeof(info->width));
	outFile.write((char*)&info->height, sizeof(info->height));
	outFile.write(&info->bitsPerPixel, sizeof(info->bitsPerPixel));
	outFile.write(&info->imageDescriptor, sizeof(info->imageDescriptor));

	for (unsigned long j = 0; j < pixels.size(); j++) {
		outFile.write((char*)&pixels.at(j)->blue, sizeof(pixels.at(j)->blue));
		outFile.write((char*)&pixels.at(j)->green, sizeof(pixels.at(j)->green));
		outFile.write((char*)&pixels.at(j)->red, sizeof(pixels.at(j)->red));
	}

}

// Default constructor
Image::Image() {
	info = AddHeader();
	width = info->width;
	height = info->height;
	size = width * height;
	vector<pixel*> pixels;
}

// copy assignment operator for creating a duplicate of a given Image
Image::Image(const Image& i) {
	width = i.width;
	height = i.height;
	info = i.info;
	pixels = i.pixels;
	size = i.size;
}

//Destructor: Clears vector of pixels and deletes the header
Image::~Image() {
	//Delete pixels and header
	pixels.clear();
	delete info;
}

bool Image::operator==(const Image& rhs) {
	bool _equal = true;
	if (this->info->bitsPerPixel != rhs.info->bitsPerPixel)						//Check if header for passed in Image matches the header of this Image
		_equal = false;
	else if (info->height != rhs.info->height)
		_equal = false;
	else if (info->width != rhs.info->width)
		_equal = false;
	else {
		for (unsigned long j = 0; j < size; j++) {		//Iterate and check each individual pixel if it equals the one passed in
			if (pixels.at(j)->blue != rhs.pixels.at(j)->blue)
				_equal = false;
			else if (pixels.at(j)->green != rhs.pixels.at(j)->green)
				_equal = false;
			else if (pixels.at(j)->red != rhs.pixels.at(j)->red)
				_equal = false;
		}
	}
	return _equal;
}

bool Image::Compare(const Image& rhs) {
	bool _equal = true;
	if (this->info->bitsPerPixel != rhs.info->bitsPerPixel)						//Check if header for passed in Image matches the header of this Image
		_equal = false;
	else if (info->height != rhs.info->height)
		_equal = false;
	else if (info->width != rhs.info->width)
		_equal = false;
	else if (pixels.size() != rhs.pixels.size())
		_equal = false;
	else {
		for (unsigned long j = 0; j < pixels.size(); j++) {		//Iterate and check each individual pixel if it equals the one passed in
			if (pixels.at(j)->blue != rhs.pixels.at(j)->blue)
 				_equal = false;
			else if (pixels.at(j)->green != rhs.pixels.at(j)->green)
				_equal = false;
			else if (pixels.at(j)->red != rhs.pixels.at(j)->red)
				_equal = false;
		}
	}
	return _equal;
}

// Remove all pixels inside an image, leaving the header
void Image::ClearPixels() {
	pixels.clear();
}

void Image::AddHeader(Header* head) {
	info = head;								//If passed in an existing header, save that as the current one
	width = head->width;
	height = head->height;
	size = width * height;
}

Image::Header* Image::AddHeader() {
	Header* h = new Header;
	return h;
}

void Image::addPixels(vector<pixel*>& p) {
	this->pixels = p;
}

void Image::AddBlankPixels(unsigned long _size) {
	vector<Image::pixel*> pix;
	for (unsigned long j = 0; j < _size; j++) {
		Image::pixel* p = new Image::pixel;
		p->blue = 0;
		p->green = 0;
		p->red = 0;
		pix.push_back(p);
	}
	this->pixels = pix;
}

void Image::Multiply(const Image* top, const Image* bot) {
	float x = 255.00f;
	vector<Image::pixel*> pix;
	vector < Image::pixel* > t = top->GetPixels();
	vector < Image::pixel* > b = bot->GetPixels();
	unsigned long size = top->GetSize();
	for (unsigned long j = 0; j < size; j++) {
		Image::pixel* p = new Image::pixel;
		p->blue = (((float)t.at(j)->blue * (float)b.at(j)->blue) / x)+0.5f;
		p->green = (((float)t.at(j)->green * (float)b.at(j)->green) / x) +0.5f;
		p->red = (((float)t.at(j)->red * (float)b.at(j)->red) / x) + 0.5f;
		pix.push_back(p);
	}
	this->pixels = pix;
}

Image::pixel* Image::MultiplyPixels(const pixel* a, const pixel* b) {
	float x = 255.00f;
	pixel* p = new pixel;
	p->blue =  (2.0f * ((float)a->blue * (float)b->blue) / x) + 0.5f;
	p->green = (2.0f * ((float)a->green * (float)b->green) / x) + 0.5f;
	p->red =   (2.0f * ((float)a->red * (float)b->red) / x) + 0.5f;
	return p;
}

Image::pixel* Image::MultiplyPixels(const pixel* a, float b) {
	float x = 255.0f;
	pixel* p = new pixel;
	p->blue = (((float)a->blue/x * b) * x) + 0.5f;
	p->green = (((float)a->green/x * b) * x) + 0.5f;
	p->red = (((float)a->red/x * b) * x) + 0.5f;
	return p;
}

void Image::Multiply(const Image* top, int _blue, int _green, int _red) {
	int x = 255;
	vector<Image::pixel*> pix;
	vector < Image::pixel* > t = top->GetPixels();
	unsigned long size = top->height * top->width;
	for (unsigned long j = 0; j < size; j++) {
		Image::pixel* p = new Image::pixel;
		p->blue = clamp(((int)t.at(j)->blue * _blue), 0, 255);
		p->green = clamp(((int)t.at(j)->green * _green), 0, 255);
		p->red = clamp(((int)t.at(j)->red * _red), 0, 255);
		pix.push_back(p);
	}
	this->pixels = pix;
} 

void Image::Subtract(const Image* top, const Image* bot) {
	vector<Image::pixel*> pix;
	vector < Image::pixel* > b = top->GetPixels();
	vector < Image::pixel* > t = bot->GetPixels();
	unsigned long size = top->GetSize();
	for (unsigned long j = 0; j < size; j++) {
		Image::pixel* p = new Image::pixel;
		p->blue = clamp(((int)t.at(j)->blue - (int)b.at(j)->blue), 0, 255);
		p->green = clamp(((int)t.at(j)->green - (int)b.at(j)->green), 0, 255);
		p->red = clamp(((int)t.at(j)->red - (int)b.at(j)->red), 0, 255);
		pix.push_back(p);
	}
	this->pixels = pix;
}

void Image::Blue(const Image* top) {
	vector<Image::pixel*> pix;
	vector < Image::pixel* > t = top->GetPixels();
	unsigned long size = top->GetSize();
	for (unsigned long j = 0; j < size; j++) {
		Image::pixel* p = new Image::pixel;
		p->blue = t.at(j)->blue;
		p->green = t.at(j)->blue;
		p->red = t.at(j)->blue;
		pix.push_back(p);
	}
	this->pixels = pix;
}

void Image::Green(const Image* top) {
	vector<Image::pixel*> pix;
	vector < Image::pixel* > t = top->GetPixels();
	unsigned long size = top->GetSize();
	for (unsigned long j = 0; j < size; j++) {
		Image::pixel* p = new Image::pixel;
		p->blue = t.at(j)->green;
		p->green = t.at(j)->green;
		p->red = t.at(j)->green;
		pix.push_back(p);
	}
	this->pixels = pix;
}

void Image::Red(const Image* top) {
	vector<Image::pixel*> pix;
	vector < Image::pixel* > t = top->GetPixels();
	unsigned long size = top->GetSize();
	for (unsigned long j = 0; j < size; j++) {
		Image::pixel* p = new Image::pixel;
		p->blue = t.at(j)->red;
		p->green = t.at(j)->red;
		p->red = t.at(j)->red;
		pix.push_back(p);
	}
	this->pixels = pix;
}

void Image::Add(const Image* top, int _blue, int _green, int _red) {
	vector<Image::pixel*> pix;
	vector < Image::pixel* > t = top->GetPixels();
	unsigned long size = top->GetSize();
	for (unsigned long j = 0; j < size; j++) {
		Image::pixel* p = new Image::pixel;
		p->blue = clamp(((int)t.at(j)->blue + _blue), 0, 255);
		p->green = clamp(((int)t.at(j)->green + _green), 0, 255);
		p->red = clamp(((int)t.at(j)->red + _red), 0, 255);
		pix.push_back(p);
	}
	this->pixels = pix;
}

void Image::Add(const Image* top, string color) {
	vector<Image::pixel*> pix = this->GetPixels();
	vector<Image::pixel*> t   = top->GetPixels();
	unsigned long size = 238800;
	for (unsigned long j = 0; j < size; j++) {
		if (color == "blue")
			pix.at(j)->blue = t.at(j)->blue;
		else if (color == "green")
			pix.at(j)->green = t.at(j)->green;
		else if (color == "red")
			pix.at(j)->red = t.at(j)->red;
	}
}

void Image::Screen(const Image* top, const Image* bot) {
	vector<Image::pixel*> pix;
	Image* t = new Image(*top);
	Image* b = new Image(*bot);
	t->Negative(t);
	b->Negative(b);

	Image* temp = new Image(); 
	temp->Multiply(t, b);
	temp->Negative(temp);
	this->pixels = temp->pixels;
}

Image::pixel* Image::ScreenPixel(const pixel* a, const pixel* b) {
	pixel* p = new pixel;
	pixel* x = new pixel;
	pixel* y = new pixel;
	x->blue = 255 - a->blue;
	x->green = 255 - a->green;
	x->red = 255 - a->red;
	y->blue = 255 - b->blue;
	y->green = 255 - b->green;
	y->red = 255 - b->red;

	p = MultiplyPixels(x, y);
	//p = MultiplyPixels(p, 2.0f);
	p->blue = 255 - p->blue;
	p->green = 255 - p->green;
	p->red = 255 - p->red;
	delete x;
	delete y;
	return p;
}

void Image::Negative(const Image* top) {
	vector<Image::pixel*> pix;
	vector < Image::pixel* > t = top->GetPixels();
	for (unsigned long j = 0; j < t.size(); j++) {
		Image::pixel* p = new Image::pixel;
		p->blue = 255 - t.at(j)->blue;
		p->green = 255 - t.at(j)->green;
		p->red = 255 - t.at(j)->red;
		pix.push_back(p);
	}
	this->pixels = pix;
}

bool Image::Gray(const pixel* p) const {
	bool gray = true;
	if (p->blue > 127)
		gray = false;


	if (p->green > 127)
		gray = false;

	if (p->red > 127)
		gray = false;

	return gray;
}

void Image::Overlay(const Image* top, const Image* bot) {
	vector<pixel*> pix;
	for (unsigned long j = 0; j < top->pixels.size(); j++) {
		if (Gray(bot->pixels.at(j))) {
			pixel* p = MultiplyPixels(top->pixels.at(j), bot->pixels.at(j));
			//p = MultiplyPixels(p, 2.0f);
			pix.push_back(p);
		}
		else {
			pixel* p = ScreenPixel(top->pixels.at(j), bot->pixels.at(j));
			pix.push_back(p);
		}
	}
	this->pixels = pix;
}

void Image::Flip(const Image* top) {
	vector<Image::pixel*> pix;
	vector<Image::pixel*> t = top->GetPixels();
	for (unsigned long j = 0; j < t.size(); j++) {
		Image::pixel* p = new Image::pixel;
		p->blue = t.at(t.size()-1 - j)->blue;
		p->green = t.at(t.size()-1 - j)->green;
		p->red = t.at(t.size()-1 - j)->red;
		pix.push_back(p);
	}
	this->pixels = pix;
}

unsigned char Image::clamp(int x, int min, int max) {
	if (x < min) return (unsigned char)min;
	else if (x > max) return (unsigned char)max;
	else return (unsigned char)x;
}
