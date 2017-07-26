#pragma once

#include "glut.h"

#define H 800
#define W 800

class GlManager
{
public:
	GlManager(int argc, char** argv);
	~GlManager();
	void BeginDraw();

private:
	inline void GLInit();
	inline void GLInitWindow();
	static void Display();

	friend void display();
};