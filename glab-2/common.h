#include <vector>

#define W 600
#define H 600

const double PI = 3.14159;

const int blocksToMorph = 2;
const GLdouble resolution  = 0.1;
const GLdouble modelHeight = 1;
const GLdouble radius = 0.5;
const GLdouble morphingStep = 0.005;
GLuint textureID;
GLfloat rotationAngle = 0;

typedef struct
{
	GLfloat u, v;
}
Texcoord;

typedef struct
{
	GLfloat x, y, z;
}
Vertex;

typedef std::pair<Texcoord, Vertex> Component;
typedef std::vector<Component> Segment;
typedef std::vector<Segment> ObjectModel;

ObjectModel cylinder, cone, morpher;

const std::vector<unsigned char> textureData
{
	128, 128, 128, 255,
	255, 0, 0, 255,
	0, 255, 0, 255,
	0, 0, 255, 255
};

enum State {CylinderToCone, ConeToCylinder};
State morpherState = State::CylinderToCone;