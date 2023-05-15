#include <windows.h>
#include "commonstuff.h"
#include "Shape.h"
#include "Alien.h"
#include "Ship.h"
#include "Bullet.h"
#include "Lista.h"
#include "Invaders.h"
#include "Ovni.h"

#ifndef __OL_H__
#define __OL_H__


class ObjectsList {
private:
	int n;
	Ship* theShip;
	Ovni* theOvni;

protected:
	Lista L;

public:
	ObjectsList();
	~ObjectsList();
	void move();
	void draw();
	void add(Shape*);
	void remove(Shape*);
	Ship* getShip();
	int collisions(Bullet*, Ship*);

	friend class Invaders;  // !!! 
};

#endif

