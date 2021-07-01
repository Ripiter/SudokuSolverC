#pragma once

#include "Input.h"
#include "Game.h"

int map[SUDOKU_WIDTH][SUDOKU_HEIGHT] = { 0 };
int generated_map[SUDOKU_WIDTH][SUDOKU_HEIGHT] = { 0 };

int is_auto_generated(int _x, int _y) {
	if (generated_map[_x][_y] == 0)
		return 0;

	return 1;
}

int valid_place(int _x, int _y) {
	if (out_of_bounds(_x, _y) == 0) {

		if (is_auto_generated(_x, _y) == 0)
			return 1;
	}
	return 0;
}

int valid_square_to_place(int to_place, int _startX, int _startY) {

	// if we want to replace a number in a square with 0
	if (to_place == 0)
		return 1;

	Vector2_t position = get_closes_middle_square(_startX, _startY);

	for (int xx = -1; xx <= 1; xx++) {
		for (int yy = -1; yy <= 1; yy++) {

			if (map[position.x + xx][position.y + yy] == to_place)
				return 0;
		}
	}

	return 1;
}

// x and y is a direction
// x = 1 is right so y = 0 
// y = 1 is going down so x = 0
int valid_line_to_place(int to_place, int _startX, int _startY) {

	// if we want to replace a number in a line with 0
	if (to_place == 0)
		return 1;

	for (int i = 0; i < 9; i++)
	{
		if (map[i][_startY] == to_place)
			return 0;
	}

	for (int i = 0; i < 9; i++)
	{
		if (map[_startX][i] == to_place)
			return 0;
	}

	return 1;
}

void print_map() {
	printf(" -------------------");
	printf("\n");
	for (int i = 0; i < SUDOKU_WIDTH; i++)
	{
		if (i % 3 == 0 && i != 0) {
			printf(" -------------------");
			printf("\n");
		}
		printf(" | ");
		for (int j = 0; j < SUDOKU_HEIGHT; j++)
		{
			if (j % 3 == 0 && j != 0)
				printf(" | ");
			printf("%d", map[i][j]);
		}
		printf(" |");
		printf("\n");

	}
	printf(" -------------------");
	printf("\n");
}


int victory() {

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (map[i][j] == 0)
				return 0;
		}
	}

	return 1;
}


int valid_input(int _number, Vector2_t _pos) {

	if (valid_place(_pos.x, _pos.y))
		if (valid_square_to_place(_number, _pos.x, _pos.y))
			if (valid_line_to_place(_number, _pos.x, _pos.y))
				return 1;

	return 0;
}

void place_in_random_position(int _amount) {

	int placed = 0;
	int placed_counter = 0;

	Vector2_t pos;
	pos.x = 0;
	pos.y = 0;

	while (placed_counter != _amount) {

		pos.x = rand() % 9;
		pos.y = rand() % 9;

		placed = rand() % 9;
		placed += 1;

		if (valid_input(placed, pos)) {
			map[pos.x][pos.y] = placed;
			generated_map[pos.x][pos.y] = placed;
			placed_counter += 1;
		}
	}
}

int main() {
	int gameOver = 0;
	time_t t;
	srand((unsigned)time(&t));

	place_in_random_position(25);

	while (gameOver == 0) {
		print_map();
		Vector2_t place = user_input_arrows();
		int number = user_input_number();;

		if (valid_input(number, place)) {

			map[place.x][place.y] = number;

			if (victory())
			{
				gameOver = 1;
			}
		}
		clear();
	}

	printf("\nYou won the game");

	return 0;
}