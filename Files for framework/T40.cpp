// Skeleton of implementation file for groups

#include "game.h"
#include "field.h"
#include "T40.h"

//////////////////////////////

T40::
T40(ISceneManager* smgr,
	 IVideoDriver* driver,
	 int x, int y, playground pg) 
  : Floor(smgr,driver,x,y,pg)
    // calling the parent constructor 
    // (if you implement a Floor Field, replace "Wall" with "Floor")
{
  // use a different texture than parent class:
  texture=driver->getTexture(texturepath+"Forward.png"); //Forward is flipped because of the camera
  block->setMaterialTexture(0,texture); 
} ;

void T40::sphereEnter(Sphere &s){
	vector3df v = s.getVelocity();
	if(v.Z > 200) { 		// Comes from left with more than 200 velocity
		v.Z = -v.Z; 		// Make it go the other direction without adding speed
	} else if(v.Z > 0) { 	// Comes from left
		v.Z = -v.Z * 1.50;	// Bounce and mult with 1.5
	} else if(v.Z >= -200) {// Comes from right with more than 200 velocity
		v.Z = v.Z * 3.0;	// Keep direction and mult velocity with 3.0
	}
	s.setVelocity(v);
}

fieldtype T40::getFieldType(){ 
  return tT40; 
}
