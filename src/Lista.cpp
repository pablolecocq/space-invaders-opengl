#include "Lista.h"
#include "stdlib.h"
#include "stdio.h"
#include "nodo.h"

/*Lista::Lista()
{
   
}*/
Lista::Lista() : inicio(nullptr), theShip(nullptr), n(0) {
    // Constructor 
}
Lista::~Lista()
{
    destruirLista();
}
void Lista::destruirLista() {
    pnodo actual = inicio;
    while (actual != nullptr) {
        pnodo siguiente = actual->next;
        delete actual->theShape;
        delete actual;
        actual = siguiente;
    }
    inicio = nullptr;
    n = 0;
}
void Lista::move() {
    // Move implementation
    pnodo actual = inicio;
    while (actual != nullptr) {
        actual->theShape->move();
        actual = actual->next;
    }

}
void Lista::draw() {
    pnodo actual = inicio;
    while (actual != nullptr) {
        actual->theShape->draw();
        actual = actual->next;
    }
}

void Lista::add(Shape* objeto) {
    pnodo nuevo = new nodo();
    nuevo->theShape = objeto;
    nuevo->next = nullptr;

    if (inicio == nullptr) {
        inicio = nuevo;
    }
    else {
        pnodo actual = inicio;
        while (actual->next != nullptr) {
            actual = actual->next;
        }
        actual->next = nuevo;
    }

    n++;
  

}


void Lista::remove(Shape* objeto) {
    if (inicio == nullptr) {
        return;
    }

    pnodo anterior = nullptr;
    pnodo actual = inicio;
    while (actual != nullptr) {
        if (actual->theShape == objeto) {
            if (anterior == nullptr) {
                inicio = actual->next;
            }
            else {
                anterior->next = actual->next;
            }
            delete actual->theShape;
            delete actual;
            n--;
            return;
        }
        anterior = actual;
        actual = actual->next;
    }
}

Ship* Lista::getShip() {
    return theShip;
}

pnodo Lista::get_head(){
    return inicio;

}
