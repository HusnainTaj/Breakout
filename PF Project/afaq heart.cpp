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
