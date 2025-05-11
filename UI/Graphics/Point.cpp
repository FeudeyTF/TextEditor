#include "Point.hpp"

Point::operator COORD()
{
	return COORD{ (short)X, (short)Y };
}