#define _USE_MATH_DEFINES
#include"shape.h"
#include<cmath>
#include <iostream>

Shape::Shape() : type(-1), volume(0), square(0), radius(0), height(0) {}

Shape::Shape(int _type, double _x1, double _y1, double _z1, double _x2, double _y2, double _z2,
	                    double _x3, double _y3, double _z3, double _x4, double _y4, double _z4) : Shape()
{
	type = _type;
	// ��������� ���������� ������
	switch (type)
	{
	case line:
		x1 = _x1; y1 = _y1; z1 = _z1;
		x2 = _x2; y2 = _y2; z2 = _z2;
		break;
	case sqr:
		x1 = _x1; y1 = _y1; z1 = _z1;
		x2 = _x2; y2 = _y2; z2 = _z2;
		x3 = _x3; y3 = _y3; z3 = _z3;
		x4 = _x4; y4 = _y4; z4 = _z4;
		break;
	case cube:
		x1 = _x1; y1 = _y1; z1 = _z1;
		x2 = _x2; y2 = _y2; z2 = _z2;
		x3 = _x3; y3 = _y3; z3 = _z3;
		x4 = _x4; y4 = _y4; z4 = _z4;
		break;
	default:
		break;
	}

	calculate_square();
	calculate_volume();
}

void Shape::calculate_volume() {

	double a = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
	double b = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2) + pow(z1 - z3, 2));

	std::cout << "SQRT=" << pow(y1 - y3, 2) << std::endl;
	double c = sqrt(pow(x1 - x4, 2) + pow(y1 - y4, 2) + pow(z1 - z4, 2));

	switch (type)
	{
	case cylinder:
		std::cout << "r=" << radius << std::endl;
		volume = M_PI * radius * radius * height;
		std::cout << "vol=" << volume << std::endl;
		break;
	case cube:
		std::cout << "a=" << a << "b=" << b << "c=" << c << std::endl;
		// ������� ������
		volume = a * b * c;
		break;
	default:
		break;
	}
}

void Shape::calculate_square() {
	// ������� ������
	double a = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
	double b = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2) + pow(z1 - z3, 2));
	double c = sqrt(pow(x1 - x4, 2) + pow(y1 - y4, 2) + pow(z1 - z4, 2));

	// ������� ������� ������
	switch (type)
	{
	case circle:
		std::cout << "r=" << radius << std::endl;
		square = M_PI * radius * radius;
		std::cout << ",sq=" << square << std::endl;
		break;
	case cylinder:
		std::cout << "r=" << radius << ",h=" << height << std::endl;
		square = (2 * M_PI * radius * radius) + (2 * M_PI * radius * height);
		std::cout << ",sq=" << square << std::endl;
		break;
	case sqr:
		std::cout << "a=" << a << "b=" << b << "c=" << c << std::endl;
		square = a * b;
		break;
	case cube:
		std::cout << "a=" << a << "b=" << b << "c=" << c << std::endl;
		square = 2 * (a * b + a * c + b * c);
		break;
	default:
		break;
	}
}

Shape::Shape(int _type, double x, double y, double z, double R, double H) : Shape()
{
	type = _type;
	// ��������� ���������� ������
	switch (type)
	{
	case circle:
		x1 = x; y1 = y; z1 = z;
		radius = R;
		break;
	case cylinder:
		x1 = x; y1 = y; z1 = z;
		radius = R;
		height = H;
		break;
	default:
		break;
	}

	calculate_square();
    calculate_volume();
}