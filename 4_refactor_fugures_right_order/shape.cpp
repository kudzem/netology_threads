#define _USE_MATH_DEFINES
#include"shape.h"
#include<cmath>
#include <iostream>

Shape::Shape(shape_type type,
	         ThreeDPoint anchor_point) : _type(type),
	                                     _anchor_point(anchor_point) { }

Shape::Shape(shape_type type, 
	         ThreeDPoint anchor_point, 
	         std::vector<ThreeDPoint>& addPoints) : _type(type), 
	                                                _anchor_point(anchor_point), 
	                                                _addPoints(addPoints) { }

Shape::Shape(shape_type type,
	         ThreeDPoint anchor_point,
	         std::vector<ThreeDPoint>&& addPoints) : _type(type),
	                                                 _anchor_point(anchor_point),
	                                                 _addPoints(addPoints) { }

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
	a = _anchor_point.distance(_addPoints[0]);
	b = _anchor_point.distance(_addPoints[1]);
	c = _anchor_point.distance(_addPoints[2]);
	//std::cout << "a=" << a << "b=" << b << "c=" << c << std::endl;
	return a * b * c;
}

double Cube::getSquare() const {
	double a, b, c;
	a = _anchor_point.distance(_addPoints[0]);
	b = _anchor_point.distance(_addPoints[1]);
	c = _anchor_point.distance(_addPoints[2]);
	return  2 * (a * b + a * c + b * c);
}

double Square::getSquare() const {
	double a, b;
	a = _anchor_point.distance(_addPoints[0]);
	b = _anchor_point.distance(_addPoints[1]);
	return a * b;
}