#pragma once
#include"shape.h"
class transform
{
public:
	transform(Shape* sh);
	Shape* shift(int m, int n, int k);
	Shape* scaleDimention(int dimention, double a);
	Shape* scaleX(double k);
	Shape* scaleY(double k);
	Shape* scaleZ(double k);
	Shape* scale(double k);

private:
	Shape* shape;
};