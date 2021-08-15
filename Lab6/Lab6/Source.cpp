#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>

int bullet[99];
int bulletx[99];
int bullety[99];

void ship()
{
	printf("<-0->");
}
void gotoxy(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y);
	ship();
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void eraseShip(int x, int y, int ship, int bg, int defaultBG)
{
	gotoxy(x, y);
	setcolor(0, defaultBG);
	printf("     ");
	setcolor(ship, bg);
}
void erase(int x, int y, int bull, int bg, int defaultBG)
{
	gotoxy(x, y);
	setcolor(0, defaultBG);
	printf(" ");
	setcolor(bull, bg);
}
void createBullet(int x, int y, int limx, int limy,int maxbullet,int bullet)
{
	if (bullet < maxbullet)
	{
		gotoxy(x + 2, y - 1);
		bulletx[bullet] = x + 2;
		bullety[bullet] = y - 1;
		printf("o");
	}
}
int updateBullet(int bullet,int bull,int bg,int defaultBG)
{
	int bulletA = 0;
	int xx[99], yy[99];
	for (int i = 0; i < bullet; i++)
	{
		int x = bulletx[i];
		int y = bullety[i];
		erase(x,y,bull,bg,defaultBG);

		if (y>=1)
		{
			gotoxy(x, y-1);
			printf("o");
			xx[bulletA] = x  ;
			yy[bulletA] = y-1;
			bulletA++;
		}
		else
		{
			continue;
		}
	}
	for (int i = 0; i < bulletA; i++)
	{
		bulletx[i] = xx[i];
		bullety[i] = yy[i];
	}
	return bulletA;
}
void shipControl1(int x, int y, int limx, int limy, int ship, int bg, int defaultBG)
{
	char c = ' ';
	draw_ship(x, y);
	do
	{
		if (_kbhit())
		{

			c = _getch();
			if (c == 'a' && x >= 1)
			{
				eraseShip(x, y, ship, bg, defaultBG);
				draw_ship(--x, y);
			}
			if (c == 'd' && x <= limx - 6)
			{
				eraseShip(x, y, ship, bg, defaultBG);
				draw_ship(++x, y);
			}
			if (c == 's' && y <= limy)
			{
				eraseShip(x, y, ship, bg, defaultBG);
				draw_ship(x, ++y);
			}
			if (c == 'w' && y >= 1)
			{
				eraseShip(x, y, ship, bg, defaultBG);
				draw_ship(x, --y);
			}
			fflush(stdin);

		}
		Sleep(10);
	} while (c != 'x');
}
void shipControl2(int x, int y, int limx, int limy, int ship, int bg, int defaultBG)
{
	int bullet = 0;
	int direction = 0,shoot=0;
	char c = ' ';
	draw_ship(x, y);
	do
	{
		bullet = updateBullet(bullet, ship, bg, defaultBG);

		if (_kbhit())
		{

			c = _getch();
			if (c == 'd')
			{
				direction = 1;
			}
			if (c == 'a')
			{
				direction = 2;
			}
			if (c == 's')
			{
				direction = 0;
			}
			fflush(stdin);
			if (c == ' ')
			{
				shoot=1;
			}

		}
		
		if (direction == 2)
		{
			if (x >= 1)
			{
				eraseShip(x, y, ship, bg, defaultBG);
				draw_ship(--x, y);
			}
		}
		if (direction == 1)
		{
			if (x <= limx - 6)
			{
				eraseShip(x, y, ship, bg, defaultBG);
				draw_ship(++x, y);
			}
		}
		if (shoot>=1)
		{
			createBullet(x,y,limx,limy,5,bullet);
			bullet += 1;
			shoot -= 1;
		}
		
		Sleep(100);
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

int main()
{
	setcolor(2, 4);
	setcursor(0);
	shipControl2(38, 20, 80, 20, 2, 4, 0);
	return 0;
}