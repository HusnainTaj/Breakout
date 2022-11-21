#include <iostream>
//#include "mygraphics.h"
#include "yourgraphics.h"

using namespace std;

int player_speed = 40;
int gameWidth = 1080, gameHeight = 600;
int gameX = 0, gameY = 0;

#pragma region Structures

struct Color
{
	int R = 0;
	int G = 0;
	int B = 0;
};

struct {
	Color White;
	Color Black;
	Color Red;
	Color Green;
	Color Blue;

	Color Front;
	Color Back;
} Colors;

struct Player
{
	int x;
	int y;

	int width = 120;
	int height = 20;

	int force_x = 1;

	int lives = 3;
} player;

struct Brick
{
	int x = 0;
	int y = 0;

	int width = 100;
	int height = 30;

	int health = 3;
} bricks[5][10];

struct Ball
{
	int x = 200;
	int y = 200;

	int width = 20;
	int height = 20;

	int force_x = 0;
	int force_y = 0;
} ball;

struct GameManager
{
	bool started = false;
	int score = 0;
	bool paused = false;

	int BricksRowCount = 5;
	int BricksColCount = 10;

	bool showStats = false;
} GM;

#pragma endregion

#pragma region Library Extensions

void drawRectangle(int x1, int y1, int x2, int y2, Color stroke, Color fill)
{
	drawRectangle(gameX + x1, y1, gameX + x2, y2, stroke.R, stroke.G, stroke.B, fill.R, fill.G, fill.B);
}

void drawRectangle(int x1, int y1, int x2, int y2, Color color)
{
	drawRectangle(gameX + x1, y1, gameX + x2, y2, color, color);
}

void drawEllipse(int x1, int y1, int x2, int y2, Color stroke, Color fill)
{
	drawEllipse(gameX + x1, y1, gameX + x2, y2, stroke.R, stroke.G, stroke.B, fill.R, fill.G, fill.B);
}

void drawEllipse(int x1, int y1, int x2, int y2, Color color)
{
	drawEllipse(gameX + x1, y1, gameX + x2, y2, color, color);
}

#pragma endregion

void DrawPlayer(Player& player)
{
	// Optimization
	if (player.force_x == 0) return;

	// remove player last position
	// // breaks with overflow logic
	//drawRectangle(player.x, player.y, player.x + player.width, player.y + player.height, Colors.Back);

	// remove whole player line
	drawRectangle(0, player.y, gameWidth, player.y + player.height, Colors.Back);

	// remove space where there player is not
	//drawRectangle(0, player.y, player.x, player.y + player.height, Colors.Back);
	//drawRectangle(player.x+player.width, player.y, gameWidth, player.y + player.height, Colors.Back);

	// removing overflow separately
	/*if (player.x + player.width > gameWidth)
	{
		int overflow_right = (player.x + player.width) - gameWidth;
		drawRectangle(0, player.y, overflow_right, player.y + player.height, Colors.Back);

		if (overflow_right > player.width)
			player.x = 0;
	}
	else if (player.x < 0)
	{
		int overflow_left = player.x * -1;
		drawRectangle(gameWidth - overflow_left, player.y, gameWidth, player.y + player.height, Colors.Back);

		if (overflow_left > player.width)
			player.x = gameWidth - player.width;
	}

	drawRectangle(player.x < 0 ? 0 : player.x, player.y, player.x + player.width > gameWidth ? gameWidth : player.x + player.width, player.y + player.height, Colors.Back);
	*/

	// Best solution: calculate the area where paddle the last was and paint only that
	// should fix flickering



	// Adding force
	int step = 25;
	if (player.force_x > 0)
	{
		player.x += step;
		player.force_x -= step;

		if (player.force_x < 0) player.force_x = 0;
	}
	else if (player.force_x < 0)
	{
		player.x -= step;
		player.force_x += step;

		if (player.force_x > 0) player.force_x = 0;
	}

	//player.x += player.force_x;
	//player.force_x = 0;

	if (player.x + player.width > gameWidth)
	{
		int overflow_right = (player.x + player.width) - gameWidth;

		drawRectangle(0, player.y, overflow_right, player.y + player.height, Colors.Front);

		if (overflow_right > player.width)
			player.x = 0;
	}
	else if (player.x < 0)
	{
		int overflow_left = player.x * -1;

		drawRectangle(gameWidth - overflow_left, player.y, gameWidth, player.y + player.height, Colors.Front);

		if (overflow_left > player.width)
			player.x = gameWidth - player.width;
	}

	drawRectangle(player.x < 0 ? 0 : player.x, player.y, player.x + player.width > gameWidth ? gameWidth : player.x + player.width, player.y + player.height, Colors.Front);
}

int GetBricksLeft()
{
	int count = 0;
	for (int r = 0; r < GM.BricksRowCount; r++)
	{
		for (int c = 0; c < GM.BricksColCount; c++)
		{
			if (bricks[r][c].health != 0) count++;
		}
	}

	return count;
}

void HandleBrickCollission(Ball& ball)
{
	for (int r = 0; r < 5; r++)
	{
		for (int c = 0; c < 10; c++)
		{
			Brick& brick = bricks[r][c];

			if (brick.health == 0) continue;

			if (
				ball.x + ball.force_x < brick.x + brick.width &&
				ball.x + ball.force_x + ball.width > brick.x &&
				ball.y + ball.force_y < brick.y + brick.height &&
				ball.height + ball.y + ball.force_y > brick.y
			)
			{
				ball.force_y *= -1;

				brick.health--;

				Color bColor = Colors.Back;

				switch (brick.health)
				{
					case 3: bColor = Colors.Green; break;
					case 2: bColor = Colors.Blue; break;
					case 1: bColor = Colors.Red; break;
					default: bColor = Colors.Back; break;
				}

				Color col = bColor;

				if (brick.health != 0)
				{
					col.R *= 1 / 1.35;
					col.G *= 1 / 1.35;
					col.B *= 1 / 1.35;
				}

				drawRectangle(brick.x, brick.y, brick.x + brick.width, brick.y + brick.height, col, bColor);

				if(brick.health == 0)
					GM.score++;

				if (GetBricksLeft() == 0)
				{
					GM.paused = true;

					cls();
					cout << "You Won!";
				}
			}
		}
	}
}

bool HandlePaddleCollission(Ball& ball)
{
	if (
		ball.x + ball.force_x < player.x + player.width &&
		ball.x + ball.force_x + ball.width > player.x &&
		ball.y + ball.force_y < player.y + player.height &&
		ball.height + ball.y + ball.force_y > player.y
		)
	{
		ball.force_y *= -1;

		// adding force on ball based on speed of paddle
		//ball.force_x = player.force_x / 10;

		return true;
	}

	return false;
}

void DrawBall(Ball& ball)
{
	HandleBrickCollission(ball);

	HandlePaddleCollission(ball);

	drawEllipse(ball.x, ball.y, ball.x + ball.width, ball.y + ball.height, Colors.Back);

	// adding force
	ball.x += ball.force_x;
	ball.y += ball.force_y;

	if (ball.x + ball.width >= gameWidth || ball.x + ball.width <= 0 ) ball.force_x *= -1;
	//if (ball.y + ball.height >= gameHeight || ball.y  <= 0) ball.force_y *= -1;
	//if (ball.y <= 0) ball.force_y *= -1;

	drawEllipse(ball.x, ball.y, ball.x + ball.width, ball.y + ball.height, Colors.Front);
}

void setUpColors()
{
	Colors.White.R = 236;
	Colors.White.G = 240;
	Colors.White.B = 241;

	Colors.Black.R = 38;
	Colors.Black.G = 38;
	Colors.Black.B = 38;

	Colors.Green.R = 26;
	Colors.Green.G = 188;
	Colors.Green.B = 156;

	Colors.Red.R = 231;
	Colors.Red.G = 76;
	Colors.Red.B = 60;

	Colors.Blue.R = 52;
	Colors.Blue.G = 152;
	Colors.Blue.B = 219;

	Colors.Front = Colors.Black;
	Colors.Back = Colors.White;
}

int main() 
{
	srand(time(NULL));

	setUpColors();

	// Initialising
	//getWindowDimensions(gameWidth, gameHeight);
	showConsoleCursor(false);
	cls();


	// Frame
	drawRectangle(gameX , 0, gameX + gameWidth, gameHeight*2, 255, 255, 255, Colors.Back.R, Colors.Back.G, Colors.Back.B);
	
	// Player Set up
	player.x = gameWidth / 2 - player.width / 2;
	player.y = gameHeight - player.height;

	// Ball Set up
	ball.y = gameHeight - 40;
	ball.x = gameWidth / 2 + ball.width / 4;

	// Bricks Set up
	int brickWidth = gameWidth / GM.BricksColCount;
	for (int r = 0; r < GM.BricksRowCount; r++)
	{
		for (int c = 0; c < GM.BricksColCount; c++)
		{
			Brick b;

			b.width = brickWidth;

			b.x = 0 + c * b.width;
			b.y = 0 + r * b.height;

			b.health = (rand() % 3) + 1;

			bricks[r][c] = b;

			//drawRectangle(gameX + b.x, b.y, gameX + b.x + b.width, b.y + b.height, 22, 160, 133, Colors.Green.R, Colors.Green.G, Colors.Green.B);
			
			Color bColor = Colors.Back;

			switch (b.health)
			{
			case 3: bColor = Colors.Green; break;
			case 2: bColor = Colors.Blue; break;
			case 1: bColor = Colors.Red; break;
			default: bColor = Colors.Back; break;
			}

			Color col = bColor;

			if (b.health != 0)
			{
				col.R *= 1 / 1.35;
				col.G *= 1 / 1.35;
				col.B *= 1 / 1.35;
			}

			drawRectangle(b.x, b.y, b.x + b.width, b.y + b.height, col, bColor);
		}
	}

	// Stats set up
	time_t startTime = time(NULL);
	int framecount = 0;
	time_t t = time(NULL);

	int samethingcount = 0; // need for pause to work

	while (true) 
	{
		char c = getKey();

		// i have no idea why but yea
		if (c == 'p')
		{
			samethingcount++;

			if (samethingcount > 1)
			{
				GM.paused = !GM.paused;
				samethingcount = 0;
			}
		}

		if (!GM.paused)
		{
			DrawBall(ball);

			DrawPlayer(player);

			if (ball.y > gameHeight)
			{
				player.lives--;

				ball.y = gameHeight - 40;
				ball.x = gameWidth / 2 + ball.width / 4;

				ball.force_x = 0;
				ball.force_y = 0;

				if (player.lives == 0)
				{
					cls();
					gotoxy(50, 20);
					cout << "You lost!";
					GM.paused = true;
				}
			}

			if (c == ' ')
			{
				GM.started = true;

				//ball.force_x = (rand() % 6);
				//ball.force_y = (rand() % 10) * -1;

				ball.force_x = 4;
				ball.force_y = -6;
			}
			if (c == 'd') player.force_x = player_speed;
			if (c == 'a') player.force_x = -player_speed;


			if (c == 'j') ball.force_x = -3;
			if (c == 'l') ball.force_x = 3;


			if (c == 'i') ball.force_y = -3;
			if (c == 'k') ball.force_y = 3;
		}


		if (c == 'q') break;
		if (c == 'o') GM.showStats = true;
		if (c == 'c') cls();
		
		

		delay(1000 / 120);

		#pragma region Statistics
		framecount++;
		if (time(NULL) > t)
		{
			if (GM.showStats)
			{
				gotoxy(0, 1);
				cout << "FOR: " << ((player.force_x < 0) ? "-" : "+") << abs(player.force_x);
				/*gotoxy(0, 3);
				cout << "x: " << ((ball.x < 0) ? "-" : "+") << abs(ball.x);
				cout << " y: " << ((ball.y < 0) ? "-" : "+") << abs(ball.y);*/
				gotoxy(0, 0);
				cout << "FPS: " << framecount;

				gotoxy(0, 2);
				cout << "TIM: " << time(NULL) - startTime;

				gotoxy(0, 3);
				cout << "SCO: " << GM.score;

				gotoxy(0, 4);
				cout << "LIV: " << player.lives;

				gotoxy(0, 5);
				cout << "BFX: " << ((ball.force_x < 0) ? "-" : "+") << abs(ball.force_x);

				gotoxy(0, 6);
				cout << "BFY: " << ((ball.force_y < 0) ? "-" : "+") << abs(ball.force_y);
			}
			
			framecount = 0;
			t = time(NULL);
		}
		
		
		#pragma endregion

	}

	cls();
	showConsoleCursor(true);

	gotoxy(0, 0);

	return 0;
}