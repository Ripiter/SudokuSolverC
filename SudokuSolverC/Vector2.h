#pragma once
typedef struct Vector2 Vector2_t;

struct Vector2 {
	int x;
	int y;
};

int compare_vector2(Vector2_t vec, Vector2_t vec2);
int compare_vector(Vector2_t vec, int _x, int _y);
int compare_position(int _x1, int _y1, int _x2, int _y2);