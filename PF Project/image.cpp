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
