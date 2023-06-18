#pragma once
#include "shape.h"
class transform
{
public:
	Shape* shift(Shape* sh, int m, int n, int k);
	Shape* scaleDimention(Shape* sh, int dimention, double a);
	Shape* scaleX(Shape* sh, double k);
	Shape* scaleY(Shape* sh, double k);
	Shape* scaleZ(Shape* sh, double k);
	Shape* scale(Shape* sh, double k);
};