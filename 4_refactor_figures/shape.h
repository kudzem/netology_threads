#pragma once
#include<string>
#include<array>

struct ThreeDPoint {
	int _x, _y, _z;
public:
	ThreeDPoint(int x, int y, int z) : _x(x), _y(y), _z(z) {}
	ThreeDPoint(const ThreeDPoint& other) : _x(other._x), _y(other._y), _z(other._z) {}
	ThreeDPoint() : _x(0), _y(0), _z(0) {}
};

template <int N>
class Shape
{
	std::array<ThreeDPoint, N> points;
public:
	template <typename BeginPointIt>
	Shape(BeginPointIt start) {
		for (auto& point : points) {
			point = *start++;
		}
	}
};

class Flat {
private:
	double square = 0;
public:
	Flat() {}
};

class Volume {
	double volume = 0;
public:
	Volume() {}
};

class Line : public Flat, public Shape<2> {
public:
	template <typename BeginPointIt>
	Line(BeginPointIt start) : Shape(start) {}
};

class Square : Flat, public Shape<4> {
public:
	template <typename BeginPointIt>
	Square(BeginPointIt start) : Shape(start) {}
};

class RotationShape : public Shape<1> {
private:
	double radius = 0;
public:
	RotationShape(const ThreeDPoint& center, int radius) : Shape(center), radius(radius) {}
};

class Circle : public Flat, public RotationShape {
public:
	Circle(const ThreeDPoint& center, int radius) : RotationShape(center, radius), Flat() {}
};

class Cube : public Volume, public Shape<8> {
public:
	template <typename BeginPointIt>
	Cube(BeginPointIt start) : Shape(start) {}
};

class Cylinder : public RotationShape, public Volume {
private:
	double height = 0;
public:
	Cylinder(const ThreeDPoint& center, int radius, int height) : RotationShape(center, radius), Volume(), height(height) {}
};
