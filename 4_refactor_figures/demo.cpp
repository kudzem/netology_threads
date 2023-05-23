#include "transform.h"
#include <vector>

int main() {

	std::vector<ThreeDPoint> points;

	points.emplace_back(0, 0, 0);
	points.emplace_back(1, 1, 0);
	Line line(points.begin());

	points.emplace_back(1, 0, 0);
	points.emplace_back(0, 1, 0);
	Square square(points.begin());

	points.emplace_back(0, 0, 1);
	points.emplace_back(1, 1, 1);
	points.emplace_back(1, 0, 1);
	points.emplace_back(0, 1, 1);

	Cube cube(points.begin());

	Cylinder cylinder(points[0], 1, 1);
	Circle circle(points[2], 1);

	transform t2(line);
	t1.scaleZ(2);
	t1.shift(0, 0, -5);

	return 0;
}