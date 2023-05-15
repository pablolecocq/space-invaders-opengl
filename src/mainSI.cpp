



//***********************
// Space Invaders Open GL
// Claudio Rossi, Universidad Politécnica de Madrid 
// (C) 2015-2023 
//***********************


#include "commonstuff.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <unistd.h>  // Esta solo sirve para linux Y osX !!!
#include <string.h>

#include "Shape.h"
#include "Ship.h"
#include "Bullet.h"
#include "Invaders.h"
#include "Alien.h"
#include "ObjectsList.h"
#include <windows.h>
#include "glut.h"



//***********************
// Prototipos de funciones 
//***********************

// Callback de la logica del juego
void myLogic();

//Callback de dibujo
void OnDibuja(void);	

//Callbacks para teclado y raton
void OnKeyboardDown(unsigned char key, int x, int y);
void OnMouseBtn(int button, int state,int x, int y);
void OnMouseMoveBtn(int x, int y);
void OnSpecKeyboardDown(int key, int x, int y);
GLuint LoadTexture( int width, int height, const char * filename );
void displaytext(GLuint Thetexture);
void init_GL_stuff();
void printdata();

  
//***********************
// Variables globales
//***********************

// Posición y step de la camara
float cam_pos[6]={0, 0, 27};


// Modo del Mouse
int MODE=NONE;

// Objetos globales
ObjectsList worldobjects;
Ship *theShip=NULL;
Bullet *theBullet=NULL;
Invaders *Team;

// Varias constantes usadas en el programa
int shotTime=0;
int nShip=3;
int score=0;
int gameover=0;
int timeout=0;

// Texture datas tructure
GLuint KLtexture;



//***********************
// Programa principal
//***********************


int main(int argc,char* argv[])
{

  // inicializaciones

  
  // Inicialización GLUT
  glutInit(&argc, argv);

  // Inicializaciones openGL (ver GLstuff.c)
  init_GL_stuff();
  

  // Define call backs te GLUT

  // Display function: contiene las instrucciones de dibujo
  glutDisplayFunc(OnDibuja);
    // Idle function: contiene la logica del juego
  glutIdleFunc(myLogic);
  
  // Callbacks de teclado y ratón
  glutKeyboardFunc(OnKeyboardDown);
  glutSpecialFunc(OnSpecKeyboardDown);
  glutMotionFunc(OnMouseMoveBtn);
  glutMouseFunc(OnMouseBtn);

  
  // Posicciona el punto de vista (cámara)
  gluLookAt(cam_pos[0],cam_pos[1],cam_pos[2],  // posicion del  ojo  
	    0.0, 0.0, 0.0,		        // hacia que punto mira  
	    0.0, 1.0, 0.0);         // vector "UP"  (vertical positivo)


  
  // Creacción de los objetos iniciales
  theShip  = worldobjects.getShip();
  Team = new Invaders(&worldobjects);

  // WORLDOBJECTS es una variable estática, se inicializa "automaticamente" - contiene los alienigenas  //***

  
  // Carga la imagen del fondo
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  KLtexture= LoadTexture(800,600, "SpaceInvaders.bmp" ); 
  glBindTexture (GL_TEXTURE_2D, KLtexture);

  
  // bucle infinito de Open GL
  glutMainLoop();

  // Esto solo sirve para que el compilador no proteste, nunca se llegará aquí
  return 0;   

}

/************************** FIN DEL MAIN ************************************/





//***********************
// Callbacks
//***********************


// Imprime puntuacción y num. de naves
void printdata()
{
  int i,l;
  char buffer[50];
  
  glPushMatrix();

  if(!gameover)
    {
      glColor3f(1.0f, 1.0f, 1.0f);
      glDisable(GL_LIGHTING);
      glRasterPos3f(-9, 9,0.1);
      sprintf(buffer,"Ships: %d       Score: %d",nShip,score);
    }
  else
    {
      glColor3f(1.0f, 0.0f, 0.0f);
      glDisable(GL_LIGHTING);
      glRasterPos3f(-2, 0,0.1);
      sprintf(buffer,"GAME OVER! Points: %d",score);
    }
  
  l=strlen(buffer); 
  
  for( i=0; i < l; i++) 
    {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]); // Print a character on the screen
    }
  
  glEnable(GL_LIGHTING);
  
  glPopMatrix();
  
}

 


// Logica del juego: mueve los objeto mandando el mensaje "move"
void myLogic()
{
  int res;

   
  if(gameover)
    if(timeout++>100)
      exit(1);
    else ;
  else
    {
      // borra el proyectil después de cierto tiempo si no ha dado con nada
      if(shotTime++>MAXSHOTTIME)
	{
	  worldobjects.remove(theBullet);    // si theBullet==NULL no pasa nada, la remove no lo encuentra y no hace nada
	  theBullet = NULL;
	  shotTime = 0;
	}
      
      // Pide al mudo que mueve los objetos
      worldobjects.move();
      
      // mueve los alienos
      Team->move();
      
      // Pide si ha habido colisión, pasa referencia a proyectil y nave, retorna tipo de colisión y posición de la colisión
      // res==0:  No ha colisicón
      // res==1:  Proyectil/Nave
      // res>=2:  Alien/Proyectil, depende del tipo de Alien
      res = worldobjects.collisions(theBullet,theShip);    
      
      
      if(res==1)    
	{
	  nShip--;
	  
	  if(nShip==0)
	    gameover=1;
	  
	  theShip->resetpos();
	}
      
      
      if(res>=2)    
	{
	  theBullet = NULL;
	  shotTime = 0;
	  score += 10*(res);
	}
      
      
      if(Team->get_lowest()<-7)
	{
	  gameover = 1;
	}
      
    }
  
}

/**************************************************************/ 

void OnDibuja(void)
{ 
  //Borrado de la pantalla	
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Dibuja la imagen del fondo
  displaytext(KLtexture);

  // imprime datos en la pantalla
  printdata();

  
  // Manda el mensaje "draw" al mundo
  worldobjects.draw();    

 
  //Al final, cambiar el buffer
  glutSwapBuffers();
  glutPostRedisplay();//se le indica que redibuje la pantalla
  /**************************************************************/
}





 

   


void OnKeyboardDown(unsigned char key, int x, int y)
{ 
  int mod;

  mod=glutGetModifiers();

  switch(key)
    {
    case 'q':
    case ESC:
      exit(1);
    case ' ':
      // Si no hay proyectil, lo crea  //***
      if(!theBullet)
	{
	  theBullet=theShip->fire(); 
	  worldobjects.add(theBullet);
	} 
      break;
    }		
}


void OnSpecKeyboardDown(int key, int x, int y)
{ 
  switch(key)
    {

    case GLUT_KEY_DOWN:
      break;
    case GLUT_KEY_UP:
      break;
    case GLUT_KEY_LEFT: theShip->strafe(-0.25,0,0);
      break;
    case GLUT_KEY_RIGHT: theShip->strafe(0.25,0,0);
      break;
    case GLUT_KEY_PAGE_DOWN:
      break;
    case GLUT_KEY_PAGE_UP:
      break;
    }		

}

// No usada
void OnMouseBtn(int button, int state,int x, int y)
{
  if(state==GLUT_DOWN)
    if(button==GLUT_LEFT_BUTTON)
      MODE=TRANS;
    else
      if(button==GLUT_RIGHT_BUTTON)
        MODE=ROT;
      else
        MODE=NONE;
}

 
// No usada
void  OnMouseMoveBtn  (int x, int y)
{
   
  if(MODE==TRANS)
    {
     
    }
  else
    {
     
    }

}




 
