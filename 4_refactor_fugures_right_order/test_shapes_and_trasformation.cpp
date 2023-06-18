#define _USE_MATH_DEFINES

#include "transform.h"
#include <iostream>
#include <vector>
#include <cassert>
#include<cmath>

void check_main_shape_parameters_match(Shape* shape, int type, double volume, double square, double height, double radius) {
	std::cout << shape->to_string() << std::endl;
	assert(shape->getType() == type);
	//std::cout << shape->getVolume() << "/" << volume <<std::endl;
	assert(shape->getVolume() == volume);
	assert(shape->getSquare() == square);
	assert(shape->getHeight() == height);
	assert(shape->getRadius() == radius);
}

int main() {

	Shape* line =   new Shape(0, 1, 1, 1, 2, 2, 2, 0, 0, 0, 0, 0, 0);
	Shape* square = new Shape(1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0);
	Shape* cube =   new Shape(2, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0);

	const double R = 2;
	const double H = 5;
	Shape* circle = new Shape(3, 1, 1, 0, R, 0);
	Shape* cylinder = new Shape(4, 1, 1, 0, R, H);

	std::vector<Shape*> shapes;

	shapes.push_back(line);
	shapes.push_back(square);
	shapes.push_back(cube);
	shapes.push_back(circle);
	shapes.push_back(cylinder);

	check_main_shape_parameters_match(line, 0, 0, 0, 0, 0);
	check_main_shape_parameters_match(square, 1, 0, 1, 0, 0);
	check_main_shape_parameters_match(cube, 2, 1, 6, 0, 0);
	check_main_shape_parameters_match(circle, 3, 0, M_PI*R*R, 0, R);
	check_main_shape_parameters_match(cylinder, 4, M_PI * R * R * H, (2 * M_PI * R * R) + (2 * M_PI * R * H), H, R);

	std::cout << "SHIFT" << std::endl;

	std::vector<transform> transformers;

	for (auto shape : shapes) {
		transformers.emplace_back(*shape);
	}

	std::vector<Shape> trasformed_shapes;
	for (auto& t : transformers) {
		trasformed_shapes.push_back(t.shift(3,3,3));
	}

	//after all figures are shifted - check that parameters are the same
	check_main_shape_parameters_match(&trasformed_shapes[0], 0, 0, 0, 0, 0);
	check_main_shape_parameters_match(&trasformed_shapes[1], 1, 0, 1, 0, 0);
	check_main_shape_parameters_match(&trasformed_shapes[2], 2, 1, 6, 0, 0);
	check_main_shape_parameters_match(&trasformed_shapes[3], 3, 0, M_PI * R * R, 0, R);
	check_main_shape_parameters_match(&trasformed_shapes[4], 4, M_PI * R * R * H, (2 * M_PI * R*R) + (2 * M_PI * R*H), H, R);

	std::cout << "SCALE X" << std::endl;

	double scale_factor = 2;
	trasformed_shapes.clear();
	for (auto& t : transformers) {
		trasformed_shapes.push_back(t.scaleX(scale_factor));
	}

	//after all figures are scaled - check that parameters are changed correctly
	check_main_shape_parameters_match(&trasformed_shapes[0], 0, 0, 0, 0, 0);
	check_main_shape_parameters_match(&trasformed_shapes[1], 1, 0, 2, 0, 0);
	check_main_shape_parameters_match(&trasformed_shapes[2], 2, 2, 10, 0, 0);
	check_main_shape_parameters_match(&trasformed_shapes[3], 3, 0, M_PI * R * R * scale_factor * scale_factor, 0, R*scale_factor);
	check_main_shape_parameters_match(&trasformed_shapes[4], 4,
		                              M_PI * R * R * H * pow(scale_factor,3),
		                              (2 * M_PI * R * R * pow(scale_factor, 2)) + (2 * M_PI * R * H * pow(scale_factor, 2)), H * scale_factor, R * scale_factor);


	std::cout << "SCALE Z" << std::endl;

	scale_factor = 0.5;
	trasformed_shapes.clear();
	for (auto& t : transformers) {
		trasformed_shapes.push_back(t.scaleZ(scale_factor));
	}

	//after all figures are scaled - check that parameters are changed correctly
	check_main_shape_parameters_match(&trasformed_shapes[0], 0, 0, 0, 0, 0);
	check_main_shape_parameters_match(&trasformed_shapes[1], 1, 0, 2, 0, 0);
	check_main_shape_parameters_match(&trasformed_shapes[2], 2, 1, 7, 0, 0);
	check_main_shape_parameters_match(&trasformed_shapes[3], 3, 0, M_PI * R * R, 0, R);
	check_main_shape_parameters_match(&trasformed_shapes[4], 4, M_PI * R * R * H, (2 * M_PI * R * R) + (2 * M_PI * R * H), H, R);


	delete line;
	delete square;
	delete cube;
	delete circle;
	delete cylinder;
}