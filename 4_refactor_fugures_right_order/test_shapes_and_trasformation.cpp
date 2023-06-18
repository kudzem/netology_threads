#define _USE_MATH_DEFINES

#include "transform.h"
#include <iostream>
#include <vector>
#include <cassert>
#include<cmath>

void check_main_shape_parameters_match(Shape* shape, int type) {
	std::cout << shape->to_string() << std::endl;
	assert(shape->getType() == type);
}

void check_main_square_parameters_match(Square* shape, int type, double square) {
	check_main_shape_parameters_match(shape, type);
	assert(shape->getSquare() == square);
}

void check_main_cube_parameters_match(Cube* shape, int type, double volume, double square) {
	check_main_shape_parameters_match(shape, type);
	assert(shape->getVolume() == volume);
	assert(shape->getSquare() == square);
}

void check_main_circle_parameters_match(Circle* shape, int type, double volume, double square, double radius) {
	check_main_shape_parameters_match(shape, type);
	assert(shape->getRadius() == radius);
	assert(shape->getSquare() == square);
}

void check_main_cylinder_parameters_match(Cylinder* shape, int type, double volume, double square, double height, double radius) {
	check_main_shape_parameters_match(shape, type);
	assert(shape->getHeight() == height);
	assert(shape->getRadius() == radius);
	assert(shape->getVolume() == volume);
	assert(shape->getSquare() == square);
}

int main() {

	Shape* line = new Line({ 1, 1, 1 }, { 2, 2, 2 });
	Shape* square = new Square({ 1, 1, 0 }, { 1, 0, 0 }, { 0, 1, 0 });
	Shape* cube = new Cube( { 0, 0, 0 }, { 1, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 });

	const double R = 2;
	const double H = 5;
	Shape* circle = new Circle({ 1, 1, 0 }, R);
	Shape* cylinder = new Cylinder({ 1, 1, 0 }, R, H);

	std::vector<Shape*> shapes;

	shapes.push_back(line);
	shapes.push_back(square);
	shapes.push_back(cube);
	shapes.push_back(circle);
	shapes.push_back(cylinder);

	check_main_shape_parameters_match(line, 0);
	check_main_square_parameters_match(static_cast<Square*>(square), 1, 1);
	check_main_cube_parameters_match(static_cast<Cube*>(cube), 2, 1, 6);
	check_main_circle_parameters_match(static_cast<Circle*>(circle), 3, 0, M_PI*R*R, R);
	check_main_cylinder_parameters_match(static_cast<Cylinder*>(cylinder), 4, M_PI * R * R * H, (2 * M_PI * R * R) + (2 * M_PI * R * H), H, R);

	std::cout << "SHIFT" << std::endl;

	transform transformer;

	for (auto shape : shapes) {
		transformer.shift(shape, 3, 3, 3);
	}

	//after all figures are shifted - check that parameters are the same
	check_main_shape_parameters_match(line, 0);
	check_main_square_parameters_match(static_cast<Square*>(square), 1, 1);
	check_main_cube_parameters_match(static_cast<Cube*>(cube), 2, 1, 6);
	check_main_circle_parameters_match(static_cast<Circle*>(circle), 3, 0, M_PI * R * R, R);
	check_main_cylinder_parameters_match(static_cast<Cylinder*>(cylinder), 4, M_PI * R * R * H, (2 * M_PI * R*R) + (2 * M_PI * R*H), H, R);

	std::cout << "SCALE X" << std::endl;

	double scale_factor = 2;
	for (auto shape : shapes) {
		transformer.scaleX(shape, scale_factor);
	}

	//after all figures are scaled - check that parameters are changed correctly
	check_main_shape_parameters_match(line, 0);
	check_main_square_parameters_match(static_cast<Square*>(square), 1, 2);
	check_main_cube_parameters_match(static_cast<Cube*>(cube), 2, 2, 10);

	check_main_circle_parameters_match(static_cast<Circle*>(circle), 3, 0, M_PI * R * R * scale_factor * scale_factor, R*scale_factor);
	check_main_cylinder_parameters_match(static_cast<Cylinder*>(cylinder), 4,
		                              M_PI * R * R * H * pow(scale_factor,3),
		                              (2 * M_PI * R * R * pow(scale_factor, 2)) + (2 * M_PI * R * H * pow(scale_factor, 2)), H * scale_factor, R * scale_factor);


	std::cout << "SCALE Z" << std::endl;

	scale_factor = 0.5;
	for (auto shape : shapes) {
		transformer.scaleZ(shape, scale_factor);
	}

	//after all figures are scaled - check that parameters are changed correctly
	check_main_shape_parameters_match(line, 0);
	check_main_square_parameters_match(static_cast<Square*>(square), 1, 2);
	check_main_cube_parameters_match(static_cast<Cube*>(cube), 2, 1, 7);

	check_main_circle_parameters_match(static_cast<Circle*>(circle), 3, 0, M_PI * R * R, R);
	check_main_cylinder_parameters_match(static_cast<Cylinder*>(cylinder), 4, M_PI * R * R * H, (2 * M_PI * R * R) + (2 * M_PI * R * H), H, R);

	std::cout << "SCALE Y" << std::endl;


	scale_factor = 2;
	for (auto shape : shapes) {
		transformer.scaleY(shape, scale_factor);
	}

	//after all figures are scaled - check that parameters are changed correctly
	check_main_shape_parameters_match(line, 0);
	check_main_square_parameters_match(static_cast<Square*>(square), 1, 4);
	check_main_cube_parameters_match(static_cast<Cube*>(cube), 2, 2, 12);

	check_main_circle_parameters_match(static_cast<Circle*>(circle), 3, 0, M_PI * R * R * pow(scale_factor, 2), R * scale_factor);
	check_main_cylinder_parameters_match(static_cast<Cylinder*>(cylinder), 4,
		M_PI * R * R * H * pow(scale_factor, 3),
		(2 * M_PI * R * R * pow(scale_factor, 2)) + (2 * M_PI * R * H * pow(scale_factor, 2)), H * scale_factor, R * scale_factor);

	delete line;
	//delete square;
	delete cube;
	delete circle;
	delete cylinder;
}