#pragma once
#include<string>
#include<array>
#include<vector>
#include<algorithm>

struct ThreeDPoint {
	std::array<double, 3> _c;
public:
	ThreeDPoint(double x, double y, double z) : _c{ x,y,z } {}
	ThreeDPoint(const ThreeDPoint& other) : _c(other._c) {}
	ThreeDPoint() : _c{ 0,0,0 } {}

	ThreeDPoint& operator+(const ThreeDPoint& other) {
		_c[0] += other._c[0];
		_c[1] += other._c[1];
		_c[2] += other._c[2];
		return *this;
	}

	ThreeDPoint& operator=(const ThreeDPoint& other) {
		_c = other._c;
		return *this;
	}

	ThreeDPoint& operator*(double factor) {
		std::for_each(_c.begin(), _c.end(), [factor](double& value) { value *= factor; });
		return *this;
	}

	ThreeDPoint& scale(int dimention, double factor) {
		_c[dimention] *= factor;
		return *this;
	}

	ThreeDPoint& scale(double factor) {
		_c[0] *= factor;
		_c[1] *= factor;
		_c[2] *= factor;
		return *this;
	}

	double distance(const ThreeDPoint& other) {
		return sqrt(pow(_c[0] - other._c[0], 2) + pow(_c[1] - other._c[1], 2) + pow(_c[2] - other._c[2], 2));
	}

	std::string to_string() {
		std::string res;
		res += "Point: ";
		std::for_each(_c.begin(), _c.end(), [&res](int val) { res += std::to_string(val) + ","; });
		return res;
	}
};

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

	std::vector<ThreeDPoint> points;

	Shape();
	Shape(int type, ThreeDPoint p1, ThreeDPoint p2, ThreeDPoint p3, ThreeDPoint p4);

	Shape(int type, ThreeDPoint center, double R, double H);
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
			double a = points[0].distance(points[1]);
			double b = points[0].distance(points[2]);
			res += "a=" + std::to_string(a) + ",b=" + std::to_string(b) + ":\n";
		}
		if (type == cube) {
			double a = points[0].distance(points[1]);
			double b = points[0].distance(points[2]);
			double c = points[0].distance(points[3]);
			res += "a=" + std::to_string(a) + ",b=" + std::to_string(b) + ",c=" + std::to_string(c) + ":\n";
		}

		for (auto& p : points) {
			res += p.to_string();
		}
		return res;
	}
};