//
//// SKIP TO LINE 84 FOR OVERLAP LOGIC
//
//#include <iostream>
//#include "youregraphics.h"
//using namespace std;
//
//bool overlapping = false;
//
//// overriding default draw method to draw with y starting from bottom
//void drawRectangleR(int x1, int y1, int x2, int y2, int R, int G, int B, int FR, int FG, int FB)
//{
//	drawRectangle(x1, 500 - y2, x2, 500 - y1, R, G, B, FR, FG, FB);
//}
//
//class rect
//{
//	public:
//	int x1 = 0;
//	int y1 = 50;
//
//	int width = 50;
//	int height = 50;
//
//	int x2()
//	{
//		return x1 + width;
//	}
//
//	int y2()
//	{
//		return y1 - height;
//	}
//
//	void draw()
//	{
//		if(overlapping)
//			drawRectangleR(x1, y1, x2(), y2(), 255, 0, 0, 40, 40, 40);
//		else
//			drawRectangleR(x1, y1, x2(), y2(), 255, 255, 255, 40,40,40);
//	}
//};
//
//int main()
//{
//	cout << "Loading...";
//	MoveWindow(GetConsoleWindow(), 0, 0, 500, 500, NULL);
//	showConsoleCursor(false);
//	cls();
//
//	delay(500);
//	drawRectangle(0, 0, 500, 500, 255, 255, 255, 255, 255, 255);
//
//	rect r1;
//	rect r2;
//
//	r2.height = 100;
//	r2.width = 100;
//	r2.x1 = 200;
//	r2.y1 = 100;
//
//	// Game Loop
//	while (true)
//	{
//		delay(50);
//
//		drawRectangle(0, 0, 500, 500, 255, 255, 255, 255, 255, 255);
//		char c = getKey();
//		r2.draw();
//		r1.draw();
//
//		if (c == 'a') r1.x1 -= 30;
//		else if (c == 'd') r1.x1 += 30;
//		else if (c == 'w') r1.y1 += 30;
//		else if (c == 's') r1.y1 -= 30;
//
//		if (c == KEY_LEFT) r2.x1 -= 30;
//		else if (c == KEY_RIGHT) r2.x1 += 30;
//		else if (c == KEY_UP) r2.y1 += 30;
//		else if (c == KEY_DOWN) r2.y1 -= 30;
//
//		//
//		//
//		// ////////////////////////////////////////// OVERLAP LOGIC STARTS HERE
//		//
//
//		int x1 = r1.x1, x2 = r1.x2(), y1 = r1.y1, y2 = r1.y2();
//		int a1 = r2.x1, a2 = r2.x2(), b1 = r2.y1, b2 = r2.y2();
//
//		// minimum distance between the objects before they overlap
//		int minDistanceX = (x2 - x1) + (a2 - a1);
//		int minDistanceY = (y1 - y2) + (b1 - b2);
//
//		// current distance
//		int distanceXL = a2 - x1; // distance x if r1 is on left of r2
//		int distanceXR = x2 - a1; // distance x if r1 is on right of r2
//
//		int distanceYT = y1 - b2; // distance y if r1 is on top of r2
//		int distanceYB = b1 - y2; // distance y if r1 is on bottom of r2
//
//		if(
//			(
//				(x1 < a1 && distanceXL < minDistanceX) ||
//				(x1 > a1 && distanceXR < minDistanceX)
//			)
//			&&
//			(
//				(y1 > b1 && distanceYT < minDistanceY) ||
//				(y1 < b1 && distanceYB < minDistanceY)
//			)
//		)
//		{
//			overlapping = true;
//		}
//		else
//		{
//			overlapping = false;
//		}
//	}
//
//	return 0;
//}


// ////////////////////////////////////////////////////////////////////////////////// 
// ////////////////////////////////////////////////////////////////////////////////// Get IMages
// ////////////////////////////////////////////////////////////////////////////////// 

//
//#pragma region Get IMages
//
//struct rgb
//{
//	int r;
//	int g;
//	int b;
//};
//
//rgb arr[150][50];
//
//struct shape
//{
//	rgb color;
//	int x;
//	int y;
//	int width;
//	int height;
//};
//
//shape shapes[40];
//int shapesI = 0;
//
//bool isColorSame(rgb a, rgb b)
//{
//	return a.r == b.r && a.g == b.g && a.b == b.b;
//}
//
//void getFromImg()
//{
//	ifstream img("D:/heart.txt", ios::in | ios::binary);
//
//	int row = 0;
//	for (string line; getline(img, line);)
//	{
//		int valNumber = 0;
//		int col = 0;
//		while (true)
//		{
//			string token = line.substr(0, line.find(" ", 0));
//
//
//			int spaceIndex = line.find(" ", 0);
//			if (spaceIndex == -1) break;
//
//			if (valNumber == 0)
//				arr[row][col].r = stoi(token);
//			else if (valNumber == 1)
//				arr[row][col].g = stoi(token);
//			else if (valNumber == 2)
//			{
//				arr[row][col].b = stoi(token);
//				valNumber = -1;
//				col++;
//			}
//
//			valNumber++;
//
//			//cout << token << endl;
//
//			line = line.substr(spaceIndex + 1, line.length());
//		}
//
//		row++;
//	}
//
//	img.close();
//}
//
//void printFromImg(int x, int y)
//{
//	for (int r = 0; r < 50; r++)
//	{
//		for (int c = 0; c < 150; c++)
//		{
//			rgb co = arr[r][c];
//			drawRectangle(x + c, y + r, x + c + 1, y + r + 1, co.r, co.g, co.b);
//		}
//	}
//}
//
//void getShapes()
//{
//	for (int r = 0; r < 600; r++)
//	{
//		for (int c = 0; c < 1080; c++)
//		{
//			rgb co = arr[r][c];
//
//			shape a;
//
//			a.x = c;
//			a.y = r;
//
//			for (int c2 = c; c2 < 1080; c2++)
//			{
//				a.width = c2 - c;
//
//				if (!isColorSame(arr[r][c], arr[r][c2])) break;
//			}
//
//			for (int r2 = r; r2 < 600; r2++)
//			{
//				a.height = r2 - r;
//
//				if (!isColorSame(arr[r][c], arr[r2][c])) break;
//			}
//
//			shapes[shapesI++] = a;
//		}
//	}
//}
//
//
//#pragma endregion
