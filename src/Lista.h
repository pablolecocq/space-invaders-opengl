#ifndef LISTA_H
#define LISTA_H

#include "nodo.h"
#include "Ship.h"
#include "Shape.h"



class Lista {
private:pnodo inicio;
	   Ship* theShip;
	   
	   int n;
	   void destruirLista();

public:
	Lista();
	~Lista();

	void move();
	void draw();
	Ship* getShip();
	void add(Shape* objeto);
	void remove(Shape* objeto);
	pnodo get_head();

};


#endif

