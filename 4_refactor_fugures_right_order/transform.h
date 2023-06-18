#pragma once
#include"shape.h"
class transform
{
public:
	transform(const Shape& sh);
	Shape shift(int m, int n, int k);
	Shape scaleX(double k);
	Shape scaleY(double k);
	Shape scaleZ(double k);
	Shape scale(double k);

private:
	Shape shape;
};