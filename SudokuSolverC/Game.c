#include "Game.h"

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
						if (compare_position(_x + xx, _y + yy, places[i], places[j])) {
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

