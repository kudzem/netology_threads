#pragma once
#include<string>
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

	int x1 = 0, y1 = 0, z1 = 0,
		x2 = 0, y2 = 0, z2 = 0,
		x3 = 0, y3 = 0, z3 = 0,
		x4 = 0, y4 = 0, z4 = 0;

	Shape();
	Shape(int type, int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int _x3, int _y3, int _z3, int _x4, int _y4, int _z4);
	Shape(int type, int x, int y, int z, double R, double H);
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
		res += std::to_string(x1) + "," + std::to_string(y1) + "," + std::to_string(z1) + "\n";
		res += std::to_string(x2) + "," + std::to_string(y2) + "," + std::to_string(z2) + "\n";
		res += std::to_string(x3) + "," + std::to_string(y3) + "," + std::to_string(z3) + "\n";
		res += std::to_string(x4) + "," + std::to_string(y4) + "," + std::to_string(z4) + "\n";
		return res;
	}
};