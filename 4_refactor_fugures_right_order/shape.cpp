#define _USE_MATH_DEFINES
#include"shape.h"
#include<cmath>
#include <iostream>

Shape::Shape() : type(unknown) {}

Shape::Shape(shape_type _type, ThreeDPoint p1, ThreeDPoint p2) : Shape()
{
	type = _type;

	points.push_back(p1);
	points.push_back(p2);
}

Shape::Shape(shape_type _type, ThreeDPoint p1, ThreeDPoint p2, ThreeDPoint p3) : Shape()
{
	type = _type;

	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
}

Shape::Shape(shape_type _type, ThreeDPoint p1, ThreeDPoint p2, ThreeDPoint p3, ThreeDPoint p4) : Shape()
{
	type = _type;

	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
}

Shape::Shape(shape_type _type, ThreeDPoint center) : Shape()
{
	type = _type;
	points.push_back(center);
}

double Cylinder::getVolume() const {
	return M_PI * getRadius() * getRadius() * height;
}

double Cylinder::getSquare() const {
	return (2 * M_PI * getRadius() * getRadius()) + (2 * M_PI * getRadius() * height);
}

double Circle::getSquare() const {
	return M_PI * getRadius() * getRadius();
}

double Cube::getVolume() const {
	double a, b, c;
	a = points[0].distance(points[1]);
	b = points[0].distance(points[2]);
	c = points[0].distance(points[3]);
	//std::cout << "a=" << a << "b=" << b << "c=" << c << std::endl;
	return a * b * c;
}

double Cube::getSquare() const {
	double a, b, c;
	a = points[0].distance(points[1]);
	b = points[0].distance(points[2]);
	c = points[0].distance(points[3]);
	return  2 * (a * b + a * c + b * c);
}

double Square::getSquare() const {
	double a, b, c;
	// стороны фигуры
	a = points[0].distance(points[1]);
	b = points[0].distance(points[2]);
	return a * b;
}