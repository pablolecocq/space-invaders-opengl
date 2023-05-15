#include <windows.h>
#include "commonstuff.h"
#include "Shape.h"


#ifndef __Ovni_H__
#define __Ovni_H__

class Ovni : public Shape {
private:
	int status;
	float size;
public:
	Ovni();
	void draw();
	void strafe(float, float, float);
	
	float getSize();
	
};

#endif