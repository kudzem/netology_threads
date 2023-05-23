#include "transform.h"

int main() {

	Shape free_figure;
	Shape line(Shape::line, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	Shape square(Shape::sqr, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	Shape cube(Shape::cube, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0);
	Shape cylinder(Shape::cylinder, 0, 0, 1, 1);
	Shape circle(Shape::circle, 0, 0, 1, 1);

	transform t1(free_figure);
	t1.scale(2);

	transform t2(line);
	t1.scaleZ(2);

	t1.shift(0, 0, -5);

	return 0;
}