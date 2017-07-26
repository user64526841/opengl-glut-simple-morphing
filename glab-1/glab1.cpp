#include <algorithm>
#include "math.h"
#include "glut.h"
#include "glab1.h"

int Glab1::x1, Glab1::y1, Glab1::x2, Glab1::y2;

Glab1::Glab1()
{}

Glab1::~Glab1()
{}

void Glab1::InitLine(int a_x1, int a_y1, int a_x2, int a_y2)
{
	x1 = a_x1, x1 = a_y1, x1 = a_x2, x1 = a_y2;
}

void Glab1::DrawLine()
{
	int xx1 = x1, yy1 = y1, xx2 = x2, yy2 = y2;
	double tng0 = 0, error = 0, x_old = 0, y_old = 0;
	double error_array[2000];
	int dx = (x2 - x1 >= 0 ? 1 : -1);
	int dy = (y2 - y1 >= 0 ? 1 : -1);
	int lengthX = abs(x2 - x1);
	int lengthY = abs(y2 - y1);
	int llengthX = lengthX;
	int llengthY = lengthY;
	int llength = std::max(lengthX, lengthY);
	int length = llength + 1;

	if(lengthY <= lengthX){
		int x = x1, y = y1, d = -lengthX;
		if(y1 != y2){
			tng0 = static_cast<double>(y2 - y1)/static_cast<double>(x2 - x1);
		}
		int i = 0;
		while(length--){

			glBegin(GL_POINTS);
			glVertex2d(x, y);
			glEnd();

			if(x != x1){
				y_old = (x - x1) * tng0;
				if(y1 == y2){
					error_array[i] = abs(y_old - (y - y1));
				}
				else{
					error_array[i] = y_old - (y - y1);
				}
			}
			else{
				error_array[i] = 0;
			}
			x += dx;
			d += 2 * lengthY;
			if(d > 0){
				d -= 2 * lengthX;
				y += dy;
			}
			++i;
		}
	}
	else{
		int x = x1, y = y1, d = -lengthY;
		if(x1 != x2){
			tng0 = static_cast<double>(x2 - x1)/static_cast<double>(y2 - y1);
		}
		int i = 0;
		while(length--){

			glBegin(GL_POINTS);
			glVertex2d(x, y);
			glEnd();

			if(y != y1){
				x_old = (y - y1) * tng0;
				if(x == x1){
					error_array[i] = abs(x_old - (x - x1));
				}
				else{
					error_array[i] = x_old - (x - x1);;
				}
			}
			else{
				error_array[i] = 0;
			}
			y += dy;
			d += 2 * lengthX;
			if(d > 0){
				d -= 2 * lengthY;
				x += dx;
			}
			i++;
		}
	}
}