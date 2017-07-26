#include "windows.h"
#include <cmath>
#include "glew.h"
#include "glut.h"
#include "common.h"

inline void initModel(const GLdouble centerHeight, const GLdouble edgeHeight, ObjectModel& model)
{
	Segment topSeg;
	//Component topCenter{{0.5f, 0.5f}, {0, centerHeight, 0}};
	Component topCenter{{0.0f, 0.0f}, {0, centerHeight, 0}};
	topSeg.push_back(topCenter);
	for(GLdouble i = 2 * PI; i >= 0; i -= resolution){
		Component edge{{0.5f * std::cos(i) + 0.5f, 0.5f * std::sin(i) + 0.5f}, {radius * std::cos(i), edgeHeight, radius * std::sin(i)}};
		//Component edge{{1.0f*std::cos(i), 1.0f*std::sin(i)}, {radius * std::cos(i), edgeHeight, radius * std::sin(i)}};
		topSeg.push_back(edge);
	}
	Component topEdgeZero{{1.0f, 1.0f}, {radius, edgeHeight, 0}};
	topSeg.push_back(topEdgeZero);
	model.push_back(topSeg);

	Segment midSeg;
	for(GLdouble i = 0; i <= 2 * PI; i += resolution){
		//const GLfloat tc = (i / static_cast<GLfloat>(2 * PI));
		const GLfloat tc = (i / static_cast<GLfloat>(2 * PI));
		//Component top{{tc, 0.0f}, {radius * std::cos(i), 0, radius * std::sin(i)}};
		Component top{{tc, 0.0f}, {radius * std::cos(i), 0, radius * std::sin(i)}};
		midSeg.push_back(top);
		//Component bottom{{tc, 1.0f}, {radius * std::cos(i), edgeHeight, radius * std::sin(i)}};
		Component bottom{{tc, 1.0f}, {radius * std::cos(i), edgeHeight, radius * std::sin(i)}};
		midSeg.push_back(bottom);
	}
	Component midBottomZero{{0.0f, 1.0f}, {radius, 0, 0}};
	midSeg.push_back(midBottomZero);
	Component midTopZero{{0.0f, 0.0f}, {radius, edgeHeight, 0}};
	midSeg.push_back(midTopZero);
	model.push_back(midSeg);

	Segment bottomSeg;
	Component bottomCenter{{0.5f, 0.5f}, {0, 0, 0}};
	for(GLdouble i = 0; i <= 2 * PI; i += resolution){
		Component edge{{0.5f * std::cos(i) + 0.5f, 0.5f * std::sin(i) + 0.5f}, {radius * std::cos(i), 0, radius * std::sin(i)}};
		bottomSeg.push_back(edge);
	}
	Component bottomEdgeZero{{0.5f, 0.5f}, {radius, 0, 0}};
	bottomSeg.push_back(bottomEdgeZero);
	model.push_back(bottomSeg);
}

void morphModel(ObjectModel& model)
{
	switch(morpherState){
	case State::CylinderToCone:{
		int morphedBlocksCount = 0;
		for(std::size_t i = 0; i < blocksToMorph; ++i){
			std::size_t morphedVertex = 0;
			std::size_t blocksize = model.at(i).size();
			for(std::size_t j = 0; j < blocksize; ++j){
				if(model.at(i).at(j).second.y > cone.at(i).at(j).second.y){
					model.at(i).at(j).second.y -= morphingStep;
				}
				else ++morphedVertex;
			}
			if(morphedVertex == blocksize) ++morphedBlocksCount;
		}
		if(morphedBlocksCount == blocksToMorph){
			morpherState = State::ConeToCylinder;
		}
	}
	break;
	case State::ConeToCylinder:{
		GLint morphedBlocksCount = 0;
		for(std::size_t i = 0; i < blocksToMorph; ++i){
			std::size_t morphedVertex = 0;
			std::size_t blocksize = model.at(i).size();
			for(std::size_t j = 0; j < blocksize; ++j){
				if(model.at(i).at(j).second.y < cylinder.at(i).at(j).second.y){
					model.at(i).at(j).second.y += morphingStep;
				}
				else ++morphedVertex;
			}
			if(morphedVertex == blocksize) ++morphedBlocksCount;
		}
		if(morphedBlocksCount == blocksToMorph){
			morpherState = State::CylinderToCone;
		}
	}
	break;
	}
}

void drawObject(const ObjectModel& model)
{
	Segment::iterator it;
	glPushMatrix();
	glTranslatef(0, -0.5, 0);

	Segment topSeg = model.at(0);
	it = topSeg.begin();
	glBegin(GL_TRIANGLE_FAN);
		for(auto end = topSeg.end(); it != end; ++it){
			Component top = *it;
			glTexCoord2f(top.first.u, top.first.v);
			glVertex3f(top.second.x, top.second.y, top.second.z);
		}
	glEnd();

	Segment midSeg = model.at(1);
	it = midSeg.begin();
	glBegin(GL_QUAD_STRIP);
		for(auto end = midSeg.end(); it != end; ++it){
			Component middle = *it;
			glTexCoord2f(middle.first.u, middle.first.v);
			glVertex3f(middle.second.x, middle.second.y, middle.second.z);
		}
	glEnd();

	Segment bottomSeg = model.back();
	it = bottomSeg.begin();
	glBegin(GL_TRIANGLE_FAN);
		for(auto end = bottomSeg.end(); it != end; ++it){
			Component bottom = *it;
			glTexCoord2f(bottom.first.u, bottom.first.v);
			glVertex3f(bottom.second.x, bottom.second.y, bottom.second.z);
			
		}
	glEnd();

	glPopMatrix();
}

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "glut.h"

#define ALPHA_VALUE 255

GLuint LoadTexture( const char * filename )
{

  GLuint texture;

  int width, height;

  unsigned char * data;

  FILE * file;

  file = fopen( filename, "rb" );

  if ( file == NULL ) return 0;
  width = 1024;
  height = 512;
  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );

 for(int i = 0; i < width * height ; ++i)
{
   int index = i*3;
   unsigned char B,R;
   B = data[index];
   R = data[index+2];

   data[index] = R;
   data[index+2] = B;

}


glGenTextures( 1, &texture );
glBindTexture( GL_TEXTURE_2D, texture );
glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
free( data );

return texture;
}

void textureInit()
{
	/*glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.data());*/

	//texture = LoadTexture("lenna.bmp");
	textureID = LoadTexture("lenna.bmp");
}

void modelInit()
{
	initModel(modelHeight, modelHeight, cylinder);
	initModel(modelHeight, 0, cone);
	initModel(modelHeight, modelHeight, morpher);
}

void timer(int value)
{
	rotationAngle += 2.0f;
	morphModel(morpher);
	glutPostRedisplay();
	glutTimerFunc(16, timer, 0);
}

void display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -5.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glRotatef(rotationAngle, 0.2f, 0.3f, 0.1f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	drawObject(cylinder);

	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(W, H);
	glutCreateWindow("Glab2 Esterlein V63504/1");
	textureInit();
	modelInit();
	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}