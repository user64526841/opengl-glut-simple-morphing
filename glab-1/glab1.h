#pragma once

#include "glmanager.h"

#define roundf(x) floor(x + 0.5f)

class Glab1
{
	friend class GlManager;

public:
	Glab1();
	~Glab1();

private:
	static int x1, y1, x2, y2;
	static void DrawLine();

public:
	static void InitLine(int a_x1, int a_y1, int a_x2, int a_y2);
};