#include "transform.h"

transform::transform(const Shape& sh)
{
	shape = sh;
}

Shape transform::shift(int m, int n, int k)
{
	ThreeDPoint shiftObject(m, n, k);
	switch (shape.getType())
	{
	case Shape::line:
		shape.points[0] = shape.points[0] + shiftObject;
		shape.points[1] = shape.points[1] + shiftObject;
		break;
	case Shape::circle:
	case Shape::cylinder:
		shape.points[0] = shape.points[0] + shiftObject;
		break;
	case Shape::sqr:
		shape.points[0] = shape.points[0] + shiftObject;
		shape.points[1] = shape.points[1] + shiftObject;
		shape.points[2] = shape.points[2] + shiftObject;
		break;
	case Shape::cube:
		shape.points[0] = shape.points[0] + shiftObject;
		shape.points[1] = shape.points[1] + shiftObject;
		shape.points[2] = shape.points[2] + shiftObject;
		shape.points[3] = shape.points[3] + shiftObject;
		break;
	}
	return shape;
}

Shape transform::scaleDimention(int dimention, double a)
{
	switch (shape.getType())
	{
	case Shape::line:
	case Shape::sqr:
	case Shape::cube:
		for (auto& p : shape.points) {
			p.scale(dimention, a);
		}
		break;
	case Shape::circle:
		for (auto& p : shape.points) {
			p.scale(dimention, a);
		}
		shape.scale_radius(a);
		break;
	case Shape::cylinder:
		for (auto& p : shape.points) {
			p.scale(dimention, a);
		}
		shape.scale_radius(a);
		shape.scale_height(a);
		break;
	}


	shape.calculate_square();
	shape.calculate_volume();

	return shape;
}
Shape transform::scaleX(double k)
{
	return scaleDimention(0, k);
}

Shape transform::scaleY(double k)
{
	return scaleDimention(1, k);
}

Shape transform::scaleZ(double k)
{
	return scaleDimention(2, k);
}

Shape transform::scale(double k)
{
	scaleX(k);
	scaleY(k);
	scaleZ(k);

	return shape;
}