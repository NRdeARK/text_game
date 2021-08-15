#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
void ship()
{
	printf("<-0->");
}
void gotoxy(int x,int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x,int y)
{
	gotoxy(x, y);
	ship();
}
void eraseShip(int x,int y)
{
	gotoxy(x, y);
	printf("     ");
}
void shipControl(int x, int y,int limx,int limy)
{
	char c = ' ';
	draw_ship(x, y);
	do
	{
		if (_kbhit())
		{
			
			c = _getch();
			if (c == 'a'&& x>=1)
			{
				eraseShip(x, y);
				draw_ship(--x, y);
			}
			if (c == 'd'&& x<=limx-6)
			{
				eraseShip(x, y);
				draw_ship(++x, y);
			}
			if (c == 's'&& y<=limy)
			{
				eraseShip(x, y);
				draw_ship(x, ++y);
			}
			if (c == 'w'&& y>=1)
			{
				eraseShip(x, y);
				draw_ship(x, --y);
			}
			fflush(stdin);
			
		}
		Sleep(10);
	} while (c != 'x');
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

int main() 
{
	setcolor(2,4);
	setcursor(0);
	shipControl(38, 20, 80, 20);
	return 0;
}