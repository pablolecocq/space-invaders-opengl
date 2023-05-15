#include "commonstuff.h"
#include "Ovni.h"
#include "Bullet.h"
#include <windows.h>
#include "glut.h"


Ovni::Ovni()
{
	size = 0.25;

	pos[X] = 0;
	pos[Y] = -2;
	pos[Z] = 0;

	tspeed[X] = 0;
	tspeed[Y] = 0;
	tspeed[Z] = 0;

	color[R] = 0.9;
	color[G] = 0.9;
	color[B] = 0.9;
}

void Ovni::strafe(float rx, float ry, float rz)
{
	pos[X] += rx;  pos[Y] += ry;  pos[Z] += rz;
}


void Ovni::draw()
{

	predraw();

	glutSolidSphere(size, 9, 8);

	postdraw();

}


float Ovni::getSize()
{
	return (0.25);
}

