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
