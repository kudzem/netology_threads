#pragma once
#include<string>
#include <iostream>


class Shape
{
private:
	int type;
	double volume;
	double square;
	double height;
	double radius;

public:
	static const int line = 0;
	static const int sqr = 1;
	static const int cube = 2;
	static const int circle = 3;
	static const int cylinder = 4;

	double x1 = 0, y1 = 0, z1 = 0,
		x2 = 0, y2 = 0, z2 = 0,
		x3 = 0, y3 = 0, z3 = 0,
		x4 = 0, y4 = 0, z4 = 0;

	Shape();
	Shape(int type, double _x1, double _y1, double _z1, double _x2, double _y2, double _z2, double _x3, double _y3, double _z3, double _x4, double _y4, double _z4);
	Shape(int type, double x, double y, double z, double R, double H);
	int getType() const { return type; }
	double getVolume() const { return volume; }
	double getSquare() const { return square; }
	double getHeight() const { return height; }
	double getRadius() const { return radius; }

	void calculate_volume();
	void calculate_square();

	void scale_radius(double a) { radius *= a; }
	void scale_height(double a) { height *= a; }

	std::string to_string() {
		std::string res;
		res += "Type=" + std::to_string(getType()) + ":\n";
		res += "volume=" + std::to_string(volume) + ":\n";
		res += "square=" + std::to_string(square) + ":\n";
		res += "height=" + std::to_string(height) + ":\n";
		res += "radius=" + std::to_string(radius) + ":\n";
		if (type == sqr) {
			double a = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
			double b = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2) + pow(z1 - z3, 2));
			res += "a=" + std::to_string(a) + ",b=" + std::to_string(b) + ":\n";
		}
		if (type == cube) {
			double a = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
			double b = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2) + pow(z1 - z3, 2));

			std::cout << "SQRT=" << sqrt(pow(z1 - z3, 2)) << std::endl;

			double c = sqrt(pow(x1 - x4, 2) + pow(y1 - y4, 2) + pow(z1 - z4, 2));
			res += "a=" + std::to_string(a) + ",b=" + std::to_string(b) + ",c=" + std::to_string(c) + ":\n";
		}
		res += std::to_string(x1) + "," + std::to_string(y1) + "," + std::to_string(z1) + "\n";
		res += std::to_string(x2) + "," + std::to_string(y2) + "," + std::to_string(z2) + "\n";
		res += std::to_string(x3) + "," + std::to_string(y3) + "," + std::to_string(z3) + "\n";
		res += std::to_string(x4) + "," + std::to_string(y4) + "," + std::to_string(z4) + "\n";
		return res;
	}
};