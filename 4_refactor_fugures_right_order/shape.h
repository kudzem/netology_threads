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
public:
	enum shape_type {
		unknown = -1,
		line,
		sqr,
		cube,
		circle,
		cylinder
	};

private:
	shape_type type;

public:

	std::vector<ThreeDPoint> points;

	Shape(shape_type _type);
	Shape(shape_type type, ThreeDPoint p1, ThreeDPoint p2);
	Shape(shape_type type, ThreeDPoint p1, ThreeDPoint p2, ThreeDPoint p3);
	Shape(shape_type type, ThreeDPoint p1, ThreeDPoint p2, ThreeDPoint p3, ThreeDPoint p4);
	Shape(shape_type type, ThreeDPoint center);

	shape_type getType() const { return type; }
	virtual std::string getTypeStr() const { return "Shape"; }

	virtual
	std::string to_string() {
		std::string res;
		res += "Type=" + getTypeStr() + "(" + std::to_string(getType()) + ")" + ":\n";

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

		return *this;
	}

	virtual Shape& scale(double factor) {
		for (auto& point : points) {
			point.scale(factor);
		}

		return *this;
	}
};

class HasSurface {
public:
	virtual double getSquare() const = 0;

};

class HasVolume {
public:
	virtual double getVolume() const = 0;
};

class RotationShape : public Shape {
private:
	double radius = 0;
public:
	RotationShape(Shape::shape_type type, ThreeDPoint center, double radius) : Shape(type, center), radius(radius) {}

	virtual Shape& scale(double factor) override {
		Shape::scale(factor);
		scaleRadius(factor);
		return *this;
	}

	virtual Shape& scale(int dimention, double factor) {
		Shape::scale(dimention, factor);
		scaleRadius(factor);
		return *this;
	}

	std::string to_string() override {
		std::string res = Shape::to_string();
		res += "radius=" + std::to_string(radius) + ":\n";
		return res;
	}

	double getRadius() const { return radius; }
	void scaleRadius(double a) { radius *= a; }

	std::string getTypeStr() const override { return "RotationShape"; }
};

class Cylinder : public RotationShape, public HasVolume, public HasSurface {
private:
	double height = 0;
public:
	Cylinder(ThreeDPoint center, double radius, double height) : RotationShape(Shape::cylinder, center, radius), HasVolume(), HasSurface(), height(height) {}

	virtual Shape& scale(double factor) override {
		RotationShape::scale(factor);
		height *= factor;

		return *this;
	}

	virtual Shape& scale(int dimention, double factor) {
		RotationShape::scale(dimention, factor);
		height *= factor;
		return *this;
	}

	std::string to_string() override {
		std::string res = RotationShape::to_string();
		res += "height=" + std::to_string(height) + ":\n";
		res += "square=" + std::to_string(getSquare()) + ":\n";
		res += "volume=" + std::to_string(getVolume()) + ":\n";
		return res;
	}

	double getHeight() const { return height; }
	void scale_height(double a) { height *= a; }

	std::string getTypeStr() const override { return "Cylinder"; }

	double getVolume() const override;
	double getSquare() const override;
};

class Circle : public RotationShape, public HasSurface {
public:
	Circle(ThreeDPoint center, double radius) : RotationShape(Shape::circle, center, radius), HasSurface() {}

	std::string getTypeStr() const override { return "Circle"; }

	double getSquare() const override;

	std::string to_string() override {
		std::string res = RotationShape::to_string();
		res += "square=" + std::to_string(getSquare()) + ":\n";
		return res;
	}
};


class Square : public HasSurface, public Shape {
public:
	Square(ThreeDPoint p1, ThreeDPoint p2, ThreeDPoint p3) : Shape(Shape::sqr, p1, p2, p3), HasSurface() {}

	virtual std::string getTypeStr() const override { return "Square"; }

	virtual double getSquare() const override;

	std::string to_string() override {
		std::string res = Shape::to_string();
		res += "square=" + std::to_string(getSquare()) + ":\n";
		res += "a=" + std::to_string(points[0].distance(points[1])) +
			   ",b=" + std::to_string(points[0].distance(points[2])) + ":\n";
		return res;
	}
};

class Cube : public Shape, public HasVolume, public HasSurface {
public:
	Cube(ThreeDPoint p1, ThreeDPoint p2, ThreeDPoint p3, ThreeDPoint p4) : Shape(Shape::cube, p1, p2, p3, p4), HasVolume(), HasSurface() {}

	virtual std::string getTypeStr() const override { return "Cube"; }

	virtual double getSquare() const override;
	virtual double getVolume() const override;

	std::string to_string() override {
		std::string res = Shape::to_string();
		res += "square=" + std::to_string(getSquare()) + ":\n";
		res += "volume=" + std::to_string(getVolume()) + ":\n";
		res += "a=" + std::to_string(points[0].distance(points[1])) + 
			   ",b=" + std::to_string(points[0].distance(points[2])) +
			   ",c=" + std::to_string(points[0].distance(points[3])) + ":\n";
		return res;
	}

};

class Line : public Shape {
public:
	Line(ThreeDPoint p1, ThreeDPoint p2) : Shape(Shape::line, p1, p2) {}

	virtual std::string getTypeStr() const override { return "Line"; }

	std::string to_string() override {
		std::string res = Shape::to_string();
		res += "a=" + std::to_string(points[0].distance(points[1])) + ":\n";
		return res;
	}

};