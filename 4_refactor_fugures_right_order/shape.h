#pragma once

#define _USE_MATH_DEFINES

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

	double distance(const ThreeDPoint& other) const {
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

	Shape(int type, ThreeDPoint center, double R);
	int getType() const { return type; }
	virtual std::string getTypeStr() const { return "Shape"; }
	double getRadius() const { return radius; }

	void scale_radius(double a) { radius *= a; }

	virtual
	std::string to_string() {
		std::string res;
		res += "Type=" + std::to_string(getType()) + ":\n";
		res += "volume=" + std::to_string(getVolume()) + ":\n";
		res += "square=" + std::to_string(getSquare()) + ":\n";
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

	Shape& shift(const ThreeDPoint& value) {
		for (auto& point : points) {
			point = point + value;
		}

		return *this;
	}

	virtual Shape& scale(int dimention, double factor) {
		for (auto& point : points) {
			point.scale(dimention, factor);
		}

		scale_radius(factor);

		return *this;
	}

	virtual Shape& scale(double factor) {
		for (auto& point : points) {
			point.scale(factor);
		}

		scale_radius(factor);

		return *this;
	}

	virtual double getVolume() const;
	virtual double getSquare() const;

};

class Cylinder : public Shape {
private:
	double height = 0;
public:
	Cylinder(ThreeDPoint center, int radius, int height) : Shape(Shape::cylinder, center, radius), height(height) {}

	virtual Shape& scale(double factor) override {
		Shape::scale(factor);
		height *= factor;

		return *this;
	}

	virtual Shape& scale(int dimention, double factor) {
		Shape::scale(dimention, factor);
		height *= factor;
		return *this;
	}

	std::string to_string() override {
		std::string res = Shape::to_string();
		res += "height=" + std::to_string(height) + ":\n";
		return res;
	}

	double getHeight() const { return height; }
	void scale_height(double a) { height *= a; }

	std::string getTypeStr() const override { return "Cylinder"; }

	double getVolume() const override;
	double getSquare() const override;
};