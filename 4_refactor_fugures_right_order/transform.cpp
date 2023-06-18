#include "transform.h"

transform::transform(const Shape& sh)
{
	shape = sh;
}

Shape transform::shift(int m, int n, int k)
{
	ThreeDPoint shiftObject(m, n, k);

	for (auto& p : shape.points) {
		p = p + shiftObject;
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