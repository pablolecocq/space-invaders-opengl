
  // PONER AQUI VUESTRO CODIGO 
#include "ObjectsList.h"
#include "Lista.h"
#include "stdlib.h"
#include "stdio.h"
#include "nodo.h"
#include "Bullet.h"


ObjectsList::ObjectsList() {
	n = 0;
	theShip = new Ship();
	L.add(theShip);
	theOvni = new Ovni();
	L.add(theOvni);
	// Create aliens and add them to the list
	for (int i = 0; i < NUMALIENS; i++) {
		float x = static_cast<float>(i % NUMCOLS) ;
		float y = 10-static_cast<float>(i / NUMCOLS);
		int  type = 4-(i / NUMCOLS);
		Alien* alien = new Alien(type, x, y);
		L.add(alien);
	}

	
	
}


ObjectsList::~ObjectsList() {
	// La lista L es la propietaria de todos los objetos (nave, ovni y aliens)
	// y los libera en su propio destructor, por lo que aqui no hay que borrar
	// theShip de nuevo (provocaria un doble free).
}

void ObjectsList::move() {
	L.move();

}
void ObjectsList::draw() {
	L.draw();
  

}

void ObjectsList::add(Shape* obj) {
	L.add(obj);

}
void ObjectsList::remove(Shape* obj) {
	L.remove(obj);

}

Ship* ObjectsList::getShip() {
	return theShip;

}

// Comprueba las colisiones del mundo:
//   - retorna >=2  si el proyectil alcanza a un alien (el valor es el tipo del
//     alien, usado para puntuar); elimina el alien y el proyectil.
//   - retorna 1    si un alien alcanza a la nave.
//   - retorna 0    si no hay colision.
int ObjectsList::collisions(Bullet* theBullet, Ship* theShip) {

	pnodo p;

	// 1) Proyectil contra aliens
	if (theBullet != NULL) {
		p = L.get_head();
		while (p != NULL) {
			Alien* theAlien = dynamic_cast<Alien*>(p->theShape);
			if (theAlien) {
				float d = (*theAlien) + theBullet;           // distancia alien-bala
				if (d < theAlien->getSize() + theBullet->getSize() + 0.2f) {
					int type = theAlien->getType();
					L.remove(theAlien);                      // elimina y libera el alien
					L.remove(theBullet);                     // elimina y libera la bala
					return type;                             // >=2 -> puntuacion
				}
			}
			p = p->next;
		}
	}

	// 2) Aliens contra la nave
	if (theShip != NULL) {
		float sp[3], ap[3];
		theShip->getPos(sp);
		p = L.get_head();
		while (p != NULL) {
			Alien* theAlien = dynamic_cast<Alien*>(p->theShape);
			if (theAlien) {
				theAlien->getPos(ap);
				if (mydistance(ap[X], ap[Y], sp[X], sp[Y])
						< theAlien->getSize() + theShip->getSize() + 0.2f) {
					return 1;                                // nave alcanzada
				}
			}
			p = p->next;
		}
	}

	return 0;
}

