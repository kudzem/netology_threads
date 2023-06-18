#define _USE_MATH_DEFINES
#include"shape.h"
#include<cmath>
#include <iostream>

Shape::Shape() : type(-1), volume(0), square(0) {}

Shape::Shape(int _type, ThreeDPoint p1, ThreeDPoint p2, ThreeDPoint p3, ThreeDPoint p4) : Shape()
{
	type = _type;
	// заполн¤ем координаты фигуры
	switch (type)
	{
	case line:
		points.push_back(p1);
		points.push_back(p2);
		break;
	case sqr:
		points.push_back(p1);
		points.push_back(p2);
		points.push_back(p3);
		break;
	case cube:
		points.push_back(p1);
		points.push_back(p2);
		points.push_back(p3);
		points.push_back(p4);
		break;
	default:
		break;
	}
}

Shape::Shape(int _type, ThreeDPoint center) : Shape()
{
	type = _type;

	switch (type)
	{
	case circle:
	case cylinder:
		points.push_back(center);
		break;
	default:
		break;
	}
}

 double Shape::getVolume() const {
	double a, b, c;
	switch (type)
	{
	case line:
	case sqr:
	case circle:
		return 0;
	case cylinder:
		return 0;
	case cube:
		a = points[0].distance(points[1]);
		b = points[0].distance(points[2]);
		c = points[0].distance(points[3]);
		//std::cout << "a=" << a << "b=" << b << "c=" << c << std::endl;
		return a * b * c;
	default:
		break;
	};
}


double Shape::getSquare() const {

	double a, b, c;
	switch (type)
	{
	case line:
		return 0;
	case circle:
	case cylinder:
		return 0;
	case sqr:
		// стороны фигуры
		a = points[0].distance(points[1]);
		b = points[0].distance(points[2]);
		std::cout << "a=" << a << "b=" << b << std::endl;
		return a * b;
	case cube:
		return 0;
	default:
		break;
	}
}

double Cylinder::getVolume() const {
	return M_PI * getRadius() * getRadius() * height;
}

double Cylinder::getSquare() const {
	return (2 * M_PI * getRadius() * getRadius()) + (2 * M_PI * getRadius() * height);
}

double Circle::getVolume() const {
	return 0;
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