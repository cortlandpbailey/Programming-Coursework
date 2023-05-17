#pragma once
#include <string>
using namespace std;

class Shape
{
public:
	virtual void Scale(float scaleFactor) = 0;
	virtual void Display() const = 0;
	Shape();
	virtual ~Shape();
};
/**********************************************************************/
class Shape2D : virtual public Shape {
public: 
	Shape2D();
	virtual ~Shape2D();
	virtual float Area() const = 0;
	void ShowArea() const;
	virtual string GetName2D() const = 0;
	bool operator>(const Shape2D& rhs) const;
	bool operator<(const Shape2D& rhs) const;
	bool operator==(const Shape2D& rhs) const;
};
/**********************************************************************/
class Shape3D : virtual public Shape {
public: 
	virtual ~Shape3D();
	virtual float Volume() const = 0;
	void ShowVolume() const;
	virtual std::string GetName3D() const = 0;
	bool operator>(const Shape3D& rhs) const;
	bool operator<(const Shape3D& rhs) const;
	bool operator==(const Shape3D& rhs) const;
};
/**********************************************************************/
class Triangle : public Shape2D {
	float base;
	float height;
	string name;
public:
	Triangle();
	Triangle(float b, float h);
	Triangle(const Triangle& t);
	~Triangle();
	void Display() const;
	void Scale(float scaleFactor);
	float Area() const;
	string GetName2D() const;
};
/**********************************************************************/
class Circle : public Shape2D {
	float radius;
	string name;

public:
	Circle();
	Circle(float rad);
	Circle(const Circle& c);
	~Circle();
	float getRadius() const;
	void Display() const;
	void Scale(float scaleFactor);
	float Area() const;
	string GetName2D() const;
};
/**********************************************************************/
class Square : virtual public Shape2D {
	float side;
	string name;
public:
	Square();
	Square(float s);
	Square(const Square& s);
	~Square();
	float Area() const;
	string GetName2D() const;
	void Display() const;
	void Scale(float scaleFactor);
};
/**********************************************************************/
class TriangularPyramid : virtual public Shape3D, virtual private Triangle {
	float height;
	string name;
	
public:
	TriangularPyramid();
	TriangularPyramid(float base, float t_height, float _height);
	~TriangularPyramid();
	float Volume() const;
	string GetName3D() const;
	void Display() const;
	void Scale(float scaleFactor);
};
/**********************************************************************/
class Cylinder : virtual public Shape3D, virtual private Circle {
	float height;
	string name;

public:
	Cylinder();
	Cylinder(float radius, float height);
	~Cylinder();
	float Volume() const;
	string GetName3D() const;
	void Display() const;
	void Scale(float scaleFactor);
};
/**********************************************************************/
class Sphere : public Shape3D, virtual private Circle {
	string name;
public:
	Sphere();
	Sphere(float radius);
	~Sphere();
	float Volume() const;
	string GetName3D() const;
	void Scale(float scaleFactor);
	void Display() const;
};