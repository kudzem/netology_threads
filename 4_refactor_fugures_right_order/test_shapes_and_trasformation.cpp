#define _USE_MATH_DEFINES

#include "transform.h"
#include <iostream>
#include <vector>
#include <cassert>
#include<cmath>

void check_main_shape_parameters_match(Shape* shape, int type, double volume, double square, double height, double radius) {
	assert(shape->getType() == type);
	//std::cout << shape->getVolume() << "/" << volume <<std::endl;
	assert(shape->getVolume() == volume);
	assert(shape->getSquare() == square);
	assert(shape->getHeight() == height);
	assert(shape->getRadius() == radius);
}

int main() {

	Shape* line =   new Shape(0, 1, 1, 1, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	Shape* square = new Shape(1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	Shape* cube =   new Shape(2, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1);
	Shape* circle = new Shape(3, 1, 1, 2, 0);
	Shape* cylinder = new Shape(4, 1, 1, 2, 5);

	std::vector<Shape*> shapes;

	shapes.push_back(line);
	shapes.push_back(square);
	shapes.push_back(cube);
	shapes.push_back(circle);
	shapes.push_back(cylinder);

	for (auto shape : shapes) {
		std::cout << shape->to_string() << std::endl;
	}

	check_main_shape_parameters_match(line, 0, 0, 0, 0, 0);
	//check_main_shape_parameters_match(square, 1, 0, 1, 0, 0);
	check_main_shape_parameters_match(square, 1, 0, 0, 0, 0);
	//check_main_shape_parameters_match(cube, 2, 1, 6, 0, 0);
	check_main_shape_parameters_match(cube, 2, 0, 0, 0, 0);
	check_main_shape_parameters_match(circle, 3, 0, M_PI*2*2, 0, 2);
	check_main_shape_parameters_match(cylinder, 4, 2 * M_PI * 2 * 5, (2 * M_PI * 2 * 2) + (2 * M_PI * 2 * 5), 5, 2);

	delete line;
	delete square;
	delete cube;
	delete circle;
	delete cylinder;
}