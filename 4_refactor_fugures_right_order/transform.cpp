#include "transform.h"

Shape* transform::shift(Shape* shape, int m, int n, int k)
{
	ThreeDPoint shiftObject(m, n, k);

	shape->shift(shiftObject);
	return shape;
}

Shape* transform::scaleDimention(Shape* shape, int dimention, double a)
{
	shape->scale(dimention, a);

	return shape;
}
Shape* transform::scaleX(Shape* shape, double k)
{
	return scaleDimention(shape, 0, k);
}

Shape* transform::scaleY(Shape* shape, double k)
{
	return scaleDimention(shape, 1, k);
}

Shape* transform::scaleZ(Shape* shape, double k)
{
	return scaleDimention(shape, 2, k);
}

Shape* transform::scale(Shape* shape, double k)
{
	scaleX(shape, k);
	scaleY(shape, k);
	scaleZ(shape, k);

	return shape;
}