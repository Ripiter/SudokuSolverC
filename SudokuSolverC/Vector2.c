#include "Vector2.h"


int compare_vector2(Vector2_t vec, Vector2_t vec2)
{
	if (vec.x == vec2.x && vec.y == vec2.y)
		return 1;

	return 0;
}

int compare_vector(Vector2_t vec, int _x, int _y)
{
	if (vec.x == _x && vec.y == _y)
		return 1;

	return 0;
}

int compare_position(int _x1, int _y1, int _x2, int _y2)
{
	if (_x1 == _x2 && _y1 == _y2)
		return 1;

	return 0;
}
