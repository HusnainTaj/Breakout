// Programming Fundamentals Project 
// Breakout Game
// Husnain Taj (22L-6786) && Afaq Khaliq (22L-6939)

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#pragma comment(lib, "Winmm.lib") // for PlaySound
//#include "mygraphics.h"
//#include "yourgraphics.h"
#include "youregraphics.h"

using namespace std;

// References
// ------------------------------------------------------------------------------
// Playing Sound
// https://learn.microsoft.com/en-us/previous-versions/dd743680(v=vs.85)
// ------------------------------------------------------------------------------
// For colored output text using cout 
// https://en.wikipedia.org/wiki/ANSI_escape_code
// ------------------------------------------------------------------------------
// Changing color scheme for the whole console
// system("color 70"); 
// https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/color
// ------------------------------------------------------------------------------


// Settings

// whether to enable testing code like controling the ball 
bool testing = false;

float dpiRatio = 1;

float BALL_FORCE = 6;
float FireBallForceInc = BALL_FORCE * 0.05;

int gameWidth = 0, gameHeight = 0;
int consoleRows = 0, consoleCols = 0;

const int MIN_BREAK_BONUS_TIME = 1;

const int PLAYER_SPEED = 60;
const int PLAYER_MOVE_STEP = 20;

const int POWERUP_DURATION = 10;

const int TOP_ROW_HEIGHT = 80;
const int BRICKS_ROW_COUNT = 6, BRICKS_COL_COUNT = 24;

#pragma region Structures

struct Color
{
	int R = 0;
	int G = 0;
	int B = 0;
};

struct {
	Color White;
	Color ConsoleWhite;
	Color Black;
	Color Red;
	Color DarkRed;
	Color Green;
	Color Blue;
	Color Purple;
	Color Orange;

	Color Front;
	Color Back;
} COLORS;

struct Player
{
	const int shortWidth = 50;
	const int normalWidth = 120;
	const int longWidth = 200;

	int x;
	int y;

	int width = 120;
	int height = 20;

	int force_x = 0;

	int lives = 3;

} player;

struct Ball
{
	const int normalWidth = 20;
	const int normalHeight = 20;
	const int fireballSizeInc = 10;

	float x = 200;
	float y = 200;

	int width = normalWidth;
	int height = normalHeight;

	float force_x = 0;
	float force_y = 0;

	bool fireball = false;
} ball;

struct Projectile
{
	int x = 0;
	int y = 0;

	const int diameter = 80;
	const int radius = diameter / 2;
	const int force_y = -20;

	bool active = false;
} projectile;

struct
{
	const int shorten = 1;
	const int elongate = 2;
	const int fireball = 3;
	const int projectile = 4;
	const int life = 5;
} PowerUpTypes;

struct PowerUp
{
	int x = 0;
	int y = 0;

	const int width = 20;
	const int height = 20;

	const int force_y = 3;

	int type;
	bool active = false;
	bool dropping = false;

	int startedTime = 0;

	Color color;
} powerUp;

struct
{
	int score = 0;

	bool started = false;
	bool over = false;
	bool paused = false;

	bool focusOut = false;

	bool showStats = false;
	int BricksLeft = BRICKS_COL_COUNT * BRICKS_ROW_COUNT;

} GameManager;

struct Brick
{
	int x = 0;
	int y = 0;

	int width = 100;
	int height = 50;

	int health = 3;
} bricks[BRICKS_ROW_COUNT][BRICKS_COL_COUNT];

#pragma endregion

#pragma region Prototypes
void Clear(Color);
void UpdateFontSize(int);
void DrawLives();
void DrawPlayer(bool);
void PrintCenter(int row, string start, string str, string end);
bool onChance(int);
int GetBricksLeft();
#pragma endregion

#pragma region Library Extensions

void drawRectangle(int x1, int y1, int x2, int y2, Color stroke, Color fill)
{
	drawRectangle( x1, y1,  x2, y2, stroke.R, stroke.G, stroke.B, fill.R, fill.G, fill.B);
}

void drawRectangle(int x1, int y1, int x2, int y2, Color color)
{
	drawRectangle( x1, y1,  x2, y2, color, color);
}

void drawEllipse(int x1, int y1, int x2, int y2, Color stroke, Color fill)
{
	drawEllipse( x1, y1,  x2, y2, stroke.R, stroke.G, stroke.B, fill.R, fill.G, fill.B);
}

void drawEllipse(int x1, int y1, int x2, int y2, Color color)
{
	drawEllipse(x1, y1,  x2, y2, color, color);
}

bool onKey(char key, char c)
{
	// Making both inputs lower case for easir comparision
	// this will also make it so we wont have to check an input twice for both cases
	if (key >= 'A' && key <= 'Z') key = char((int(key)) + 32);
	if (c >= 'A' && c <= 'Z') c = char((int(c)) + 32);

	return key == c;
}
#pragma endregion

#pragma region HighScores

int HighScores[5];

bool AddScore(int score)
{
	// let say scores = 8, 6, 4, 2, 1
	// now if the new score is 7
	// we first find the index 'i' of the score less then 7
	// then we start swapping elements from the end of the array to that index i
	// so after the below logic the array becomes 8, 1, 6, 4, 2
	// now we replace 1 at i with the new score
	for (int i = 0; i < 5; i++)
	{
		if (score > HighScores[i])
		{
			// swap from the end to i
			for (int j = 4; j > i; j--)
			{
				int temp = HighScores[j];
				HighScores[j] = HighScores[j - 1];
				HighScores[j - 1] = temp;
			}

			HighScores[i] = score;
			return true;
		}
	}

	return false;
}

void SaveHighScores()
{
	ofstream saveFile;
	saveFile.open("highscores.txt");

	for (int i = 0; i < 5; i++)
	{
		saveFile << HighScores[i] << endl;
	}

	saveFile.close();
}

void LoadHighScores()
{
	ifstream saveFile;
	saveFile.open("highscores.txt");

	for (int i = 0; i < 5; i++)
	{
		saveFile >> HighScores[i];
	}

	saveFile.close();
}

#pragma endregion

#pragma region Colission Detection

int LastTimeBrickBroke = 0;
void HandleBrickCollission(Ball& ball)
{
	// detecting collision for the next ball position
	int nextBallX = ball.x + ball.force_x;
	int nextBallY = ball.y + ball.force_y;

	int minDistanceX = ball.width / 2 + bricks[0][0].width / 2;
	int minDistanceY = ball.height / 2 + bricks[0][0].height / 2;

	int minProjectileDistanceX = projectile.radius + bricks[0][0].width / 2;

	for (int r = 0; r < BRICKS_ROW_COUNT; r++)
	{
		for (int c = 0; c < BRICKS_COL_COUNT; c++)
		{
			// dont even check for collision if bricks health is zero
			if (bricks[r][c].health == 0) continue;

			bool collisioned = false;
			Brick& brick = bricks[r][c];

			float distanceX = abs((brick.x + brick.width / 2) - (nextBallX + ball.width / 2));
			float distanceY = abs((brick.y + brick.height / 2) - (nextBallY + ball.height / 2));

			if (distanceX <= minDistanceX && distanceY <= minDistanceY) 
			{
				if (nextBallY + ball.height / 2 > brick.y + brick.height ||
					nextBallY + ball.height / 2 < brick.y)
				{
					ball.force_y *= -1;
				}
				else ball.force_x *= -1;
				
				if (ball.fireball)
					brick.health = 0;
				else
					brick.health--;

				collisioned = true;
			}

			float projectileDistanceX = abs((brick.x + brick.width / 2) - (projectile.x + projectile.radius));

			// Collisoin for Projectile
			if (
				projectile.active &&
				projectileDistanceX <= minProjectileDistanceX &&
				projectile.y < brick.y + brick.height
				)
			{
				brick.health = 0;
				collisioned = true;
			}

			// only redraw if something collided
			if (collisioned)
			{
				PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);

				Color brickColor = COLORS.Back;

				switch (brick.health)
				{
				case 3: brickColor = COLORS.Green; break;
				case 2: brickColor = COLORS.Blue; break;
				case 1: brickColor = COLORS.Red; break;
				default: brickColor = COLORS.Back; break;
				}

				Color darkerBrickColor = brickColor; // for border

				if (brick.health != 0)
				{
					darkerBrickColor.R *= 1 / 1.35;
					darkerBrickColor.G *= 1 / 1.35;
					darkerBrickColor.B *= 1 / 1.35;
				}

				drawRectangle(brick.x, brick.y, brick.x + brick.width, brick.y + brick.height, darkerBrickColor, brickColor);

				if (brick.health <= 0)
				{
					// Reward a bonus if player broke the brick in 1s of breaking the last one
					if (time(NULL) - LastTimeBrickBroke <= MIN_BREAK_BONUS_TIME)
						GameManager.score += 10;
					else
						GameManager.score += 5;

					GameManager.BricksLeft--;
					LastTimeBrickBroke = time(NULL);

					// Spawn a new power up - 40% chance it will be dropped
					if (!powerUp.dropping && !powerUp.active && onChance(40))
					{
						powerUp.color = COLORS.Purple;
						powerUp.x = brick.x + brick.width / 2;

						// dropping from last bricks height to avoid reprinting bricks
						powerUp.y = bricks[BRICKS_ROW_COUNT - 1][BRICKS_COL_COUNT - 1].y + bricks[BRICKS_ROW_COUNT - 1][BRICKS_COL_COUNT - 1].height;
						
						int randomChance = rand() % 100;
						
						if (randomChance < 5) // 5
						{
							powerUp.type = PowerUpTypes.life;
							powerUp.color = COLORS.Red;
						}
						else if (randomChance >= 5 && randomChance < 20) // 15
							powerUp.type = PowerUpTypes.projectile;
						else if(randomChance >= 20 && randomChance < 50) // 30
							powerUp.type = PowerUpTypes.fireball;
						else if (randomChance >= 50 && randomChance < 100) // 50
							powerUp.type = onChance(50) ? PowerUpTypes.elongate : PowerUpTypes.shorten;

						powerUp.dropping = true;
					}
				}

				// Stop the game if all bricks are broken
				if (GameManager.BricksLeft <= 0) GameManager.over = true;
			}


			if (collisioned && !projectile.active)
				return;
		}
	}
}

bool HandlePaddleCollission(Ball& ball)
{
	// detecting collision for the next ball position
	int nextBallX = ball.x + ball.force_x;
	int nextBallY = ball.y + ball.force_y;

	int minDistanceX = ball.width / 2 + player.width / 2;
	int minDistanceY = ball.height / 2 + player.height / 2;

	float distanceX = abs((player.x + player.width / 2) - (nextBallX + ball.width / 2));
	float distanceY = abs((player.y + player.height / 2) - (nextBallY + ball.height / 2));

	if (distanceX <= minDistanceX && distanceY <= minDistanceY)
	{
		int ballCenter = nextBallX + ball.width / 2;

		float ballDistance = player.x + player.width - ballCenter;

		float ratio = ballDistance / player.width;

		ball.force_x = BALL_FORCE * cos((ratio * (180 - 30) + 15) * 3.14 / 180);
		ball.force_y = -BALL_FORCE * sin((ratio * (180 - 30) + 15) * 3.14 / 180);

		return true;
	}

	return false;
}

void setFireball(bool on)
{
	drawEllipse(ball.x, ball.y, ball.x + ball.width, ball.y + ball.height, COLORS.Back);

	if (on && !ball.fireball && GameManager.started)
	{
		ball.width = ball.normalWidth + ball.fireballSizeInc;
		ball.height = ball.normalHeight + ball.fireballSizeInc;

		ball.fireball = true;
	}
	else if (!on && ball.fireball && GameManager.started)
	{
		ball.width = ball.normalWidth;
		ball.height = ball.normalHeight;

		ball.fireball = false;
	}
}

bool HandlePaddleCollission(PowerUp& powerUp)
{
	// detecting collision for the next ball position
	int nextProjectX = powerUp.x;
	int nextProjectY = powerUp.y + powerUp.force_y;

	int minDistanceX = powerUp.width / 2 + player.width / 2;
	int minDistanceY = powerUp.height / 2 + player.height / 2;

	float distanceX = abs((player.x + player.width / 2) - (nextProjectX + powerUp.width / 2));
	float distanceY = abs((player.y + player.height / 2) - (nextProjectY + powerUp.height / 2));

	if (distanceX <= minDistanceX && distanceY <= minDistanceY)
	{
		if (powerUp.type == PowerUpTypes.shorten)
		{
			player.width = player.shortWidth;
		}
		else if (powerUp.type == PowerUpTypes.elongate)
		{
			player.width = player.longWidth;
		}
		else if (powerUp.type == PowerUpTypes.fireball)
		{
			setFireball(true);
		}
		else if (powerUp.type == PowerUpTypes.life && player.lives < 3)
		{
			player.lives++;
			DrawLives();
		}
		else if (powerUp.type == PowerUpTypes.projectile)
		{
			projectile.x = player.x + player.width / 2;
			projectile.y = player.y - projectile.diameter;

			projectile.active = true;
		}

		powerUp.dropping = false;
		powerUp.active = true;
		powerUp.startedTime = time(NULL);

		DrawPlayer(true);

		return true;
	}

	return false;
}

#pragma endregion

#pragma region Drawing

void Clear(Color bg = COLORS.Back)
{
	gotoxy(0, 0);
	cls();
	delay(100);
	drawRectangle(0, 0, gameWidth, gameHeight, bg);
	delay(200);
}

void DrawPlayer(bool redraw = false)
{
	if (redraw) drawRectangle(0, player.y, gameWidth, player.y + player.height, COLORS.Back);

	// Removing old paddle
	if (player.x + player.width > gameWidth)
	{
		int overflow_right = (player.x + player.width) - gameWidth;
		drawRectangle(0, player.y, overflow_right, player.y + player.height, COLORS.Back);
	}
	else if (player.x < 0)
	{
		int overflow_left = player.x * -1;
		drawRectangle(gameWidth - overflow_left, player.y, gameWidth, player.y + player.height, COLORS.Back);
	}

	// Calculating the differnece b/w the area of last and new paddle position and remove that
	if (player.x + player.force_x > player.x)
		drawRectangle(player.x, player.y, player.x + player.force_x + player.width, player.y + player.height, COLORS.Back);
	else
		drawRectangle(player.x + player.force_x, player.y, player.x + player.width, player.y + player.height, COLORS.Back);


	// Adding force
	// Moving player in steps to make the movement smooth
	if (player.force_x > 0)
	{
		player.x += PLAYER_MOVE_STEP;
		player.force_x -= PLAYER_MOVE_STEP;

		if (player.force_x < 0) player.force_x = 0;
	}
	else if (player.force_x < 0)
	{
		player.x -= PLAYER_MOVE_STEP;
		player.force_x += PLAYER_MOVE_STEP;

		if (player.force_x > 0) player.force_x = 0;
	}


	// Calculate how much player is out of one side of the screen and teleport him accordingly
	if (player.x + player.width > gameWidth)
	{
		int overflow_right = (player.x + player.width) - gameWidth;

		drawRectangle(0, player.y, overflow_right, player.y + player.height, COLORS.Front);

		if (overflow_right > player.width)
			player.x = 0;
	}
	else if (player.x < 0)
	{
		int overflow_left = player.x * -1;

		drawRectangle(gameWidth - overflow_left, player.y, gameWidth, player.y + player.height, COLORS.Front);

		if (overflow_left > player.width)
			player.x = gameWidth - player.width;
	}

	drawRectangle(player.x < 0 ? 0 : player.x, player.y, player.x + player.width > gameWidth ? gameWidth : player.x + player.width, player.y + player.height, COLORS.Front);
}

void DrawBall()
{
	drawEllipse(ball.x, ball.y, ball.x + ball.width, ball.y + ball.height, COLORS.Back);

	HandleBrickCollission(ball);

	HandlePaddleCollission(ball);

	// Checking for Wall Collision
	if (ball.x + ball.force_x + ball.width >= gameWidth)
	{
		ball.x = gameWidth - ball.width;
		ball.force_x *= -1;
	}
	if (ball.x <= 0)
	{
		ball.x = 0;
		ball.force_x *= -1;
	}

	if (ball.y + ball.force_y < TOP_ROW_HEIGHT)
	{
		ball.y = TOP_ROW_HEIGHT + 1;
		ball.force_y *= -1;
	}

	// adding force
	ball.x += ball.force_x + (ball.fireball ? (FireBallForceInc * (ball.force_x + 1 / abs(ball.force_x + 1))) : 0);
	ball.y += ball.force_y + (ball.fireball ? (FireBallForceInc * (ball.force_y + 1 / abs(ball.force_y + 1))) : 0);

	drawEllipse(ball.x, ball.y, ball.x + ball.width, ball.y + ball.height, ball.fireball ? COLORS.Orange : COLORS.Front);
}

void DrawPowerUp()
{
	if (powerUp.active)
	{
		if (time(NULL) - powerUp.startedTime > POWERUP_DURATION)
		{
			powerUp.active = false;

			if (powerUp.type == PowerUpTypes.elongate || powerUp.type == PowerUpTypes.shorten)
				player.width = player.normalWidth;
			else if (powerUp.type == PowerUpTypes.fireball)
				setFireball(false);

			DrawPlayer(true);
		}
	}

	if (powerUp.dropping)
	{
		bool hit = HandlePaddleCollission(powerUp);

		drawEllipse(powerUp.x, powerUp.y, powerUp.x + powerUp.width, powerUp.y + powerUp.height, COLORS.Back);

		// adding force
		powerUp.y += powerUp.force_y;

		// remove the power up once its out of the screen
		if (powerUp.y > gameHeight + 100)
		{
			powerUp.dropping = false;
		}

		if (!hit) drawEllipse(powerUp.x, powerUp.y, powerUp.x + powerUp.width, powerUp.y + powerUp.height, powerUp.color);
	}
}

void DrawProjectile()
{
	if (projectile.active)
	{
		drawRectangle(projectile.x, projectile.y, projectile.x + projectile.radius, projectile.y + projectile.diameter, COLORS.Back);

		projectile.y += projectile.force_y;

		if (projectile.y <= TOP_ROW_HEIGHT)
		{
			projectile.active = false;
			return;
		}

		int r3 = (projectile.radius / (float)2.5);
		int r2 = (projectile.radius / (float)1.38);
		drawEllipse(projectile.x + projectile.radius / 2 - r3 / 2, projectile.y + projectile.radius, projectile.x + projectile.radius / 2 - r3 / 2 + r3, projectile.y + projectile.radius + r3, COLORS.Orange);
		drawEllipse(projectile.x + projectile.radius / 2 - r2 / 2, projectile.y + projectile.radius / 2, projectile.x + projectile.radius / 2 + r2 / 2, projectile.y + projectile.radius / 2 + r2, 230, 126, 34, 230, 126, 34);
		drawEllipse(projectile.x, projectile.y, projectile.x + projectile.radius, projectile.y + projectile.radius, COLORS.Orange);
	}
}

void DrawHeart(int x1, int y1, int scale, Color color) {
	// x1 and y1 coordinate of leftmost corner and it takes scale 
	// scale determines size of heart
	if (scale % 2 != 0)
	{
		scale = scale / 2 * 2;
	}
	drawLine(x1, y1, x1 + (scale / 2), y1 + (scale / 2), color.R, color.G, color.B);
	drawLine(x1 + scale, y1, x1 + (scale / 2), y1 + (scale / 2), color.R, color.G, color.B);
	drawLine(x1, y1, x1 + scale / 4.0, y1 - scale / 4.0, color.R, color.G, color.B);
	drawLine(x1 + scale / 4.0, y1 - scale / 4.0, x1 + (scale / 2), y1, color.R, color.G, color.B);
	drawLine(x1 + scale, y1, (x1 + scale) - scale / 4.0, y1 - scale / 4.0, color.R, color.G, color.B);
	drawLine((x1 + scale) - scale / 4.0, y1 - scale / 4.0, x1 + (scale / 2), y1, color.R, color.G, color.B);

	for (int i = 2; i <= scale; i++) {
		drawLine(x1 + i, y1, x1 + (scale / 2), y1 + (scale / 2), color.R, color.G, color.B);
	}
	int max = y1 - scale / 4.0;
	for (int i = 2; max <= y1; i++, max++) {
		drawLine(x1, y1, x1 + scale / 4.0, (y1 - scale / 4.0) + i, color.R, color.G, color.B);
		drawLine(x1 + scale, y1, (x1 + scale) - scale / 4.0, (y1 - scale / 4.0) + i, color.R, color.G, color.B);
		drawLine(x1 + scale / 4.0, (y1 - scale / 4.0) + i, x1 + (scale / 2), y1, color.R, color.G, color.B);
		drawLine((x1 + scale) - scale / 4.0, (y1 - scale / 4.0) + i, x1 + (scale / 2), y1, color.R, color.G, color.B);

	}
}

void DrawLives()
{
	for (int i = 1; i <= 3; i++)
	{
		if (i <= player.lives)
			DrawHeart(gameWidth - (50 * i) - 25 - (i * 20), 30, TOP_ROW_HEIGHT - 20, COLORS.Red);
		else
			DrawHeart(gameWidth - (50 * i) - 25 - (i * 20), 30, TOP_ROW_HEIGHT - 20, Color{ 10,10,10 });
	}
}

int lastScore = -1;
void DrawScore(bool force = false)
{
	// only print new score if the score has changed
	if (lastScore != GameManager.score || force)
	{
		string a = to_string(GameManager.score);
		gotoxy(0, 0);

		cout << "\033[27m " << a << "";

		lastScore = GameManager.score;

		gotoxy(consoleCols / 2 - strlen("SAVE   PAUSE") / 2, 0);
		cout << "\033[7mS\033[27mAVE   \033[7mP\033[27mAUSE\033[27m";
	}
}

void DrawBricks()
{
	for (int r = 0; r < BRICKS_ROW_COUNT; r++)
	{
		for (int c = 0; c < BRICKS_COL_COUNT; c++)
		{
			Brick& b = bricks[r][c];

			Color bColor = COLORS.Back;

			switch (b.health)
			{
			case 3: bColor = COLORS.Green; break;
			case 2: bColor = COLORS.Blue; break;
			case 1: bColor = COLORS.Red; break;
			default: bColor = COLORS.Back; break;
			}

			// darkering the color for borders

			Color darkerbColor = bColor;

			if (b.health != 0)
			{
				darkerbColor.R *= 1 / 1.35;
				darkerbColor.G *= 1 / 1.35;
				darkerbColor.B *= 1 / 1.35;
			}

			drawRectangle(b.x, b.y, b.x + b.width, b.y + b.height, darkerbColor, bColor);
		}
	}

	GameManager.BricksLeft = GetBricksLeft();
}

void RedrawGame()
{
	Clear();

	drawRectangle(0, 0, gameWidth, TOP_ROW_HEIGHT, COLORS.Front);

	DrawLives();

	DrawPlayer(true);

	DrawBall();

	lastScore = -1;
	DrawScore();

	if (GameManager.paused)
	{
		gotoxy(consoleCols / 2 - strlen("SAVE   RESUME") / 2, 0);
		cout << "\033[7mS\033[27mAVE   \033[7mR\033[27mESUME\033[27m";
	}
	else 
	{
		gotoxy(consoleCols / 2 - strlen("SAVE   PAUSE ") / 2, 0);
		cout << "\033[7mS\033[27mAVE   \033[7mP\033[27mAUSE \033[27m";
	}

	DrawBricks();
}

#pragma endregion

#pragma region Saving Game State
bool saveFileExists = false;
bool DoesSaveFileExist()
{
	ifstream saveFile;
	saveFile.open("gamestate.txt");

	return saveFile.is_open();
}

void SaveGameState()
{
	ofstream saveFile;
	saveFile.open("gamestate.txt");

	saveFile << player.x << endl;
	saveFile << player.y << endl;
	saveFile << player.width << endl;
	saveFile << player.height << endl;
	saveFile << player.force_x << endl;
	saveFile << player.lives << endl;

	saveFile << ball.x << endl;
	saveFile << ball.y << endl;
	saveFile << ball.width << endl;
	saveFile << ball.height << endl;
	saveFile << ball.force_x << endl;
	saveFile << ball.force_y << endl;

	saveFile << powerUp.x << endl;
	saveFile << powerUp.y << endl;
	saveFile << powerUp.type << endl;
	saveFile << powerUp.startedTime << endl;
	saveFile << powerUp.dropping << endl;
	saveFile << powerUp.active << endl;
	saveFile << powerUp.color.R << endl;
	saveFile << powerUp.color.G << endl;
	saveFile << powerUp.color.B << endl;

	saveFile << projectile.x << endl;
	saveFile << projectile.y << endl;
	saveFile << projectile.active << endl;

	saveFile << GameManager.paused << endl;
	saveFile << GameManager.score << endl;
	saveFile << GameManager.showStats << endl;
	saveFile << GameManager.started << endl;
	saveFile << GameManager.BricksLeft << endl;
	saveFile << GameManager.over << endl;

	for (size_t r = 0; r < BRICKS_ROW_COUNT; r++)
	{
		for (size_t c = 0; c < BRICKS_COL_COUNT; c++)
		{
			Brick b = bricks[r][c];

			saveFile << b.x << endl;
			saveFile << b.y << endl;
			saveFile << b.width << endl;
			saveFile << b.height << endl;
			saveFile << b.health << endl;
		}
	}

	saveFile.close();
}

void LoadGameState()
{
	ifstream saveFile;
	saveFile.open("gamestate.txt");

	saveFile >> player.x;
	saveFile >> player.y;
	saveFile >> player.width;
	saveFile >> player.height;
	saveFile >> player.force_x;
	saveFile >> player.lives;

	saveFile >> ball.x;
	saveFile >> ball.y;
	saveFile >> ball.width;
	saveFile >> ball.height;
	saveFile >> ball.force_x;
	saveFile >> ball.force_y;

	saveFile >> powerUp.x;
	saveFile >> powerUp.y;
	saveFile >> powerUp.type;
	saveFile >> powerUp.startedTime;
	saveFile >> powerUp.dropping;
	saveFile >> powerUp.active;
	saveFile >> powerUp.color.R;
	saveFile >> powerUp.color.G;
	saveFile >> powerUp.color.B;

	saveFile >> projectile.x;
	saveFile >> projectile.y;
	saveFile >> projectile.active;

	saveFile >> GameManager.paused;
	saveFile >> GameManager.score;
	saveFile >> GameManager.showStats;
	saveFile >> GameManager.started;
	saveFile >> GameManager.BricksLeft;
	saveFile >> GameManager.over;

	GameManager.paused = true; // pause the game on load so player has time to get ready

	for (size_t r = 0; r < BRICKS_ROW_COUNT; r++)
	{
		for (size_t c = 0; c < BRICKS_COL_COUNT; c++)
		{
			Brick& b = bricks[r][c];

			saveFile >> b.x;
			saveFile >> b.y;
			saveFile >> b.width;
			saveFile >> b.height;
			saveFile >> b.health;
		}
	}

	RedrawGame();

	saveFile.close();
}

#pragma endregion

#pragma region Initial Set up

void setUpColors()
{
	COLORS.White.R = 236;
	COLORS.White.G = 240;
	COLORS.White.B = 241;

	COLORS.ConsoleWhite.R = 204;
	COLORS.ConsoleWhite.G = 204;
	COLORS.ConsoleWhite.B = 204;

	COLORS.Black.R = 38;
	COLORS.Black.G = 38;
	COLORS.Black.B = 38;

	COLORS.Green.R = 26;
	COLORS.Green.G = 188;
	COLORS.Green.B = 156;

	COLORS.Red.R = 231;
	COLORS.Red.G = 76;
	COLORS.Red.B = 60;

	COLORS.DarkRed.R = 192;
	COLORS.DarkRed.G = 57;
	COLORS.DarkRed.B = 43;

	COLORS.Blue.R = 52;
	COLORS.Blue.G = 152;
	COLORS.Blue.B = 219;

	COLORS.Purple.R = 116;
	COLORS.Purple.G = 94;
	COLORS.Purple.B = 197;

	COLORS.Orange.R = 211;
	COLORS.Orange.G = 84;
	COLORS.Orange.B = 0;

	COLORS.Front = COLORS.Black;
	COLORS.Back = COLORS.White;
}

void setInitPos()
{
	// Player Set up
	player.x = gameWidth / 2 - player.width / 2;
	player.y = gameHeight - player.height - 20;

	drawRectangle(0, player.y, gameWidth, player.y + player.height, COLORS.Back);

	// Ball Set up
	setFireball(false);
	ball.y = player.y - ball.height - 20;
	ball.x = gameWidth / 2 - ball.width / 2;

	ball.force_x = 0;
	ball.force_y = 0;

	DrawPlayer(true);

	GameManager.started = false;
}

#pragma endregion

#pragma region Main Menu
const int menuItemsLength = 3;
string menuItems[menuItemsLength] = { "CONTINUE", "NEW GAME", "EXIT    " };
int currentMenuItem = 0;

void printMenuItems()
{
	int startRow = consoleRows / 2 - 5;

	if (startRow < 0) startRow = 0;

	int a = consoleCols / 4 - strlen("BREAKOUT") / 2 - 1;
	gotoxy(a + 1, startRow + 1);
	cout << "\033[73;27;4;30;47;27mBREAK\033[3mOUT\033[23m\033[24;30;47m" << endl; //4;30;47;27

	for (int i = 0; i < menuItemsLength; i++)
	{
		gotoxy(a, startRow + i + 3);

		if (currentMenuItem == i)
		{
			if (i == 0 && !saveFileExists)
				cout << "\033[27;37;48;2;231;76;60m" << " " << menuItems[i] << " " << "\033[30;47;29m";
			else
				cout << "\033[7m" << " " << menuItems[i] << " " << "\033[27m";
		}
		else
			cout << " " << menuItems[i] << " ";

	}

	gotoxy(a - 2, startRow + 4 + 3);
	cout << " \033[7m TAJ && AFK ";
	gotoxy(0, 0);
}

string repeatStr(string s, int times)
{
	string neww;

	for (size_t i = 0; i < times; i++)
	{
		neww += s;
	}

	return neww;
}

void PrintCenterHScores(int row, string start, string str, string end, int division = 2)
{
	gotoxy(consoleCols / 2, row);

	int a = round((consoleCols / division - str.length() / 2));
	int b = (consoleCols / 2) - a - str.length() + ((consoleCols % 2 == 0) ? 1 : 2);

	cout << repeatStr(" ", a) << start << str << end << repeatStr(" ", b);
}

void PrintCenter(int row, string start, string str, string end)
{
	int a = round((consoleCols / 2 - str.length() / 2));

	gotoxy(a, row);

	cout << start << str << end;
}

void printHighScores()
{
	int startRow = consoleRows / 2 - 3;

	cout << "\033[7m";
	for (size_t i = 0; i <= startRow; i++)
	{
		PrintCenterHScores(i, "", "", "");
	}

	PrintCenterHScores(startRow, "\033[27m", " HIGH SCORES ", "\033[7m", 4);

	PrintCenterHScores(startRow + 1, "", "", "");
	cout << "\033[7m";

	if (HighScores[0] == 0)
	{

		PrintCenterHScores(startRow + 2, "", "NO", "", 4);
		PrintCenterHScores(startRow + 3, "", "SCORES", "", 4);
		PrintCenterHScores(startRow + 4, "", "YET", "", 4);
		PrintCenterHScores(startRow + 5, "", "", "", 4);
		PrintCenterHScores(startRow + 6, "", "PLAY MORE!", "", 4);
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			string outputs = to_string(i + 1) + ". " + to_string(HighScores[i]);

			if (HighScores[i] != 0)
				PrintCenterHScores(startRow + i + 2, "", outputs, "", 4);
			else
				PrintCenterHScores(startRow + i + 2, "", "", "");
		}
	}

	for (size_t i = startRow + 7; i <= consoleRows + 1; i++)
	{
		PrintCenterHScores(i, "", "", "");
	}

}
#pragma endregion

#pragma region Transitions

const float TRANSITION_SPEED = 1;

void TransitionRight(Color first, Color second)
{
	for (float i = 0; i < gameWidth + gameWidth / 2; i += TRANSITION_SPEED)
	{
		drawLine(0 + i, 0, 0 + i, gameHeight, first.R, first.G, first.B);
	}

	delay(200);

	for (float i = 0; i < gameWidth + gameWidth / 2; i += TRANSITION_SPEED)
	{
		drawLine(0 + i, 0, 0 + i, gameHeight, second.R, second.G, second.B);
	}

	delay(200);

	for (float i = 0; i < gameWidth + gameWidth / 2; i += TRANSITION_SPEED)
	{
		drawLine(0 + i, 0, 0 + i, gameHeight, COLORS.Back.R, COLORS.Back.G, COLORS.Back.B);
	}
}

void TransitionLeft(Color first, Color second)
{
	for (float i = gameWidth; i > 0; i -= TRANSITION_SPEED)
	{
		drawLine(i, 0, i, gameHeight, first.R, first.G, first.B);
	}

	delay(100);

	for (float i = gameWidth; i > 0; i -= TRANSITION_SPEED)
	{
		drawLine(i, 0, i, gameHeight, second.R, second.G, second.B);
	}

	delay(100);

	for (float i = gameWidth; i > 0; i -= TRANSITION_SPEED)
	{
		drawLine(i, 0, i, gameHeight, COLORS.Back.R, COLORS.Back.G, COLORS.Back.B);
	}
}

void TransitionUp(Color Back, Color Front)
{
	for (int i = 0; i < gameHeight + gameHeight / 2; i++)
	{
		drawLine(0, gameHeight - i, gameWidth, gameHeight - i, Front.R, Front.G, Front.B);
		drawLine(0, gameHeight - i + gameHeight / 2, gameWidth, gameHeight - i + gameHeight / 2, Back.R, Back.G, Back.B);
	}
}

void TransitionDown(Color First, Color Second)
{
	for (float i = 0; i < gameHeight + gameHeight / 2; i += TRANSITION_SPEED)
	{
		drawLine(0, i, gameWidth, i, First.R, First.G, First.B);
	}

	delay(200);

	for (float i = 0; i < gameHeight + gameHeight / 4; i += TRANSITION_SPEED)
	{
		drawLine(0, i, gameWidth, i, Second.R, Second.G, Second.B);
	}

	/*delay(200);

	for (float i = 0; i < gameHeight + gameHeight / 4; i+= 0.5)
	{
		drawLine(0, i, gameWidth, i, COLORS.Back.R, COLORS.Back.G, COLORS.Back.B);
	}*/
}
#pragma endregion

bool onChance(int chance)
{
	int r = rand() % 100;

	if (r < chance) return true;

	return false;
}

int GetBricksLeft()
{
	int count = 0;
	for (int r = 0; r < BRICKS_ROW_COUNT; r++)
	{
		for (int c = 0; c < BRICKS_COL_COUNT; c++)
		{
			if (bricks[r][c].health > 0) count++;
		}
	}

	return count;
}

// Changes the font size of the console to get specified no of rows
void UpdateFontSize(int rowsCount)
{
	rowsCount++;
	HWND tconsole = GetConsoleWindow();
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	GetCurrentConsoleFontEx(consoleHandle, FALSE, &cfi);
	float a = cfi.dwFontSize.Y / cfi.dwFontSize.X;

	cfi.dwFontSize.Y = ((float)gameHeight / rowsCount) / dpiRatio;


	cfi.FontWeight = FW_BOLD;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(consoleHandle, TRUE, &cfi);
	GetCurrentConsoleFontEx(consoleHandle, FALSE, &cfi);
	float b = cfi.dwFontSize.Y / (float)cfi.dwFontSize.X;

	consoleCols = ((float)gameWidth / (float)cfi.dwFontSize.X) / dpiRatio;
	consoleRows = ((float)gameHeight / cfi.dwFontSize.Y) / dpiRatio;

	delay(500);
}

// Changes the font size of the console to a specific height
void UpdateFontSizePx(int fHeight)
{
	HWND tconsole = GetConsoleWindow();
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	GetCurrentConsoleFontEx(consoleHandle, FALSE, &cfi);
	cfi.dwFontSize.Y = fHeight / dpiRatio;
	cfi.FontWeight = FW_BOLD;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(consoleHandle, TRUE, &cfi);
	GetCurrentConsoleFontEx(consoleHandle, FALSE, &cfi);

	consoleCols = ((float)gameWidth / (float)cfi.dwFontSize.X) / dpiRatio;
	consoleRows = ((float)gameHeight / cfi.dwFontSize.Y) / dpiRatio;

	delay(500);
}

int main()
{
	cout << "Loading...";
	PlaySound(TEXT("bgsound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);

	HWND console = GetConsoleWindow();
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	srand(time(NULL));
	system("color 70"); // https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/color

	float dpi = GetDpiForSystem();
	float wdpi = GetDpiForWindow(console);

	dpiRatio = wdpi / dpi;

	SetProcessDPIAware();
	ShowWindow(console, SW_SHOWMAXIMIZED);

	delay(400);

	saveFileExists = DoesSaveFileExist();

	LoadHighScores();

	getWindowDimensions(gameWidth, gameHeight);
	getConsoleWindowDimensions(consoleCols, consoleRows);

	// Setting ball speed based on screen height
	BALL_FORCE = gameHeight / 150;
	FireBallForceInc = BALL_FORCE * 0.10;

	showConsoleCursor(false);
	cls();

	setUpColors();


#pragma region Main Menu

	UpdateFontSize(8);

	// Updating consoles color table with custom colors
	// also adjusting the buffer size to match with font size for 8 rows
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(consoleHandle, &info);
	info.ColorTable[0] = RGB(COLORS.Black.R, COLORS.Black.G, COLORS.Black.B);
	info.ColorTable[2] = RGB(COLORS.Green.R, COLORS.Green.G, COLORS.Green.B);
	info.ColorTable[4] = RGB(COLORS.Red.R, COLORS.Red.G, COLORS.Red.B);
	info.ColorTable[5] = RGB(COLORS.Purple.R, COLORS.Purple.G, COLORS.Purple.B);
	info.ColorTable[7] = RGB(COLORS.White.R, COLORS.White.G, COLORS.White.B);

	info.bFullscreenSupported = true;
	info.dwSize.X = consoleCols + 1;
	info.dwSize.Y = consoleRows + 2;
	info.srWindow.Top = 0;
	info.srWindow.Bottom = consoleRows + 1;
	info.srWindow.Left = 0;
	//info.srWindow.Right = 20;

	SetConsoleScreenBufferInfoEx(consoleHandle, &info);

	Clear();

	printHighScores();

	printMenuItems();

	// since the loop runs too fast
	// we only handle input when it is detected multiple times
	int holder = 0;

	while (true) // Menu Loop
	{
		char c = getKey();

		if (onKey('s', c) || onKey(KEY_DOWN, c))
		{
			holder++;
			if (holder > 1)
			{
				currentMenuItem++;
				if (currentMenuItem >= menuItemsLength) currentMenuItem = 0;

				printMenuItems();

				holder = 0;
			}
		}
		else if (onKey('w', c) || onKey(KEY_UP, c))
		{
			holder++;
			if (holder > 1)
			{
				currentMenuItem--;
				if (currentMenuItem < 0) currentMenuItem = menuItemsLength - 1;
				printMenuItems();
				holder = 0;
			}
		}
		else if (onKey('\r', c)) // on Enter press
		{
			if (currentMenuItem == 0)
			{
				if (saveFileExists)
				{
					TransitionLeft(COLORS.Purple, COLORS.Blue);
					break;
				}
				else
				{
					int a = consoleCols / 4 - strlen("BREAKOUT") / 2 - 1;
					gotoxy(a, 3);
					cout << "\033[27;37;48;2;231;76;60m" << " " << "NO  SAVE" << " " << "\033[30;47;29m";
				}
			}
			else if (currentMenuItem == 1)
			{
				TransitionRight(COLORS.Purple, COLORS.Green);
				break;
			}
			else if (currentMenuItem == 2) exit(0);
		}

		delay(10);
	}


#pragma endregion

	PlaySound(NULL, 0, 0); // stop the bg sound

	system("color 07");
	Clear();
	UpdateFontSizePx(TOP_ROW_HEIGHT - 2);

	drawRectangle(0, 0, gameWidth, gameHeight, COLORS.Back);
	drawRectangle(0, 0, gameWidth, TOP_ROW_HEIGHT, COLORS.Front);

	if (currentMenuItem == 0)
	{
		LoadGameState();
	}
	else
	{
		setInitPos();
		DrawLives();

		// Bricks Size Set up
		int brickWidth = gameWidth / BRICKS_COL_COUNT;
		int brickHeight = (gameHeight - TOP_ROW_HEIGHT) / 2 / BRICKS_ROW_COUNT;
		float extraSpace = (((float)gameWidth / (float)BRICKS_COL_COUNT) - brickWidth) * BRICKS_COL_COUNT;

		// Setting up intial bricks coordinates
		for (int r = 0; r < BRICKS_ROW_COUNT; r++)
		{
			for (int c = 0; c < BRICKS_COL_COUNT; c++)
			{
				Brick brick;

				brick.width = brickWidth;
				brick.height = brickHeight;

				brick.x = c * brick.width + extraSpace / 2;
				brick.y = r * brick.height + TOP_ROW_HEIGHT;


				// making sure first col is fixed with left side of screen
				if (c == 0)
				{
					brick.width += extraSpace;
					brick.x = 0;
				}

				// making last col fixed with right side of screen
				if (c == BRICKS_COL_COUNT - 1)
				{
					brick.width += extraSpace;
				}

				brick.health = (rand() % 4);

				bricks[r][c] = brick;
			}
		}

		DrawBricks();
	}



	// Stats set up
	time_t startTime = time(NULL);
	int framecount = 0;
	time_t t = time(NULL);

	// Game Loop
	while (!GameManager.over)
	{
		char c = getKey();

		// pause the game if window focus changes
		if (c == WINDOW_FOCUS_CHANGED)
		{
			GameManager.paused = true;

			delay(500);
			RedrawGame();

			gotoxy(consoleCols / 2 - strlen("SAVE   RESUME") / 2, 0);
			cout << "\033[7mS\033[27mAVE   \033[7mR\033[27mESUME\033[27m";
		}
		else if (onKey('p', c))
		{
			GameManager.paused = true;

			gotoxy(consoleCols / 2 - strlen("SAVE   RESUME") / 2, 0);
			cout << "\033[7mS\033[27mAVE   \033[7mR\033[27mESUME\033[27m";
		}
		else if (onKey('r', c))
		{
			GameManager.paused = false;

			gotoxy(consoleCols / 2 - strlen("SAVE   PAUSE ") / 2, 0);
			cout << "\033[7mS\033[27mAVE   \033[7mP\033[27mAUSE \033[27m";
		}

		if (!GameManager.paused) // Draw only if game is not paused
		{
			DrawBall();

			DrawPlayer();

			DrawPowerUp();

			DrawProjectile();

			DrawScore();

			if (!GameManager.started)
			{
				gotoxy(consoleCols / 2 - strlen("PRESS SPACE TO START") / 2, 0);
				cout << "PRESS SPACE TO START";
			}
			
			// dec lives if ball leaves the screen
			if (ball.y > gameHeight)
			{
				player.lives--;

				DrawLives();
				setInitPos();

				if (player.lives <= 0) GameManager.over = true;
			}


			if (onKey(' ', c) && !GameManager.started)
			{
				ball.force_x = BALL_FORCE * cos((rand() % (180 - 40) + 20) * 3.14 / 180);
				ball.force_y = -BALL_FORCE * sin((rand() % (180 - 40) + 20) * 3.14 / 180);

				gotoxy(consoleCols / 2 - strlen("PRESS SPACE TO START") / 2, 0);
				cout << repeatStr(" ", strlen("PRESS SPACE TO START") + 2);
				DrawScore(true);
				GameManager.started = true;
			}
			else if (onKey('d', c) || onKey(KEY_RIGHT, c)) player.force_x = PLAYER_SPEED;
			else if (onKey('a', c) || onKey(KEY_LEFT, c)) player.force_x = -PLAYER_SPEED;

			if (testing) // ball movement
			{
				if (c == 'j')
					ball.force_x = -5;
				else if (c == 'l')
					ball.force_x = 5;
				else if (c == 'i')
					ball.force_y = -5;
				else if (c == 'k')
					ball.force_y = 5;
			}
		}

		if (onKey('s', c)) SaveGameState();
		
		if (onKey('o', c)) GameManager.showStats = true;

		if (testing)
		{
			if (c == 'f') setFireball(true);
			else if (c == 'g') setFireball(false);
			else if (c == 'y') RedrawGame();
			else if (c == 't')
			{
				projectile.x = player.x + player.width / 2;
				projectile.y = player.y - projectile.diameter;

				projectile.active = true;
			}
			else if (c == 'c') cls();
		}

		delay(1000 / 120);

#pragma region Statistics
		framecount++;
		if (time(NULL) > t)
		{
			if (GameManager.showStats)
			{
				/*gotoxy(0, 0);
				cout << "TIM: " << time(NULL) - startTime;*/

			gotoxy(0, 0);
				cout << repeatStr(" ", to_string(GameManager.score ).length() + 3) << "FPS: " << framecount;
				/*
				gotoxy(0, 2);
				cout << "FOR: " << ((player.force_x < 0) ? "-" : "+") << abs(player.force_x);

				gotoxy(0, 3);
				cout << "BFX: " << ((ball.force_x < 0) ? "-" : "+") << abs(ball.force_x);

				gotoxy(0, 4);
				cout << "BFY: " << ((ball.force_y < 0) ? "-" : "+") << abs(ball.force_y);

				gotoxy(0, 5);
				cout << "LFT: " << GameManager.BricksLeft;*/


				/*gotoxy(0, 3);
				cout << "SCO: " << GameManager.score;

				gotoxy(0, 4);
				cout << "LIV: " << player.lives;*/
			}

			framecount = 0;
			t = time(NULL);
		}

#pragma endregion
	}

	PlaySound(TEXT("bgsound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);

	system("color 70");
	Clear();
	UpdateFontSize(8);
	getConsoleWindowDimensions(consoleCols, consoleRows);

	// Checking wheather player won or lost
	if (player.lives > 0) // player won
	{
		TransitionDown(COLORS.Red, COLORS.Green);

		drawRectangle(0, 0, gameWidth, gameHeight, COLORS.Green);

		system("color 27");

		PrintCenter(3, "\033[7m", " YOU WON!! ", "\033[27m");
	}
	else // player lost
	{
		TransitionDown(COLORS.Green, COLORS.Red);

		drawRectangle(0, 0, gameWidth, gameHeight, COLORS.Red);

		system("color 47");

		PrintCenter(3, "\033[31;47m", " YOU LOST! ", "");
	}

	string scoreString = " SCORE " + to_string(GameManager.score) + " ";

	if (scoreString.length() % 2 == 0) scoreString = " SCORE  " + to_string(GameManager.score) + " ";

	PrintCenter(5, "\033[30;47;29;7m", scoreString, "\033[27m");

	// Updating Highscores file if the score is in top 5
	if (AddScore(GameManager.score))
	{
		SaveHighScores();

		PrintCenter(7, "\033[30;47;29;7m", " NEW TOP 5 ", "\033[27m");
	}

	while (true);

	cls();
	showConsoleCursor(true);

	gotoxy(0, 0);

	return 0;
}
