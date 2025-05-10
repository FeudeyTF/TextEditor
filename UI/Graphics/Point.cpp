#include "Point.h"

Point::operator COORD()
{
	return COORD{ (short)X, (short)Y };
}