// note that your header files must be protected against multiple inclusion using the definition of a special identifier
// note that you also need the #endif at the end of the file
 
#ifndef ____TT71____
#define ____TT71____

#include "game.h"
#include "field.h"
#include "T1.h"


#include <irrlicht.h>
#include <iostream>
//#include <string>
using namespace irr;
using namespace std;
//using core::vector3df;
//using scene::ISceneManager;
//using scene::ISceneNode;
//using video::IVideoDriver;
//using video::ITexture;
//using core::position2di;

class T71: public Floor //, public Sphere// if you implement a Floor tile, replace "Wall" with "Floor"
{
protected:
  // this one contains a second texture (for when the sphere is on this floor)
  ITexture *alt_texture;
  //vector3df position,velocity;
  //ISceneManager* smgr;
  //IVideoDriver* driver;
  ISceneNode * sphere;
  //ITexture * texture;
  //void (*altSphereProgress)(Sphere &,position2di,f32,f32);
  f32 spheresize; 
  T71 *related;
  f32 size;

public:
  T71(ISceneManager* smgr,
      IVideoDriver* driver,
      int x, int y, playground  pg) ;
  virtual fieldtype getFieldType();  
  virtual void sphereEnter(Sphere &s);
   virtual void introduceTo(Field &f);
 // virtual void setSize(f32 size);
  
  //void sphereExit(Sphere &s);
  // you need to declare here all (virtual) functions that change with respect to parent class
  // see example in testfiled.h and testfield.cpp
  
  };
#endif
