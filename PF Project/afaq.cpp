////-------------------------------------------------------------------------------------------
////-------------------------------------------------------------------- Afaq's HEART ---------
////-------------------------------------------------------------------------------------------


//#include <iostream>
//#include "yourgraphics.h"
//using namespace std;
//
//
//void drawheart(int x1, int y1, int scale) {  // x1 and y1 coordinate of leftmost corner and it takes scale 
//												// scale determines size of heart
//	if (scale % 2 != 0) {						// see where function is called down.
//		scale = scale / 2 * 2;
//	}
//	drawLine(x1, y1, x1+(scale/2), y1+(scale/2), 0, 0, 0);
//	drawLine(x1+scale, y1, x1+(scale/2), y1 + (scale / 2), 0, 0, 0);
//	drawLine(x1 , y1, x1+scale/4.0, y1-scale/4.0, 0, 0, 0);
//	drawLine(x1 + scale / 4.0, y1 - scale / 4.0,x1+(scale/2),y1, 0, 0, 0);
//	drawLine(x1 +scale, y1 , (x1 + scale)-scale/4.0, y1 - scale / 4.0, 0, 0, 0);
//	drawLine((x1 + scale) - scale / 4.0, y1 - scale / 4.0, x1 + (scale/2), y1, 0, 0, 0);
//
//	for (int i = 1; i <= scale; i++) {
//		drawLine(x1+i, y1, x1 + (scale / 2), y1 + (scale / 2), 0, 0, 0);
//	}
//	int max = y1 - scale / 4.0;
//	for (int i = 1; max<=y1; i++,max++) {
//		drawLine(x1, y1, x1 + scale / 4.0, (y1 - scale / 4.0)+i, 0, 0, 0);
//		drawLine(x1 + scale, y1, (x1 + scale) - scale / 4.0, (y1 - scale / 4.0) + i, 0, 0, 0);
//		drawLine(x1 + scale / 4.0,( y1 - scale / 4.0)+i, x1 + (scale / 2), y1, 0, 0, 0);
//		drawLine((x1 + scale) - scale / 4.0, (y1 - scale / 4.0) + i, x1 + (scale / 2), y1, 0, 0, 0);
//		
//	}
//
//}
//
//int main() {
//	int x, y;
//	getWindowDimensions(x, y);
//	showConsoleCursor(false);
//	
//	cls();
//	
//	drawRectangle(0, 0, x, y, 255, 255, 255, 255, 255, 255);
//	
//	drawheart(200, 200, 50);// x1 is 200 ,y1 is 200 coordinates and the scale is set to 400
//	// try 100 200 400  values in the third position which gives determines scale of heart
//	
//	while (true);
//
//	// igonore the things below
//
//
//	//drawLine(200, 200, 400, 400,0,0,0);
//	//drawLine(600, 200, 400, 400, 0, 0, 0);
//
//	//drawLine(200, 200, 300, 100, 0, 0, 0);// line up from left
//	//
//	//
//	//drawLine(300, 100, 400, 200, 0, 0, 0); // line down from left
//	//drawLine(600, 200, 500, 100, 0, 0, 0);
//	//drawLine(500, 100, 400, 200, 0, 0, 0);
//
//	//for (int i = 1; i <= 400; i++) {
//	//	drawLine(200+i, 200, 400, 400, 0, 0, 0);
//	//}
//	//for (int i = 1; i <= 100; i++) {
//	//	drawLine(200, 200, 300, 100+i, 0, 0, 0);
//	//	drawLine(600, 200, 500, 100+i, 0, 0, 0);
//	//	drawLine(300, 100+i, 400, 200, 0, 0, 0);
//	//	drawLine(500, 100+i, 400, 200, 0, 0, 0);
//	//}
//}


////-------------------------------------------------------------------------------------------
////-------------------------------------------------------------------------------------------
////-------------------------------------------------------------------------------------------

//#include <iostream>
//#include "mygraphics.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <conio.h>
//#include <dos.h>
//
//using namespace std;
//const int width = 375, height = 425;
//int w, h;
//struct cordofball {
//	int x=0;
//	int y=0;
//	int downright = 1;
//	int downleft = 0;
//	int upright = 0;
//	int upleft = 0;
//};
//cordofball ballposition;
//
//void collisiondetection() {
//	if (ballposition.x + 450 < 0)
//		if (ballposition.downleft)
//			swap(ballposition.downleft, ballposition.downright);
//		else
//			swap(ballposition.upleft, ballposition.upright);
//	else if (ballposition.y + 300 < 0)
//		if (ballposition.upleft)
//			swap(ballposition.upleft, ballposition.downleft);
//		else
//			swap(ballposition.upright, ballposition.downright);
//	else if (ballposition.x + 475 > w)
//		if (ballposition.downright)
//			swap(ballposition.downright, ballposition.downleft);
//		else
//			swap(ballposition.upright, ballposition.upleft);
//	else if (ballposition.y + 325 > h)
//		if (ballposition.downright)
//			swap(ballposition.downright, ballposition.upright);
//		else
//			swap(ballposition.downleft, ballposition.upleft);
//
//}
//
//void updateball() {
//	drawEllipse(ballposition.x+450,ballposition.y+ 300, ballposition.x+ 475, ballposition.y+325, 0, 0, 0, 255, 255, 255);
//	if (ballposition.downright) {
//		ballposition.x += 15;
//		ballposition.y += -15;
//	}
//	else if (ballposition.downleft) {
//		ballposition.x += -15;
//		ballposition.y += -15;
//	}
//	else if (ballposition.upright) {
//		ballposition.x += 15;
//		ballposition.y += 15;
//	}
//	else {
//		ballposition.x += -15;
//		ballposition.y += 15;
//	}
//}
//
//void moverectangle(int i,int j,int k) {
//	drawRectangle(j + i + width, height, j + i + width + 200, height + 25, 0, 0, 0,0,0,0);
//	drawRectangle(j + i + k + width, height, j + i + k + width + 200, height + 25, 0, 0, 0, 0, 0, 0);
//	cls();
//	drawRectangle(j + width, height, j + width + 200, height + 25, 0, 0, 0, 0, 0, 0);
//}
//
//
//
//void input(char c,int& i,int& j,int& k) {
//	if (c == 'd') {
//		j += 15;
//		i = -15;
//		k = 3;
//	}
//	if (c == 'a') {
//		j -= 15;
//		i = 15;
//		k = -3;
//	}
//}
//
//int main() {
//	int  j = 0,i=0,k=0;
//	char c;
//	
//	getWindowDimensions(w, h);
//	drawRectangle(0, 0, w, h, 0, 0, 0,255,0,0);
//	cls();
//	
//	showConsoleCursor(false);
//	while (true) {
//		
//		drawRectangle(j + width, height, j + width + 200, height + 25, 0, 0, 0, 0, 0, 0);
//		i = 0;
//		k = 0;
//		c = getKey();
//		input(c, i, j, k);
//		moverectangle(i, j, k);
//		
//		
//		
//		
//	}
//	
//	return 0;
//}