//#include<iostream>
//#include<fstream>
//#include<conio.h>
//#include<cstdlib>
//#include<time.h>
//#include "youregraphics.h"
//int wi = 0, h = 0;
//int w = 106, screenheight = 29;
//int brikWidth = 0;
//int bx = 0, by = 0;
//
//void live(int life)
//{
//	int change = 3;
//	int i = 0;
//	int lx1 = wi - 25 * 3 - 20, ly1 = h - 20 - 20;
//
//	while (i < 3)
//	{
//		drawEllipse(lx1 + i * 5, ly1, lx1 + 20 + i * 5, ly1 + 20 , 255, 255, 255, 0, 0, 0);
//		lx1 = lx1 + 20;
//		i++;
//
//	}
//
//	lx1 = wi - 25 * 3 - 20, ly1 = h - 20 - 20;
//	i = 0;
//	while (i < life)
//	{
//		drawEllipse(lx1 + i * 5, ly1, lx1 + 20 + i * 5, ly1 + 20, 0, 0, 255, 255, 153, 0);
//		lx1 = lx1 + 20;
//		i++;
//	}
//
//	//if (life == 3)
//	//	while (i < 3)
//	//	{
//	//		drawEllipse(lx1 + i * 5, ly1, lx1 + 20 + i * 5, ly1 + 20, 0, 0, 255, 255, 153, 0);
//	//		lx1 = lx1 + 20;
//	//		i++;
//	//	}
//	//if (life == 2) {
//	//	while (i < 2)
//	//	{
//	//		drawEllipse(lx1 + i * 5, ly1, lx1 + 20 + i * 5, ly1 + 20, 0, 0, 255, 255, 153, 0);
//	//		lx1 = lx1 + 20;
//	//		i++;
//	//	}
//	//	drawEllipse(lx1 + i * 5, ly1, lx1 + 20 + i * 5, ly1 + 20 , 255, 255, 255, 0, 0, 0);
//	//}
//	//if (life == 1) {
//	//	drawEllipse(lx1 + i * 5, ly1, lx1 + 20 + i * 5, ly1 + 20 , 0, 0, 255, 255, 153, 0);
//	//	lx1 = lx1 + 20;
//	//	while (i < 2)
//	//	{
//	//		drawEllipse(lx1 + i * 5, ly1, lx1 + 20 + i * 5, ly1 + 20 , 255, 255, 255, 0, 0, 0);
//	//		lx1 = lx1 + 20;
//	//		i++;
//	//	}
//
//	//}
//
//}
//void collision(int& ballx, int& bally, int& playerx, int& playery, int& by, int brickh[5][10], int bricky[5][10], int brickx[5][10]) {
//	if (
//		ballx < playerx + 100 &&
//		ballx + 10 > playerx &&
//		bally < playery + 10 &&
//		bally + 10 > playery
//		)
//	{
//		if (by > 0)
//			bally = playery - 11;
//		else
//			bally = playery + 16;
//
//
//		by *= -1;
//	}
//
//	for (int y = 0; y < 5; y++)
//	{
//		for (int x = 0; x < 10; x++) {
//			if (brickh[y][x] != 0) {
//				if (
//					ballx + bx * 3 < brickx[y][x] + brikWidth &&
//					ballx + bx * 3 + 10 > brickx[y][x] &&
//					bally + by * 3 < bricky[y][x] + 15 &&
//					bally + by * 3 + 10 > bricky[y][x]
//					) {
//					by *= -1;
//					brickh[y][x]--;
//
//					int gap = 5;
//
//
//					if (brickh[y][x] == 0) {
//
//						drawRectangle(brickx[y][x], bricky[y][x], brickx[y][x] + brikWidth, bricky[y][x] + 25, 0, 0, 0, 0, 0, 0);
//					
//					}
//					else if (brickh[y][x] == 2)
//						drawRectangle(brickx[y][x], bricky[y][x] + gap, brickx[y][x] + brikWidth - gap, bricky[y][x] + 25, 255, 75, 184, 0, 255, 72);
//					else 
//						drawRectangle(brickx[y][x], bricky[y][x] + gap, brickx[y][x] + brikWidth - gap, bricky[y][x] + 25, 64, 75, 184, 0, 255, 72);
//
//				}
//			}
//		}
//	}
//}
//
//using namespace std;
//
//
//int main() {
//	srand(time(NULL));
//	// initialising
//
//	int lives = 3;
//	int startball = 0;
//	int dir = 1; // 1- topright(for wall x+w>=x,x+W<x+w,y>=yy<y+h), 2- topleft(for wall,,,x>=x,x<x+w,y>=y,y<y+h), 3- bottomleft(for ball x+w>=x,x+W<x+w,y>=yy<y+h, 4-bottomright (for ball,,,x>=x,x<x+w,y>=y,y<y+h)
//	int bricksleft = 50;
//	int win = 0;
//	int lose = 0;
//
//	SetProcessDPIAware();
//	int row = 0, col = 0;
//	getWindowDimensions(wi, h);
//	getConsoleWindowDimensions(row, col);
//
//	cls();
//	showConsoleCursor(false);
//
//	delay(100);
//
//
//	brikWidth = wi / 10;
//	bool reload = false;
//	int gap = 5;
//	int top = 40;
//
//	int bricksx[5][10];
//	int bricksy[5][10];
//	int bricksh[5][10];
//
//	for (int y = 0; y < 5; y++)
//	{
//		for (int x = 0; x < 10; x++)
//		{
//			bricksx[y][x] = x * brikWidth;
//			bricksy[y][x] = 25 * y + top;
//
//			if(y == 0 || y == 1)
//				bricksh[y][x] = rand() % 3 + 1;
//			else bricksh[y][x] = 3;
//
//		}
//	}
//
//	int playerx = 350, playery = 390, ballx = 390, bally = 360;
//	char c = 'c';
//
//
//
//
//	int px = 0;
//
//	bool started = false;
//	//promt to reload
//
//	ifstream saves("save.txt");
//
//	if (saves.is_open()) {
//		char question = '3';
//		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n                         INPUT 1 TO RELOAD OLD SAVE AND 2 TO START A NEW GAME";
//		do {
//			question = getKey();
//			if (question == '1')
//				reload = true;
//		} while (question != '1' && question != '2');
//
//		if (reload) {
//			saves >> lives;
//			saves >> ballx;
//			saves >> bx;
//			saves >> bally;
//			saves >> by;
//			saves >> playerx;
//			saves >> px;
//			saves >> playery;
//			saves >> bricksleft;
//			for (int y = 0; y < 5; y++)
//			{
//				for (int x = 0; x < 10; x++)
//				{
//					saves >> bricksx[y][x];
//					saves >> bricksy[y][x];
//					saves >> bricksh[y][x];
//				}
//			}
//		}
//		saves.close();
//	}
//
//	delay(200);
//	cls();
//	cout << "\n\n                                      YOU READY?";
//	delay(1500);
//	cls();
//	cout << " BUCKLE UP";
//	delay(1500);
//	cls();
//	cout << " LETS GO";
//	delay(1500);
//	cls();
//	drawRectangle(0, 0, wi, h, 255, 255, 255, 0, 0, 0);
//
//	for (int y = 0; y < 5; y++)
//	{
//		for (int x = 0; x < 10; x++)
//		{
//			if (bricksh[y][x] != 0)
//				drawRectangle(bricksx[y][x], bricksy[y][x] + gap, bricksx[y][x] + brikWidth - gap, bricksy[y][x] + 25, 64, 75, 184, 0, 255, 72);
//		}
//	}
//
//	while (lives > 0)
//	{
//		live(lives);
//		while (true)
//		{
//
//			drawEllipse(ballx, bally, ballx + 10, bally + 10, 0, 0, 0, 0, 0, 0);
//			if (c == ' ' && !started) {
//				bx = (rand() % 10) - 5;
//				if (bx == 0) { bx = 1; }
//
//				by = -4;//( rand() % 7) - 3;
//
//				// if (by == 0 && by >= 0) { by *= -1; }
//
//				started = true;
//			}
//
//
//			if (ballx < 0) {
//				ballx = 0;
//				bx *= -1;
//
//			}
//			if (ballx + 10 > wi) {
//				ballx = wi - 10;
//				bx *= -1;
//			}
//			if (bally < 0) {
//				bally = 0;
//				by *= -1;
//
//			}
//			if (bally + 11 > h) {
//				/*bally = h - 21;
//				by *= -1;*/
//				lives--;
//				live(lives);
//				drawRectangle(playerx, playery, playerx + 100, playery + 15, 0, 0, 0, 0, 0, 0);
//				delay(1000);
//				playerx = 350, playery = 390, ballx = 390, bally = 360;
//				if (lives == 0) break;
//			}
//
//			collision(ballx, bally, playerx, playery, by, bricksh, bricksy, bricksx);
//
//			ballx += bx;
//			bally += by;
//
//			//if (ballx <= playerx && ballx + ballx + 21 < playerx && bally <= playery && bally + bally + 21 >= playery) {
//			//    //ballx = playerx + playerx + 100;
//			//    by *= -1;
//			//}
//
//
//			drawEllipse(ballx, bally, ballx + 10, bally + 10, 255, 0, 0, 255, 0, 0);
//
//			//collision
//
//
//			drawRectangle(playerx, playery, playerx + 100, playery + 15, 0, 0, 0, 0, 0, 0);
//
//			c = getKey();
//			//if (c == 32) { startball = 1; }
//			if (c == 'q')break;
//
//			if (c == 'd') {
//				px = 30;
//			}
//
//			if (c == 'a') {
//				px = -30;
//			}
//			if (c == 'p')
//			{
//				while (c != 'r')
//				{
//					delay(1);
//					c = getKey();
//				}
//			}
//
//			if (c == 's') {
//
//				ofstream saves("save.txt");
//
//
//				saves << lives << " ";
//				saves << ballx << " ";
//				saves << bx << " ";
//				saves << bally << " ";
//				saves << by << " ";
//				saves << playerx << " ";
//				saves << px << " ";
//				saves << playery << " ";
//				saves << bricksleft << " ";
//				for (int y = 0; y < 5; y++)
//				{
//					for (int x = 0; x < 10; x++)
//					{
//						saves << bricksx[y][x] << " ";
//						saves << bricksy[y][x] << " ";
//						saves << bricksh[y][x] << " ";
//					}
//				}
//				saves.close();
//			}
//
//			playerx += px;
//			px = 0;
//
//			if (playerx < 0) { playerx = 0; }
//			else if (playerx + 100 > wi) { playerx = wi - 100; }
//
//			drawRectangle(playerx, playery, playerx + 100, playery + 15, 255, 0, 0, 255, 0, 0);
//
//			delay(10);
//
//
//		}
//	}
//	gotoxy(w + 1, screenheight + 1);
//	system("pause");
//
//
//	gotoxy(0, 0);
//
//	return 0;
//
//}
