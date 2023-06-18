#pragma once
#include<string>
class Shape
{
public:
	static const int line = 0;
	static const int sqr = 1;
	static const int cube = 2;
	static const int circle = 3;
	static const int cylinder = 4;
	Shape();
	Shape(int type, int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int _x3, int _y3, int _z3, int _x4, int _y4, int _z4, int _x5, int _y5, int _z5, int _x6, int _y6, int _z6, int _x7, int _y7, int _z7, int _x8, int _y8, int _z8);
	Shape(int type, int x, int y, int z, double R, double H);
	int getType() const { return type; }
	double getVolume() const { return volume; }
	double getSquare() const { return square; }
	double getHeight() const { return height; }
	double getRadius() const { return radius; }

	int type;
	int x1 = 0, y1 = 0, z1 = 0,
		x2 = 0, y2 = 0, z2 = 0,
		x3 = 0, y3 = 0, z3 = 0,
		x4 = 0, y4 = 0, z4 = 0,
		x5 = 0, y5 = 0, z5 = 0,
		x6 = 0, y6 = 0, z6 = 0,
		x7 = 0, y7 = 0, z7 = 0,
		x8 = 0, y8 = 0, z8 = 0;
	double volume;
	double square;
	double height;
	double radius;

	std::string to_string() {
		std::string res;
		res += "Type=" + std::to_string(getType()) + ":\n";
		res += "volume=" + std::to_string(volume) + ":\n";
		res += "square=" + std::to_string(square) + ":\n";
		res += "height=" + std::to_string(height) + ":\n";
		res += "radius=" + std::to_string(radius) + ":\n";
		res += std::to_string(x1) + "," + std::to_string(y1) + "," + std::to_string(z1) + "\n";
		res += std::to_string(x2) + "," + std::to_string(y2) + "," + std::to_string(z2) + "\n";
		res += std::to_string(x3) + "," + std::to_string(y3) + "," + std::to_string(z3) + "\n";
		res += std::to_string(x4) + "," + std::to_string(y4) + "," + std::to_string(z4) + "\n";
		res += std::to_string(x5) + "," + std::to_string(y5) + "," + std::to_string(z5) + "\n";
		res += std::to_string(x6) + "," + std::to_string(y6) + "," + std::to_string(z6) + "\n";
		res += std::to_string(x7) + "," + std::to_string(y7) + "," + std::to_string(z7) + "\n";
		res += std::to_string(x8) + "," + std::to_string(y8) + "," + std::to_string(z8) + "\n";

		return res;
	}
};