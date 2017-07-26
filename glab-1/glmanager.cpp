#include "glmanager.h"
#include "glab1.h"

GlManager::GlManager(int argc, char** argv)
{
	glutInit(&argc, argv);
	GLInit();
	GLInitWindow();
}

GlManager::~GlManager()
{}

inline void GlManager::GLInit()
{
	glShadeModel(GL_FLAT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
    glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

inline void GlManager::GLInitWindow()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(H, W);
	glutCreateWindow("Glab 1");
	glutDisplayFunc(display);
}

void GlManager::Display()
{
	Glab1::DrawLine();
}

void GlManager::BeginDraw()
{
	glutMainLoop();
}

void display()
{
	GlManager::Display;
}