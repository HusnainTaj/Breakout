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