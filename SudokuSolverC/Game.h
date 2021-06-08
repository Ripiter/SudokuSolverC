#pragma once
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "Vector2.h"
#include <conio.h>
#include "DataReturn.h"

#define SUDOKU_WIDTH 9
#define SUDOKU_HEIGHT 9

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define clear() printf("\033[H\033[J")


Vector2_t get_current_position();
DataReturn_t get_char_at_position(int _x, int _y);
Vector2_t get_closes_middle_square(int _x, int _y);