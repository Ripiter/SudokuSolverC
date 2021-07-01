#include "Input.h"


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

		printf("Number 0-9: ");
		scanf_s("%d", &number);
		getchar();
		printf("\n");

	} while (number < 0 || number >= 10);

	return number;
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