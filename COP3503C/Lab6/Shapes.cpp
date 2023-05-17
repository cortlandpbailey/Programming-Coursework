#include "Shapes.h"
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
const float PI = 3.14159f;
using namespace std;

Shape::Shape() {}
Shape::~Shape() {}

/************************** Shape 2D functions **********************************/
Shape2D::Shape2D() {}
Shape2D::~Shape2D() {}
//Define 2D >
bool Shape2D::operator>(const Shape2D& rhs) const {
	if (this->Area() > rhs.Area()) {
		return true;
	}
	else return false;
}
//Define 2D <
bool Shape2D::operator<(const Shape2D& rhs) const {
	if (this->Area() < rhs.Area()) {
		return true;
	}
	else return false;
}
//Define 2D ==
bool Shape2D::operator==(const Shape2D& rhs) const {
	if (this->Area() == rhs.Area()) {
		return true;
	}
	else return false;
}
//Define 2D Show Area:
void Shape2D::ShowArea() const {
	cout << "The area of the " << this->GetName2D() << " is : ";
	cout << this->Area() << endl;
}

/************************** Shape 3D functions **********************************/

Shape3D::~Shape3D()  {}
void Shape3D::ShowVolume() const {
	cout << "The volume of the " << this->GetName3D() <<" is : ";
	cout << this->Volume() << endl;
}
bool Shape3D::operator>(const Shape3D& rhs) const {
	if (this->Volume() > rhs.Volume()) {
		return true;
	}
	else return false;
}
bool Shape3D::operator<(const Shape3D& rhs) const {
	if (this->Volume() < rhs.Volume()) {
		return true;
	}
	else return false;
}
bool Shape3D::operator==(const Shape3D& rhs) const {
	if (this->Volume() == rhs.Volume()) {
		return true;
	}
	else return false;
}

/***************************** TRIANGLE ************************************/
//Default constructor for Triangle
Triangle::Triangle() {
	base = 0.0f;
	height = 0.0f;
	name = "Triangle";
}
//Constructor for Triangle
Triangle::Triangle(float b, float h) {
	base = b;
	height = h;
	name = "Triangle";
}
//Copy Constructor for Triangle
Triangle::Triangle(const Triangle& t) {
	this->base = t.base;
	this->height = t.height;
	name = "Triangle";
}
//Define how a Triangle uses Scale from Shape:
void Triangle::Scale(float scaleFactor) {
	base = base * scaleFactor;
	height = height * scaleFactor;
}
//Define how a Triangle uses Display from Shape:
void Triangle::Display() const {
	cout << "The area of the Triangle is: " << Area() << endl;
	cout << "Base: " << base << endl;
	cout << "Height: " << height << endl;
}
//Define 2D shape Area from Shape2D:
float Triangle::Area() const {
	return (0.5f * base * height);
}
//Define Triangle Getname from Shape2D:
string Triangle::GetName2D() const {
	return name;
}
//Destructor
Triangle::~Triangle() {}

/************************ CIRCLE *************************************/
//Default constructor for a Circle
Circle::Circle() {
	radius = 0.0f;
	name = "Circle";
}
//Constructor for circle
Circle::Circle(float rad) {
	radius = rad;
	name = "Circle";
}
//Copy Constructor for Circle
Circle::Circle(const Circle& c) {
	this->radius = c.radius;
	name = "Circle";
}
//Destructor
Circle::~Circle() {}
//Define how a Circle uses Scale from Shape:
void Circle::Scale(float scaleFactor) {
	radius = radius * scaleFactor;
}
//Define how a Circle uses Display from Shape:
void Circle::Display() const {
	cout << "The area of the Circle is: " << Area() << endl;
	cout << "Radius: " << radius << endl;
}
//Define Circle Area from Shape2D:
float Circle::Area() const {
	float temp = PI * pow(radius, 2.0f);
	return temp;
}
//Define Circle Getname from Shape2D:
string Circle::GetName2D() const {
	return name;
}
//return the radius of the Circle:
float Circle::getRadius() const {
	return radius;
}

/*********************** SQUARE ****************************************/
//Default constructor for a square
Square::Square() {
	side = 0;
	name = "Square";
}
//Constructor for a square
Square::Square(float s) {
	side = s;
	name = "Square";
}
//Copy Constructor for Square
Square::Square(const Square& s) {
	this->side = s.side;
	name = "Square";
}
//Destructor
Square::~Square() {}
//Define how a Square uses Scale from Shape:
void Square::Scale(float scaleFactor) {
	side = side * scaleFactor;
}
//Define how a Square uses Display from Shape:
void Square::Display() const {
	cout << "The area of the Square is: " << Area() << endl;
	cout << "Length of a side: " << side << endl;
}
//Define Square Area from Shape2D:
float Square::Area() const {
	float temp =pow(side, 2.0f);
	return temp;
}
//Define Square Getname from Shape2D:
string Square::GetName2D() const {
	return name;
}

/************************** SPHERE ******************************************/
// Default Constr for Sphere
Sphere::Sphere() : Circle(0.0f) {
	name = "Sphere";
}
//Constructor:
Sphere::Sphere(float radius) : Circle(radius) {
	name = "Sphere";
}
//Destructor
Sphere::~Sphere() {}
//Scale the Sphere
void Sphere::Scale(float scaleFactor) {
	Circle::Scale(scaleFactor);
}
//Display the sphere info
void Sphere::Display() const {
	cout << "The volume of the Sphere is: " << Volume() << endl;
	Circle::Display();
}
//Return the name of the 3D Shape
string Sphere::GetName3D() const {
	return name;
}
// Return the volume of the 3D shape
float Sphere::Volume() const {
	float temp = (4.0f / 3.0f) * PI * pow(getRadius(), 3.0f);
	return temp;
}
/************************** TRIANGULAR PYRAMID ******************************************/
//Default Constr
TriangularPyramid::TriangularPyramid() : Triangle() {
	height = 0.0f;
	name = "Triangular Pyramid";
}
//Constructor
TriangularPyramid::TriangularPyramid(float _height, float base, float t_height) : Triangle(base, t_height) {
	height = _height;
	name = "Triangular Pyramid";
}
//Destuctor
TriangularPyramid::~TriangularPyramid() {}
//return volume of the pyramid
float TriangularPyramid::Volume() const {
	float temp = 1.0f / 3.0f * Triangle::Area() * height;
	return temp;
}
//Get pyramid name
string TriangularPyramid::GetName3D() const {
	return name;
}
//Scale pyramid
void TriangularPyramid::Scale(float scaleFactor) {
	Triangle::Scale(scaleFactor);
	height = height * scaleFactor;
}
//Display Pyramid info
void TriangularPyramid::Display() const {
	cout << "The volume of the Triangular Pyramid is: " << Volume() << endl;
	cout << "The height is: " << height << endl;
	Triangle::Display();
}
/************************** Cylinder ******************************************/
//Default Constr
Cylinder::Cylinder() : Circle(0.0f) {
	height = 0.0f;
	name = "Cylinder";
}
//Constructor
Cylinder::Cylinder(float _height, float radius) : Circle(radius) {
	height = _height;
	name = "Cylinder";
}
//Destructor
Cylinder::~Cylinder() {}
//Get the volume
float Cylinder::Volume() const {
	float temp = Circle::Area() * height;
	return temp;
}
//Get the 3D name
string Cylinder::GetName3D() const {
	return name;
}
//Display the cylinder info
void Cylinder::Display() const {
	cout << "The volume of the Cylinder is: " << Volume() << endl;
	cout << "The height is: " << height << endl;
	Circle::Display();
}
//Scale Cylinder by given value
void Cylinder::Scale(float scaleFactor) {
	Circle::Scale(scaleFactor);
	height = height * scaleFactor;
}
