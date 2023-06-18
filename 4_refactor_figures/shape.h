#pragma once
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <iostream>

struct ThreeDPoint {
	std::array<int, 3> _c;
public:
	ThreeDPoint(int x, int y, int z) : _c{ x,y,z } {}
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

	ThreeDPoint& operator*(int factor) {
		std::for_each(_c.begin(), _c.end(), [factor](int& value) { value *= factor; });
		return *this;
	}

	ThreeDPoint& scale(int dimention, int factor) {
		_c[dimention] *= factor;
		return *this;
	}

	ThreeDPoint& scale(int factor) {
		_c[0] *= factor;
		_c[1] *= factor;
		_c[2] *= factor;
		return *this;
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
	std::vector<ThreeDPoint> points;
public:
	template <typename BeginPointIt>
	Shape(BeginPointIt* start, unsigned number_of_points) {
		while(number_of_points--) {
			points.push_back(*start++);
		}
	}

	Shape& shift(const ThreeDPoint& value) {
		for (auto& point : points) {
			point = point + value;
		}

		return *this;
	}

	virtual Shape& scale(int dimention, int factor) {
		std::cout << "Scale dimention points" << std::endl;
		for (auto& point : points) {
			point.scale(dimention, factor);
		}

		return *this;
	}

	virtual Shape& scale(int factor) {
		for (auto& point : points) {
			point.scale(factor);
		}

		std::cout << "Scale points" << std::endl;

		return *this;
	}

	virtual std::string to_string() {
		std::string res;
		res += get_type() + ":\n";
		std::for_each(points.begin(), points.end(), [&res](auto val) { res += val.to_string() + "\n"; });
		return res;
	}

	virtual std::string get_type() const { return "Arbitrary"; }
};

class HasSurface {
protected:
	double square = 0;
public:
	HasSurface() {}

	virtual double get_square() = 0;
};

class HasVolume {
protected:
	double volume = 0;
public:
	HasVolume() {}

	virtual double get_volume() = 0;
};

class Line : public Shape {
public:
	template <typename BeginPointIt>
	Line(BeginPointIt start) : Shape(start, 2) {}

	virtual std::string get_type() const override { return "Line"; }
};

class Square : HasSurface, public Shape {
public:
	template <typename BeginPointIt>
	Square(BeginPointIt* start) : Shape(start, 4) {}

	virtual std::string get_type() const override { return "Square"; }

	virtual double get_square() override { return square; }
};

class RotationShape : public Shape {
private:
	double radius = 0;
public:
	RotationShape(const ThreeDPoint* center, int radius) : Shape(center, 1), radius(radius) {}

	virtual Shape& scale(int factor) override {
		Shape::scale(factor);
		radius *= factor;

		return *this;
	}

	virtual Shape& scale(int dimention, int factor) {
		Shape::scale(dimention, factor);
		return *this;
	}

	virtual std::string to_string() override {
		std::string res = Shape::to_string();
		res += "Radius: " + std::to_string(radius) + "\n";
		return res;
	}

};

class Circle : public HasSurface, public RotationShape {
public:
	Circle(const ThreeDPoint* center, int radius) : RotationShape(center, radius), HasSurface() {}

	virtual double get_square() override { return square; }

	virtual std::string get_type() const override { return "Circle"; }
};

class Cube : public HasVolume, public HasSurface, public Shape {
public:
	Cube(const ThreeDPoint* points) : Shape(points, 8) {}

	virtual std::string get_type() const override { return "Cube"; }

	virtual double get_square() override { return square; }

	virtual double get_volume() override { return volume; }
};

class Cylinder : public RotationShape, public HasVolume, public HasSurface {
private:
	double height = 0;
public:
	Cylinder(const ThreeDPoint* center, int radius, int height) : RotationShape(center, radius), HasVolume(), height(height) {}

	virtual Shape& scale(int factor) override {
		RotationShape::scale(factor);
		height *= factor;

		return *this;
	}

	virtual Shape& scale(int dimention, int factor) {
		RotationShape::scale(dimention, factor);
		return *this;
	}

	virtual std::string to_string() override {
		std::string res = RotationShape::to_string();
		res += "Height: " + std::to_string(height) + "\n";
		return res;
	}

	virtual double get_square() override { return square; }
	virtual double get_volume() override { return volume; }

	virtual std::string get_type() const override { return "Cylinder"; }
};
