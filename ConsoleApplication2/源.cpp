#include<math.h>
#include<graphics.h>
#include <stdio.h>
#define YELLOW WHITE
//计算下一个基准圆的y坐标
double CalculateY(double a, double b) {
	double y;

	y= (a*a - 800 * a + 160000) / (4 * (b + 40 * pow(b,0.5) + 400));

	return y;
}
//计算下一个基准圆的x坐标
double CalculateX(double y) {
	double x;
	x = 400 - pow(1600 * y, 0.5);
	return x;
}
//联立上一个基准圆求解的圆的y坐标
double CalculateY1(double a, double b, double c ,double d) {
	double y;
	y = (a*a*b + b*c*c + a*a*d + c*c*d - 2 * a*a*pow(b*d, 0.5) - 2 * c*c*pow(b*d, 0.5) - 2 * a*b*c - 2 * a*c*d + 4 * a*c*pow(b*d, 0.5)) / (4 * (b*b - 2 * b*d + d*d));
	return y;
}
//联立上一个基准圆求解的圆的x坐标
double CalculateX1(double a, double b, double y) {
	double x;
	x =pow((y +b)*(y +b) - (y - b)*(y - b), 0.5)+a ;
	return x;
}
//联立上一个基准圆和中心大圆求解的圆的x坐标
double CalculateX2(double a, double b,double c, double d)
{
	double x;
	x = -(0.5*(160000.0*b - 160000.0*d - 1.0*b*c*c + a*a*d - 400.0*a*a + 400.0*c*c)) / (400.0*a - 400.0*b - 400.0*c + 400.0*d - 1.0*a*d + b*c);
	return x;
}
//联立上一个基准圆和中心大圆求解的圆的y坐标
double CalculateY2(double a, double b, double x) {
	double y;
	y = (0.25*(a*a*a*a - 4.0*a*a*a*x + 1600.0*a*a*b + 4.0*a*a*x*x + 1600.0*a*a*x - 960000.0*a*a - 3200.0*a*b*x - 3200.0*a*x*x + 1920000.0*a*x - 4.0*b*b*x*x + 3200.0*b*b*x - 640000.0*b*b + 3200.0*b*x*x - 1280000.0*b*x + 256000000.0*b - 256000000.0*x + 25600000000.0)) / ((a - 400.0)*(b - 400.0)*(a - 2.0*x + 400.0));
	return y;
}
//画正方形函数
void DrawSquare(int x0, int y0)
{

	for (; x0 <= 900; x0++)
	{
		putpixel(x0, y0, YELLOW);

	}
	for (; y0 <= 800; y0++)
	{
		putpixel(x0, y0, YELLOW);

	}
	for (; x0 >= 100; x0--)
	{
		putpixel(x0, y0, YELLOW);

	}
	for (; y0 >= 0; y0--)
	{
		putpixel(x0, y0, YELLOW);
	}
}
//画圆函数
int DrawCircle(int x0, int y0, int r)
{


	putpixel(x0, y0 + r, YELLOW);
	int d = 5 / 4 - r;
	int x = 0;
	int y = r;
	while (x <= y)
	{
		if (d >= 0)
		{
			x++;
			y--;
			d += 2 * (x - y) + 1;
		}
		else
		{
			x++;
			d += 2 * x + 1;
		}
		putpixel(x0 + x, y0 + y, YELLOW);
		putpixel(x0 + x, y0 - y, YELLOW); //(x,-y)
		putpixel(x0 - x, y0 + y, YELLOW); //(-x,y)
		putpixel(x0 - x, y0 - y, YELLOW); //(-x,-y)
		putpixel(x0 + y, y0 + x, YELLOW); //(y,x)
		putpixel(x0 + y, y0 - x, YELLOW); //(y,-x)
		putpixel(x0 - y, y0 + x, YELLOW); //(-y,x)
		putpixel(x0 - y, y0 - x, YELLOW); //(-y,-x)

	}

	return 0;
}
//基准圆及以此求解出的周围的三个圆的位置和半径
struct Circle {
	double x;
	double y;
	double r;
	double x1;
	double y1;
	double r1;
	double x2;
	double y2;
	double r2;
	double x3;
	double y3;
	double r3;
}; 
//计算产生的每一个圆的位置和半径
struct MaxCircle {
	double x;
	double y;
	double r;
};
//遍历数组找出最大圆
double Max(MaxCircle k[])
{
	int i = 0, t=0;
	double r = k[0].r;
	for (; i < 400; i++)
		if (k[i].r>r) { r = k[i].r; t = i; }
	return t;
}

int main() 
{
	int m;//要画的圆的数量 (等待用户输入)
	scanf_s("%d", &m);
	initgraph(1000, 800);
	DrawSquare(100, 0); 
	if (m >= 1) DrawCircle(500, 400, 400);
	if (m >= 2)DrawCircle(167, 67, 67);
	if (m >= 3)DrawCircle(167, 733, 67);
	if (m >= 4)DrawCircle(833, 733, 67);
	if (m >= 5)DrawCircle(833, 67, 67);

	int i;
	struct Circle circles[400];
	struct MaxCircle radius[400];
	if(m>5)
		for (i = 0; i <=((m-1 - 5) /8); i++)
		{
			if (i == 0)//首轮迭代初始数据
			{
				circles[0].x = 164;
				circles[0].y = 35;
				circles[0].r = 35;
				DrawCircle((int)circles[i].x + 100, (int)circles[i].y, (int)circles[i].r);
				if (m - 5 - 8 * i >= 2) DrawCircle((int)(800 - circles[i].x) + 100, (int)circles[i].y, (int)circles[i].r);
				if (m - 5 - 8 * i >= 3) DrawCircle((int)(800 - circles[i].x) + 100, (int)(800 - circles[i].y), (int)circles[i].r);
				if (m - 5 - 8 * i >= 4) DrawCircle((int)circles[i].x + 100, (int)(800 - circles[i].y), (int)circles[i].r);
				if (m - 5 - 8 * i >= 5) DrawCircle((int)circles[i].y + 100, (int)circles[i].x, (int)circles[i].r);
				if (m - 5 - 8 * i >= 6) DrawCircle((int)(800 - circles[i].y) + 100, (int)circles[i].x, (int)circles[i].r);
				if (m - 5 - 8 * i >= 7) DrawCircle((int)(800 - circles[i].y) + 100, (int)(800 - circles[i].x), (int)circles[i].r);
			    if (m - 5 - 8 * i >= 8) DrawCircle((int)circles[i].y + 100, (int)(800 - circles[i].x), (int)circles[i].r);
				radius[399].r = 11; radius[399].y = 11; radius[399].x = 11;
				radius[398].r = 35 * 11 / 65; radius[398].y = 35 * 11 / 65; radius[398].x = 164 * 11 / 65;
			}
			else
			{//上一轮求解的新圆作为这一轮的基准圆
				circles[i].x = circles[i - 1].x1;
				circles[i].y = circles[i - 1].y1;
				circles[i].r = circles[i - 1].r1;
				//遍历数组画出最大圆
				int t = Max(radius);
				DrawCircle((int)radius[t].x + 100, (int)radius[t].y, (int)radius[t].r);
				if (m - 5 - 8 * i >= 2) DrawCircle((int)(800 - radius[t].x) + 100, (int)radius[t].y, (int)radius[t].r);
				if (m - 5 - 8 * i >= 3) DrawCircle((int)(800 - radius[t].x) + 100, (int)(800 - radius[t].y), (int)radius[t].r);
				if (m - 5 - 8 * i >= 4) DrawCircle((int)radius[t].x + 100, (int)(800 - radius[t].y), (int)radius[t].r);
				if (m - 5 - 8 * i >= 5)	DrawCircle((int)radius[t].y + 100, (int)radius[t].x, (int)radius[t].r);
				if (m - 5 - 8 * i >= 6) DrawCircle((int)(800 - radius[t].y) + 100, (int)radius[t].x, (int)radius[t].r);
				if (m - 5 - 8 * i >= 7) DrawCircle((int)(800 - radius[t].y) + 100, (int)(800 - radius[t].x), (int)radius[t].r);
				if (m - 5 - 8 * i >= 8) DrawCircle((int)radius[t].y + 100, (int)(800 - radius[t].x), (int)radius[t].r);
				if ((radius[t].y == 11) || (radius[t].x == 11)) m = m + 4;
				radius[t].r = 0; radius[t].x = 0; radius[t].y = 0;
			}
			//迭代求解第一个新圆
			circles[i].y1 = CalculateY(circles[i].x, circles[i].y);
			circles[i].x1 = CalculateX(circles[i].y1);
			circles[i].r1 = circles[i].y1;
			//存储第一个新圆的位置和半径
			radius[3 * i].r = circles[i].r1; radius[397-3 * i].r = circles[i].r1 * 11 / 65;
			radius[3 * i].y = circles[i].y1; radius[397 - 3 * i].y = circles[i].y1 * 11 / 65;
			radius[3 * i].x = circles[i].x1; radius[397- 3 * i].x= circles[i].x1 * 11 / 65;

			if (i == 0)//首轮迭代初始数据
			{
				circles[i].y2 = CalculateY1(67, 67, circles[i].x, circles[i].y);
				circles[i].x2 = CalculateX1(67, 67, circles[i].y2);
				circles[i].r2 = circles[i].y2;
			}
			else//迭代求解第二个新圆
			{
				circles[i].y2 = CalculateY1(circles[i - 1].x, circles[i - 1].y, circles[i].x, circles[i].y);
				circles[i].x2 = CalculateX1(circles[i - 1].x, circles[i - 1].y, circles[i].y2);
				circles[i].r2 = circles[i].y2;
			}
			//存储第二个新圆的位置和半径
			radius[3 * i + 1].r = circles[i].r2; radius[397 - 3 * i-1].r = circles[i].r2 * 11 / 65;
			radius[3 * i + 1].x = circles[i].x2; radius[397 - 3 * i-1].x = circles[i].x2* 11 / 65;
			radius[3 * i + 1].y = circles[i].y2; radius[397 - 3 * i-1].y = circles[i].y2 * 11 / 65;


			if (i == 0)//首轮迭代初始数据
			{
				circles[i].x3 = CalculateX2(67, 67, circles[i].x, circles[i].y);
				circles[i].y3 = CalculateY2(67, 67, circles[i].x3);
				circles[i].r3 = pow((circles[i].x3 - 400)*(circles[i].x3 - 400) + (circles[i].y3 - 400)*(circles[i].y3 - 400), 0.5) - 400;
			}
			else//迭代求解第三个新圆
			{
				circles[i].x3 = CalculateX2(circles[i - 1].x, circles[i - 1].y, circles[i].x, circles[i].y);
				circles[i].y3 = CalculateY2(circles[i - 1].x, circles[i - 1].y, circles[i].x3);
				circles[i].r3 = pow((circles[i].x3 - 400)*(circles[i].x3 - 400) + (circles[i].y3 - 400)*(circles[i].y3 - 400), 0.5) - 400;
			}
			//存储第三个新圆的位置和半径
			radius[3 * i + 2].r = circles[i].r3; radius[397 - 3 * i-2].r = circles[i].r3 * 11 / 65;
			radius[3 * i + 2].x = circles[i].x3; radius[397- 3 * i - 2].x = circles[i].x3 * 11 / 65;
			radius[3 * i + 2].y = circles[i].y3; radius[397 - 3 * i - 2].y = circles[i].y3 * 11 / 65;
            Sleep(300);
		}
	getchar();
	getchar();
	getchar();
	return 0;
}
