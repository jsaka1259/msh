#include <common.h>

int getch(void)
{
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = fgetc(stdin);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}
