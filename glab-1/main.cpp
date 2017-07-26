#include <algorithm>
#include "glut.h"

#define H 800
#define W 800

int displayPhase = 0;

void initGL()
{
	glShadeModel(GL_FLAT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	gluOrtho2D(0.0, 800.0, 0.0, 800.0);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(170.0, static_cast<GLdouble>(w) / static_cast<GLdouble>(h), 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key){
	case 27:
		exit(0);
	case ' ':
		++displayPhase;
		glutPostRedisplay();
		break;
	}
}

void arrow_keys(int a_keys, int x, int y)
{
	switch(a_keys){
	case GLUT_KEY_UP:
		glutFullScreen();
		break;
	case GLUT_KEY_DOWN:
		glutReshapeWindow(H, W);
		break;
	}
}

void setPixel(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void drawBresLine(GLint x1, GLint y1, GLint x2, GLint y2)
{
	const int deltaX = std::abs(x2 - x1);
    const int deltaY = std::abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;

    setPixel(x2, y2);
    
	while(x1 != x2 || y1 != y2){

        setPixel(x1, y1);

        const int error2 = error * 2;
        if(error2 > -deltaY){
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX){
            error += deltaX;
            y1 += signY;
        }
    }
}

void initLine()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	GLint x1 = 100, y1 = 200, x2 = 700, y2 = 600;
	drawBresLine(x1, y1, x2, y2);
	glutSwapBuffers();
}

void drawGrid()
{
	glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2d(-100.0, 0.0);
		glVertex2d(100.0, 0.0);
		glVertex2d(0.0, -100.0);
		glVertex2d(0.0, 100.0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
}

void drawShapes()
{
	if(displayPhase == 0){
		glBegin(GL_TRIANGLES);
			glColor3f(0.5f, 0.0f, 0.8f);
			glVertex2d(20.0f, 50.0f);
			glVertex2d(50.0f, 50.0f);
			glVertex2d(50.0f, 100.0f);
		glEnd();		
	}
	glPopMatrix();
	glPushMatrix();
	
	if(displayPhase == 1){
		glTranslatef(20.0f, 50.0f, 0.0f);
		glRotated(90.0, 0.0, 0.0, 1.0);
		glBegin(GL_TRIANGLES);
			glColor3f(0.5f, 0.0f, 0.8f);
			glVertex2d(0.0f, 0.0f);
			glVertex2d(30.0f, 0.0f);
			glVertex2d(30.0f, 50.0f);
		glEnd();
	}
	glPopMatrix();
	glPushMatrix();

	if(displayPhase == 2){
		glTranslatef(20.0f, 50.0f, 0.0f);
		glRotated(90.0, 0.0, 0.0, 1.0);
		glBegin(GL_TRIANGLES);
			glColor3f(0.5f, 0.0f, 0.8f);
			glVertex2d(-10.0f, 50.0f);
			glVertex2d(20.0f, 50.0f);
			glVertex2d(20.0f, 100.0f);
		glEnd();
	}
	glPopMatrix();
	glPushMatrix();

	if(displayPhase == 3){
		glTranslatef(20.0f, 50.0f, 0.0f);
		glRotated(90.0, 0.0, 0.0, 1.0);
		glBegin(GL_TRIANGLES);
			glColor3f(0.5f, 0.0f, 0.8f);
			glVertex2d(-10.0f, 50.0f);
			glVertex2d(20.0f, 50.0f);
			glVertex2d(20.0f, 100.0f);
		glEnd();
		glTranslatef(9.15f, 60.85f, 0.0f);

		GLfloat theta;
		GLfloat pi = std::acos(-1.0);
		GLfloat radius = 10.85f;
		GLfloat step = 1.0f;

		glBegin(GL_TRIANGLE_FAN);
		for(GLfloat a = 0.0f; a < 360.0f; a += step){
			theta = 2.0f * pi * a / 180.0f;
			glColor3f(0.0f, 0.0f, 0.8f);
			glVertex3f(radius * std::cos(theta), radius * std::sin(theta), 0.0f);
		}
		glEnd();
	}

	if(displayPhase == 4){
		displayPhase = 0;
		glutPostRedisplay();
	}
}

void initShapes()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -10.0f);
	glPushMatrix();
	drawGrid();
	drawShapes();
	glutSwapBuffers();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(H, W);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Glab1 Esterlein V63504/1");
	initGL();
	//glutDisplayFunc(initLine);
	glutDisplayFunc(initShapes);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);
	glutMainLoop();
}