
#include "Shape.h"
#include "commonstuff.h"
#include <windows.h>
#include "glut.h"

Shape::Shape()
{
  mynumber = RAND_DOM(0,1000000);
  // TBD: check mynumber is not repeated
}
Shape::~Shape()
{
}

void  Shape::getPos(float *p)
{
  p[X] = pos[X];
  p[Y] = pos[Y];
  p[Z] = pos[Z];
}


int Shape::getNo()
{
  return mynumber;
}

void Shape::predraw()
{
  glPushMatrix();
  glTranslatef(pos[X],pos[Y],pos[Z]);

  glRotatef(-90,1,0,0);
  //glRotatef(rot[Y],0,1,0);
  //glRotatef(rot[Z],0,0,1);
  
  glColor3f(color[R],color[G],color[B]);
}

void Shape::postdraw()
{
  glPopMatrix();
}

void Shape::move()
{
  pos[X] += tspeed[X];
  pos[Y] += tspeed[Y];
  pos[Z] += tspeed[Z];

  
  // check world boundaries
  if(pos[X]<=-SIZEX2) {pos[X] = -SIZEX2; tspeed[X] = -tspeed[X];}
  if(pos[Y]<=-SIZEY2) {pos[Y] = -SIZEY2; tspeed[Y] = 4*ALIEN_SPEED*(RAND_FRAC()+0.2);}// -tspeed[Y];}
  //if(pos[Z]<=-SIZEZ2) {pos[Z] = SIZEZ2; tspeed[Z] = -tspeed[Z];}
  
  if(pos[X]>=SIZEX2) {pos[X] = SIZEX2; tspeed[X] = -tspeed[X];}
  if(pos[Y]>=SIZEY2) {pos[Y] = SIZEY2; tspeed[Y] = -0.01*ALIEN_SPEED;}
  // if(pos[Z]>=SIZEZ2) {pos[Z] = -SIZEX2; tspeed[Z] = -tspeed[Z];}
  
}


void Shape::changedir()
{
  
}


int Shape::operator*(Shape*)
{
  return 1;
}
