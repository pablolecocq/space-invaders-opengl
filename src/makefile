 
LDFLAGS= -L/usr/local/lib    -lm   -framework GLUT -framework OpenGL -framework Cocoa 

LinuxLFLAGS= -lGL -lGLU -lglut -lm


#
# How to make .c into .o
#
.cpp.o: commonstuff.h
	g++   -c $< -w


all:	Shape.o  Bullet.o Invaders.o Alien.o Ship.o mainSI.o Lista.o commonstuff.h  ObjectsList.o nodo.h GLstuff.o
	g++ Shape.o   Bullet.o Invaders.o Alien.o Ship.o mainSI.o ObjectsList.o Lista.o GLstuff.o $(LDFLAGS)  -o SpaceInvadersGL -w


Linux:	Shape.o  Bullet.o Invaders.o Alien.o Ship.o mainSI.o Lista.o commonstuff.h  ObjectsList.o nodo.h 
	g++ Shape.o   Bullet.o Invaders.o Alien.o Ship.o mainSI.o ObjectsList.o Lista.o  $(LinuxLFLAGS)  -o SpaceInvadersGL -w

clean:
	rm -f *~
	rm -f *.o
