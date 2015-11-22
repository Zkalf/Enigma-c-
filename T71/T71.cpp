// Skeleton of implementation file for groups

#include "game.h"
#include "field.h"
#include "T71.h"
#include "T1.h"




T71::T71(ISceneManager* smgr,
	 IVideoDriver* driver,
	 int x, int y, playground pg) 
    : Floor(smgr,driver,x,y,pg)
   {
  this->texture=driver->getTexture(texturepath+"T71.png"); /// set the T71 texture 
  block = smgr->addCubeSceneNode(fieldsize);
  block->setMaterialTexture(0,texture); 
  block->setPosition(cubePosition(x,y,false));
  block->setMaterialFlag(video::EMF_LIGHTING, false);  
  
  
    related=0;
	}
	
	
void T71 :: introduceTo(Field &f)
	 {
	 related=(T71 *) &f;
	 }

/****************************************/	 
void T71::sphereEnter(Sphere &s){

/**********************************/
if (related)
    s.setSize(3.f); // make the sphere bigger
  else
    s.setSize(1.f); //make the sphere smaller

/**********************************/

  this->texture=driver->getTexture(texturepath+"won.png");
 
  // build a block and paint it with texture
  block = smgr->addCubeSceneNode(fieldsize);
  block->setMaterialTexture(0,texture); 
  block->setPosition(cubePosition(x,y,true));
  block->setMaterialFlag(video::EMF_LIGHTING, false); 
  
 
  cerr<<"you have won";
}

/****************************************/
/*void T71::sphereExit(Sphere &s){
if (related)
    s.setSize(3.f); // make the sphere bigger
  
  //block->setMaterialTexture(0,texture);
}*/

fieldtype T71::getFieldType(){ 
  return tT71; 
}

