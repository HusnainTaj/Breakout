//#include<iostream>
//#include"yourgraphics.h"
//#include<cstdlib>
//#include<fstream>
//using namespace std;
//char c;
//
//
//int lives = 3;
//int score = 0;
//int check = 0;
//int hs[6] = { 0,0,0,0,0,0 };
//int highscore;
//
//
//
//
//int screenWidth, screenHeight;
//struct rect
//{
//
//	int x1 = 0;
//	int y1 = 0;
//	int x2 = 0;
//	int y2 = 0;
//	int health;
//
//
//}pad, brick[15][10];
//struct ellipse
//{
//
//	int x1 = 520;
//	int y1 = 300;
//	int x2 = x1 + 30;
//	int y2 = y1 + 30;
//	int velocityX = 0;
//	int velocityY = 2;
//
//}ball;
//void paddlemovement(int l)
//{
//	c = getKey();
//	if (pad.x1 > 0 && pad.x2 < l)
//	{
//
//		if (c == 'd')
//		{
//			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 0, 0, 0);
//
//			pad.x1 += 25;
//			pad.x2 += 25;
//			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 255, 255, 0);
//
//		}
//
//		if (c == 'a')
//		{
//
//			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 0, 0, 0);
//
//			pad.x1 -= 25;
//			pad.x2 -= 25;
//			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 255, 255, 0);
//
//		}
//	}
//	else if (pad.x1 <= 0)
//	{
//
//		if (c == 'd')
//		{
//
//			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 0, 0, 0);
//
//			pad.x1 += 25;
//			pad.x2 += 25;
//			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 255, 255, 0);
//
//		}
//	}
//	else if (pad.x2 >= l)
//	{
//
//		if (c == 'a')
//		{
//			cout << "yahi";
//			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 0, 0, 0);
//			pad.x1 -= 25;
//			pad.x2 -= 25;
//			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 255, 255, 0);
//		}
//	}
//}
//
//void save()
//{
//	ofstream write("storage.txt");
//	write << pad.x1 << " " << pad.x2 << " " << pad.y1 << " " << pad.y2 << " " << ball.x1 << " " << ball.x2 << " " << ball.y1 << " " << ball.y2 << " " << lives << " " << score << " ";
//	for (int i = 0; i < 15; i++)
//	{
//		for (int j = 0; j < 10; j++)
//		{
//			write << brick[i][j].x1 << " " << brick[i][j].x2 << " " << brick[i][j].y1 << " " << brick[i][j].y2 << " " << brick[i][j].health << " ";
//
//		}
//	}
//	write.close();
//}
//
//void load()
//{
//	ifstream read("storage.txt");
//	if (read)
//	{
//		read >> pad.x1 >> pad.x2 >> pad.y1 >> pad.y2 >> ball.x1 >> ball.x2 >> ball.y1 >> ball.y2 >> lives >> score;
//		for (int i = 0; i < 15; i++)
//		{
//			for (int j = 0; j < 10; j++)
//			{
//				read >> brick[i][j].x1 >> brick[i][j].x2 >> brick[i][j].y1 >> brick[i][j].y2 >> brick[i][j].health;
//
//			}
//		}
//		read.close();
//	}
//
//}
//
//void quit()
//{
//	if (c == 'q')
//	{
//		cls();
//		gotoxy(55, 14);
//		cout << "GAME QUITTED";
//		delay(100000);
//
//	}
//}
//
//void pause()
//{
//	if (c == 'p')
//		while (1)
//		{
//			c = getKey();
//			if (c == 'r')
//			{
//				break;
//			}
//		}
//}
//
//void respawn()
//{
//	if (ball.y2 > pad.y2 + 70)
//	{
//		lives--;
//		if (lives == 2)
//		{
//			drawEllipse(900, 38, 930, 65, 0, 0, 0, 0, 0, 0);
//
//		}
//		else if (lives == 1)
//		{
//			drawEllipse(850, 38, 880, 65, 0, 0, 0, 0, 0, 0);
//
//		}
//		else if (lives == 0)
//		{
//			drawEllipse(800, 38, 830, 65, 0, 0, 0, 0, 0, 0);
//
//		}
//		ball.x1 = 520;
//		ball.y1 = 300;
//		ball.x2 = ball.x1 + 30;
//		ball.y2 = ball.y1 + 30;
//		ball.velocityX = 0;
//		ball.velocityY = 2;
//
//
//		drawEllipse(ball.x1, ball.y1, ball.x2, ball.y2, 0, 0, 0, 255, 255, 255);
//		delay(400);
//
//
//	}
//}
//
//void gameover()
//{
//	if (lives == 0)
//	{
//
//
//
//		cls();
//		gotoxy(55, 14);
//		cout << "GAME OVER" << endl;
//		delay(1000000);
//
//	}
//
//}
//
//void gamewon()
//{
//	if (check == 100)
//	{
//		cls();
//		gotoxy(45, 14);
//		cout << "CONGRATULATIONS.....YOU HAVE WON";
//		delay(100000);
//
//	}
//}
//
//void highestscore()
//{
//
//
//
//
//}
//
//int main()
//{
//	char z;
//
//
//	SetProcessDPIAware();
//	getWindowDimensions(screenWidth, screenHeight);
//	cls();
//	pad.x1 = 450;
//	pad.y1 = screenHeight - 40;
//	pad.x2 = pad.x1 + 200;
//	pad.y2 = pad.y1 + 15;
//
//	for (int i = 0; i < 6; i++)
//	{
//		cout << hs[i] << endl;
//	}
//	cout << "Press n for NEW GAME" << endl;
//	cout << "Press l to LOAD GAME" << endl;
//	cin >> z;
//	cls();
//
//	brick[0][0].x1 = 0;
//	brick[0][0].y1 = 60;
//	brick[0][0].x2 = brick[0][0].x1 + screenWidth / 10;
//	brick[0][0].y2 = brick[0][0].y1 + 20;
//
//	for (int i = 4, k = 60; i < 15; i++)
//	{
//
//		for (int j = 0; j < 10; j++)
//		{
//			brick[i][j].health = (rand() % (5 - 3 + 1)) + 3;
//
//			brick[i][j].x1 = brick[0][0].x1 + (j * (screenWidth / 10));
//			brick[i][j].y1 = (i * k);
//			brick[i][j].x2 = brick[i][j].x1 + screenWidth / 10;
//			brick[i][j].y2 = (i + 1) * 20;
//		}
//
//		k = 20;
//	}
//
//	if (z == 'l')
//	{
//		load();
//	}
//
//	ifstream readhs("highscore.txt");
//	for (int i = 1; i < 6; i++)
//	{
//		readhs >> hs[i];
//	}
//	highscore = hs[5];
//
//
//	gotoxy(80, 2);
//	cout << "Lives:";
//	gotoxy(10, 2);
//	cout << "Score:" << score;
//	gotoxy(30, 2);
//	cout << "High Score : " << highscore;
//
//	drawRectangle(0, 0, screenWidth, screenHeight, 0, 0, 0, 0, 0, 0);
//	gotoxy(0, 0);
//	if (lives == 3)
//	{
//
//		drawEllipse(800, 38, 830, 65, 204, 0, 0, 204, 0, 0);
//		drawEllipse(850, 38, 880, 65, 204, 0, 0, 204, 0, 0);
//		drawEllipse(900, 38, 930, 65, 204, 0, 0, 204, 0, 0);
//	}
//	else if (lives == 2)
//	{
//		drawEllipse(800, 38, 830, 65, 204, 0, 0, 204, 0, 0);
//		drawEllipse(850, 38, 880, 65, 204, 0, 0, 204, 0, 0);
//	}
//	else if (lives == 1)
//	{
//		drawEllipse(800, 38, 830, 65, 204, 0, 0, 204, 0, 0);
//
//	}
//
//
//
//	showConsoleCursor(false);
//
//	//loop for printing the bricks
//	for (int i = 4, k = 60; i < 15; i++)
//	{
//
//		for (int j = 0; j < 10; j++)
//		{
//			if (brick[i][j].health >= 3)
//			{
//
//				drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 255, 0, 0);
//			}
//			if (brick[i][j].health == 2)
//			{
//				drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 69, 82, 69);
//
//			}
//			if (brick[i][j].health == 1)
//			{
//				drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 142, 86, 190);
//
//			}
//			if (brick[i][j].health == 0)
//			{
//				drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 0, 0, 0);
//
//			}
//		}
//	}
//
//
//
//
//	//printing paddle
//	drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 255, 255, 0);
//
//
//	int r = 23;
//	int g = 98;
//	int b = 42;
//
//	//main loop
//	while (true)
//	{
//		drawLine(0, 10, screenWidth, 10, 255, 0, 0);
//		drawLine(0, 90, screenWidth, 90, 255, 0, 0);
//		drawLine(screenWidth / 2, 0, screenWidth / 2, 90, 255, 0, 0);
//		drawLine(0, 0, 0, screenHeight, 255, 0, 0);
//		drawLine(screenWidth, 0, screenWidth, screenHeight, 255, 0, 0);
//		//moving the paddle
//
//		paddlemovement(screenWidth);
//		drawEllipse(ball.x1, ball.y1, ball.x2, ball.y2, 0, 0, 0, 0, 0, 0);
//		ball.x1;
//		ball.x2;
//		ball.y1 += ball.velocityY;
//		ball.y2 += ball.velocityY;
//
//		drawEllipse(ball.x1, ball.y1, ball.x2, ball.y2, 0, 0, 0, 255, 255, 255);
//		if (ball.x2 >= pad.x1 + 95 && ball.x1 <= pad.x1 + 105 && ball.y2 >= pad.y1)
//		{
//			ball.velocityX = 0;
//			ball.velocityY = -2;
//		}
//		else if ((ball.x1 >= pad.x1 + 105 && ball.x1 <= pad.x1 + 150 && ball.y2 >= pad.y1))
//		{
//			ball.velocityX = 1;
//			ball.velocityY = -2;
//		}
//		else if ((ball.x1 >= pad.x1 + 105 && ball.x1 <= pad.x2 && ball.y2 >= pad.y1))
//		{
//			ball.velocityX = 2;
//			ball.velocityY = -2;
//		}
//		else if (ball.x2 >= pad.x1 + 45 && ball.x2 <= pad.x1 + 95 && ball.y2 >= pad.y1)
//		{
//			ball.velocityX = -1;
//			ball.velocityY = -2;
//		}
//		else if (ball.x2 >= pad.x1 && ball.x2 <= pad.x1 + 45 && ball.y2 >= pad.y1)
//		{
//			ball.velocityX = -2;
//			ball.velocityY = -2;
//		}
//		if (ball.x1 < 0 || ball.x2 > screenWidth) {
//			ball.velocityX *= -1;
//		}
//		else if (ball.y1 < 93)
//		{
//			ball.velocityY *= -1;
//		}
//
//		drawEllipse(ball.x1, ball.y1, ball.x2, ball.y2, 0, 0, 0, 0, 0, 0);
//		ball.x1 += ball.velocityX;
//		ball.x2 += ball.velocityX;
//		ball.y1 += ball.velocityY;
//		ball.y2 += ball.velocityY;
//		drawEllipse(ball.x1, ball.y1, ball.x2, ball.y2, 0, 0, 0, 255, 255, 255);
//		ball.velocityX == 1;
//		ball.velocityY == 2;
//		delay(10);
//
//		for (int i = 4; i < 15; i++)
//		{
//			for (int j = 0; j < 10; j++)
//			{
//				if (brick[i][j].health > 0)
//				{
//					if (ball.x2 + ball.velocityX > brick[i][j].x1 && ball.x1 + ball.velocityX<brick[i][j].x2 && ball.y2>brick[i][j].y1 && ball.y1 < brick[i][j].y2)
//					{
//						brick[i][j].health--;
//						ball.velocityX *= -1;
//
//						score++;
//						gotoxy(10, 2);
//						cout << "Score:" << score;
//						gotoxy(0, 0);
//						if (brick[i][j].health == 2)
//						{
//							drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 69, 82, 69);
//						}
//						else if (brick[i][j].health == 1)
//						{
//							drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 142, 86, 190);
//						}
//
//
//						else if (brick[i][j].health == 0)
//						{
//							drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 0, 0, 0);
//							check++;
//						}
//
//					}
//					else if (ball.x2 > brick[i][j].x1 && ball.x1  < brick[i][j].x2 && ball.y2 + ball.velocityY> brick[i][j].y1 && ball.y1 + ball.velocityY < brick[i][j].y2)
//					{
//						brick[i][j].health--;
//						ball.velocityY *= -1;
//
//						score++;
//						gotoxy(10, 2);
//						cout << "Score:" << score;
//						gotoxy(0, 0);
//						if (brick[i][j].health == 2)
//						{
//							drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 69, 82, 69);
//						}
//						else if (brick[i][j].health == 1)
//						{
//							drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 142, 86, 190);
//						}
//
//
//						else if (brick[i][j].health == 0)
//						{
//							drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 0, 0, 0);
//						}
//					}
//
//				}
//
//			}
//		}
//		if (ball.y2 > pad.y2 + 70)
//		{
//			lives--;
//			if (lives == 2)
//			{
//				drawEllipse(900, 38, 930, 65, 0, 0, 0, 0, 0, 0);
//
//			}
//			else if (lives == 1)
//			{
//				drawEllipse(850, 38, 880, 65, 0, 0, 0, 0, 0, 0);
//
//			}
//			ball.x1 = 520;
//			ball.y1 = 300;
//			ball.x2 = ball.x1 + 30;
//			ball.y2 = ball.y1 + 30;
//			ball.velocityX = 0;
//			ball.velocityY = 2;
//
//
//			drawEllipse(ball.x1, ball.y1, ball.x2, ball.y2, 0, 0, 0, 255, 255, 255);
//			delay(400);
//
//
//		}
//		if (score > highscore)
//		{
//			highscore = score;
//		}
//		gotoxy(30, 2);
//		cout << "High Score : " << highscore;
//
//		if (c == 's')
//		{
//			save();
//		}
//
//		respawn();
//
//		pause();
//
//		quit();
//
//		gameover();
//
//		gamewon();
//
//	}
//
//	int current = score;
//
//	hs[0] = score;
//
//	for (int i = 0; i < 6; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			if (hs[j] > hs[j + 1])
//			{
//				int temp = hs[j + 1];
//				hs[j + 1] = hs[j];
//				hs[j] = temp;
//			}
//		}
//	}
//
//	ofstream writehs("highscore.txt");
//	for (int i = 1; i < 6; i++)
//	{
//		writehs << hs[i] << " ";
//	}
//}