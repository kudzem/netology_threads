#include "transform.h"
#include <vector>
#include <iostream>
#include <memory>

int main() {

	std::vector<ThreeDPoint> points;

	std::vector<std::unique_ptr<Shape>> shapes;

	points.emplace_back(0, 0, 0);
	points.emplace_back(1, 1, 0);
	points.emplace_back(1, 0, 0);
	points.emplace_back(0, 1, 0);
	points.emplace_back(0, 0, 1);
	points.emplace_back(1, 1, 1);
	points.emplace_back(1, 0, 1);
	points.emplace_back(0, 1, 1);

	Shape shape(&points[0], 4);

	std::unique_ptr<Line> line = std::make_unique<Line>(&points[0]);
	shapes.push_back(std::move(line));
	std::unique_ptr<Square> square = std::make_unique<Square>(&points[0]);
	shapes.push_back(std::move(square));
	std::unique_ptr<Cube> cube = std::make_unique<Cube>(&points[0]);
	shapes.push_back(std::move(cube));

	std::unique_ptr<Cylinder> cylinder = std::make_unique<Cylinder>(&points[0],1,1);
	shapes.push_back(std::move(cylinder));
	std::unique_ptr<Circle> circle = std::make_unique<Circle>(&points[0],1);
	shapes.push_back(std::move(circle));


	ThreeDPoint jump_up(1,1,1);

	for (auto& shape : shapes) {
		shape->shift(jump_up);
		shape->scale(2);
		shape->scale(0, -1);
	}

	for (auto& shape : shapes) {
		std::cout << shape->to_string() << std::endl;
	}

	return 0;
}