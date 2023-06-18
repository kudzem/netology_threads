#define _USE_MATH_DEFINES
#include"shape.h"
#include<cmath>
#include <iostream>

Shape::Shape() : type(-1), volume(0), square(0), radius(0), height(0) {}

Shape::Shape(int _type, int _x1, int _y1, int _z1, int _x2, int _y2, int _z2,
	                    int _x3, int _y3, int _z3, int _x4, int _y4, int _z4) : Shape()
{
	type = _type;
	// заполн¤ем координаты фигуры
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

	int a = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
	int b = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2) + pow(z1 - z3, 2));
	int c = sqrt(pow(x1 - x4, 2) + pow(y1 - y4, 2) + pow(z1 - z4, 2));

	switch (type)
	{
	case cylinder:
		std::cout << "r=" << radius << std::endl;
		volume = M_PI * radius * radius * height;
		std::cout << "vol=" << volume << std::endl;
		break;
	case cube:
		std::cout << "a=" << a << "b=" << b << "c=" << c << std::endl;
		// стороны фигуры
		volume = a * b * c;
		break;
	default:
		break;
	}
}

void Shape::calculate_square() {
	// стороны фигуры
	int a = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
	int b = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2) + pow(z1 - z3, 2));
	int c = sqrt(pow(x1 - x4, 2) + pow(y1 - y4, 2) + pow(z1 - z4, 2));

	// считаем площадь фигуры
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

Shape::Shape(int _type, int x, int y, int z, double R, double H) : Shape()
{
	type = _type;
	// заполн¤ем координаты фигуры
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