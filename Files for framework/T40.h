// note that your header files must be protected against multiple inclusion using the definition of a special identifier
// note that you also need the #endif at the end of the file
 
#ifndef ____TT40____
#define ____TT40____

#include "game.h"
#include "field.h"

class T40: public Floor // if you implement a Floor tile, replace "Wall" with "Floor"
{
public:
  T40(ISceneManager* smgr,
      IVideoDriver* driver,
      int x, int y, playground  pg) ;
  virtual fieldtype getFieldType();
  virtual void sphereEnter(Sphere &s);
  // you need to declare here all (virtual) functions that change with respect to parent class
  // see example in testfiled.h and testfield.cpp
};


#endif
