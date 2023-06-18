#include "transform.h"

transform::transform(const Shape& sh)
{
	shape = sh;
}

Shape transform::shift(int m, int n, int k)
{
	switch (shape.getType())
	{
	case Shape::line:
		shape.x1 += m; shape.y1 += n;
		shape.x2 += m; shape.y2 += n;
		break;
	case Shape::circle:
	case Shape::cylinder:
		shape.x1 += m; shape.y1 += n; shape.z1 += k;
		break;
	case Shape::sqr:
		shape.x1 += m; shape.y1 += n;
		shape.x2 += m; shape.y2 += n;
		shape.x3 += m; shape.y3 += n;
		shape.x4 += m; shape.y4 += n;
		break;
	case Shape::cube:
		shape.x1 += m; shape.y1 += n; shape.z1 += k;
		shape.x2 += m; shape.y2 += n; shape.z2 += k;
		shape.x3 += m; shape.y3 += n; shape.z3 += k;
		shape.x4 += m; shape.y4 += n; shape.z4 += k;
		break;
	}
	return shape;
}

Shape transform::scaleX(double a)
{
	switch (shape.getType())
	{
	case Shape::line:
		shape.x1 *= a;
		shape.x2 *= a;
		break;
	case Shape::sqr:
		shape.x1 *= a;
		shape.x2 *= a;
		shape.x3 *= a;
		shape.x4 *= a;
		break;
	case Shape::cube:
		shape.x1 *= a;
		shape.x2 *= a;
		shape.x3 *= a;
		shape.x4 *= a;
		break;
	case Shape::circle:
		shape.x1 *= a;
		shape.scale_radius(a);
		break;
	case Shape::cylinder:
		shape.x1 *= a;
		shape.scale_radius(a);
		shape.scale_height(a);
		break;
	}


	shape.calculate_square();
	shape.calculate_volume();

	return shape;
}

Shape transform::scaleY(double d)
{
	switch (shape.getType())
	{
	case Shape::line:
		shape.y1 *= d;
		shape.y2 *= d;
		break;
	case Shape::sqr:
		shape.y1 *= d;
		shape.y2 *= d;
		shape.y3 *= d;
		shape.y4 *= d;
		break;
	case Shape::cube:
		shape.y1 *= d;
		shape.y2 *= d;
		shape.y3 *= d;
		shape.y4 *= d;
		break;
	case Shape::circle:
		shape.y1 *= d;
		shape.scale_radius(d);
		break;
	case Shape::cylinder:
		shape.y1 *= d;
		shape.scale_radius(d);
		shape.scale_height(d);
	}

	shape.calculate_square();
	shape.calculate_volume();
	return shape;
}

Shape transform::scaleZ(double e)
{
	switch (shape.getType())
	{
	case Shape::line:
		shape.z1 *= e;
		shape.z2 *= e;
		break;
	case Shape::sqr:
		shape.z1 *= e;
		shape.z2 *= e;
		shape.z3 *= e;
		shape.z4 *= e;
		break;
	case Shape::cube:
		shape.z1 *= e;
		shape.z2 *= e;
		shape.z3 *= e;
		shape.z4 *= e;
		break;
	case Shape::circle:
		shape.z1 *= e;
		shape.z2 *= e;
		shape.z3 *= e;
		shape.z4 *= e;
		shape.scale_radius(e);
		break;
	case Shape::cylinder:
		shape.z1 *= e;
		shape.z2 *= e;
		shape.z3 *= e;
		shape.z4 *= e;
		shape.scale_radius(e);
		shape.scale_height(e);
	}

	shape.calculate_square();
	shape.calculate_volume();
	return shape;
}

Shape transform::scale(double s)
{
	scaleX(s);
	scaleY(s);
	scaleZ(s);

	return shape;
}