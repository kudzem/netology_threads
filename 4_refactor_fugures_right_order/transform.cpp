#include "transform.h"

transform::transform(Shape* sh)
{
	shape = sh;
}

Shape* transform::shift(int m, int n, int k)
{
	ThreeDPoint shiftObject(m, n, k);

	shape->shift(shiftObject);
	return shape;
}

Shape* transform::scaleDimention(int dimention, double a)
{
	shape->scale(dimention, a);

	return shape;
}
Shape* transform::scaleX(double k)
{
	return scaleDimention(0, k);
}

Shape* transform::scaleY(double k)
{
	return scaleDimention(1, k);
}

Shape* transform::scaleZ(double k)
{
	return scaleDimention(2, k);
}

Shape* transform::scale(double k)
{
	scaleX(k);
	scaleY(k);
	scaleZ(k);

	return shape;
}