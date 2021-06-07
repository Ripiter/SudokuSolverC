#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define clear() printf("\033[H\033[J")
#define SUDOKU_WIDTH 9
#define SUDOKU_HEIGHT 9

int map[SUDOKU_WIDTH][SUDOKU_HEIGHT] = { 0 };
int generated_map[SUDOKU_WIDTH][SUDOKU_HEIGHT] = { 0 };


typedef struct Vector2 Vector2_t;

struct Vector2 {
	int x;
	int y;
};

typedef struct DataReturn DataReturn_t;

struct DataReturn {
	Vector2_t pos;
	char character;
};


int out_of_bounds(int _x, int _y) {
	if (_x >= 0 && _x < SUDOKU_WIDTH && _y >= 0 && _y < SUDOKU_HEIGHT)
		return 0;

	return 1;
}

// x,y is the place we want to place our number
// returns vector 2 with the closes numbers
Vector2_t get_closes_middle_square(int _x, int _y) {

	// 1
	// 4
	// 7
	Vector2_t position;
	position.x = 0;
	position.y = 0;


	int places[] = { 1, 4 , 7 };

	int out_of_bounds_counter = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int xx = -1; xx <= 1; xx++) {
				for (int yy = -1; yy <= 1; yy++) {

					if (out_of_bounds(_x + xx, _y + yy) == 0) {
						if (_x + xx == places[i] && _y + yy == places[j]) {
							position.x = places[i];
							position.y = places[j];

							return position;
						}
					}
				}
			}

		}
	}

	return position;
}


Vector2_t user_input_position() {

	Vector2_t positions;

	int x = -1;
	int y = -1;

	do {
		printf("\nX: ");
		scanf_s("%d", &x);
		getchar();
		printf("\n");

	} while (x < 0 || x >= 9);

	do {
		printf("Y: ");
		scanf_s("%d", &y);
		getchar();
		printf("\n");

	} while (y < 0 || y >= 9);

	positions.x = y;
	positions.y = x;

	return positions;
}

int user_input_number() {

	int number = 0;

	do {

		printf("Number 1-9: ");
		scanf_s("%d", &number);
		getchar();
		printf("\n");

	} while (number <= 0 || number >= 10);

	return number;
}

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

int valid_squares() {
	int current_cell_mount = 0;

	for (int i = 1; i < 8; i += 3)
	{
		for (int j = 1; j < 8; j += 3)
		{
			current_cell_mount = 0;

			for (int xx = -1; xx <= 1; xx++) {
				for (int yy = -1; yy <= 1; yy++) {

					current_cell_mount += map[i + xx][j + yy];
				}
			}

			if (current_cell_mount != 45)
				return 0;
		}
	}
	return 1;
}

int valid_square_to_place(int to_place, int _startX, int _startY) {

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

int valid_lines() {

	int counter = 0;

	int fullX = 0;
	int fullY = 0;

	for (int l = 0; l < 9; l++)
	{
		counter = 0;
		//Loop thru each X fields
		for (int i = 0; i < 9; i++)
		{
			if (map[i][fullY] == 0)
				return 0;

			counter += map[i][fullY];
		}

		// Check the X counter
		if (counter != 45)
			return 0;

		// Reset values
		counter = 0;

		// Loop thru each Y fields
		for (int i = 0; i < 9; i++)
		{
			if (map[fullX][i] == 0)
				return 0;

			counter += map[fullX][i];
		}

		// Check the Y counter
		if (counter != 45)
			return 0;

		fullX++;
		fullY++;
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



Vector2_t get_current_position() {

	Vector2_t d;
	d.x = 0;
	d.y = 0;

	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo))
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());

	d.x = screenBufferInfo.dwCursorPosition.X;
	d.y = screenBufferInfo.dwCursorPosition.Y;

	return d;
}

DataReturn_t get_char_at_position(int _x, int _y) {
	DataReturn_t r;

	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo))
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());

	r.pos.x = _x;
	r.pos.y = _y;

	char buf[2];
	COORD c = { r.pos.x, r.pos.y };
	DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		printf("Error reading console.");

	r.character = buf[0];
	return r;
}


Vector2_t user_input_arrows() {
	char Arrow = 0;
	Arrow = _kbhit();

	int realX = 0;
	int realY = 0;

	DataReturn_t data;
	data.pos.x = 0;
	data.pos.y = 0;

	int done = 0;

	Vector2_t arrowPos;
	arrowPos.x = 0;
	arrowPos.y = 0;

	Vector2_t endMapPos = get_current_position();

	gotoxy(data.pos.x, data.pos.y);

	while (Arrow != 27 && done == 0) {
		Arrow = _getch();

		if (Arrow != -32) {

			if (72 == Arrow) {
				//printf("Up");
				if (data.pos.y > 0)
					data.pos.y -= 1;
			}
			if (80 == Arrow) {
				//printf("Down");
				data.pos.y++;
			}
			if (77 == Arrow) {
				//printf("Right");
				data.pos.x++;
			}
			if (75 == Arrow) {
				//printf("Left");
				if (data.pos.x > 0)
					data.pos.x--;
			}
			if (Arrow == 13) {
				//printf("Enter");
				int x = data.pos.x;
				int y = data.pos.y;

				for (int i = 0; i <= x; i++)
				{
					DataReturn_t d = get_char_at_position(i, y);

					if (d.character != '|' && d.character != ' ' && d.character != '-')
						realX += 1;
				}
				realX -= 1;
				for (int i = 0; i <= y; i++)
				{
					DataReturn_t d = get_char_at_position(x, i);

					if (d.character != '|' && d.character != ' ' && d.character != '-')
						realY += 1;
				}
				realY -= 1;

				DataReturn_t d = get_char_at_position(x, y);

				if (d.character != '|' && d.character != ' ' && d.character != '-') {
					arrowPos.y = realX;
					arrowPos.x = realY;
					done = 1;
				}

				realX = 0;
				realY = 0;
			}

			gotoxy(data.pos.x + 1, data.pos.y + 1);
		}
	}
	gotoxy(endMapPos.x, endMapPos.y + 1);
	return arrowPos;
}

int main() {

	int gameOver = 0;
	time_t t;
	srand((unsigned)time(&t));

	place_in_random_position(20);

	while (gameOver == 0) {
		print_map();
		Vector2_t place = user_input_arrows();
		int number = user_input_number();;

		if (valid_input(number, place)) {

			map[place.x][place.y] = number;

			if (victory())
			{
				printf("\nYou won the game");
				gameOver = 1;
			}
		}
		clear();
	}
	return 0;
}