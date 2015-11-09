#include <irrlicht.h>
#include "driverChoice.h"
#include <iostream>
#include <matrix4.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace irr;
using namespace std;

/* The following class is for handling mouse and keyboard events
   You do not need to work on this. */
class MyEventReceiver : public IEventReceiver
{
public:
  core::position2di Position;
  virtual bool OnEvent(const SEvent& event)
  {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
      {
	switch(event.MouseInput.Event)
	  {
	  case EMIE_MOUSE_MOVED:
	    Position.X = event.MouseInput.X;
	    Position.Y = event.MouseInput.Y;
	    break;
	    
	  default:
	    break;
	  }
      }    
    return false;
  }
  virtual bool IsKeyDown(EKEY_CODE keyCode) const
  {
    return KeyIsDown[keyCode];
  }
  MyEventReceiver()
  {
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
      KeyIsDown[i] = false;
  } 
private:
  bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

// The actual program
int main()
{
  // Initialization of Device, Video Driver and Scene Manager
  video::E_DRIVER_TYPE driverType=video::EDT_OPENGL; 
  MyEventReceiver receiver;  
  IrrlichtDevice* device = createDevice(driverType,
					core::dimension2d<u32>(960, 720), 16, false, false, false, &receiver);
  if (device == 0) return 1; 
  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* smgr = device->getSceneManager();

  // Building the scene. First define some constants to work with...

  const int dimx=20;   // the playground will have 20 x 13 fields
  const int dimy=13;
  const f32 fieldsize=8.f;  // each field is a square or a cube of side length 8 units 
  const f32 halffieldsize=fieldsize/2;
  const f32 spheresize = 2.f;  // sphere has radius 2 units

  const f32 offsetx=fieldsize*dimx/2; // offset of the playground's center from (0,0,0)
  const f32 offsety=fieldsize*dimy/2;

  const f32 minborderx = spheresize+fieldsize; // borders of the field (for collision detection)
  const f32 maxborderx = fieldsize*(dimx-1)-spheresize;
  const f32 minbordery = spheresize+fieldsize;  
  const f32 maxbordery = fieldsize*(dimy-1)-spheresize;
  
  //new vars
  const f32 blueTileStart = fieldsize*5-spheresize;
  const f32 blueTileEnd = fieldsize*6+spheresize;
  
  const f32 backArrowStartX = fieldsize*10-spheresize;
  const f32 backArrowEndX = fieldsize*11+spheresize;
  
  const f32 downArrowStartX = fieldsize*4-spheresize;
  const f32 downArrowEndX = fieldsize*5+spheresize;
  const f32 downArrowStartY = fieldsize*8-spheresize;
  const f32 downArrowEndY = fieldsize*9+spheresize;
  
  const f32 upArrowStartX = fieldsize*14-spheresize;
  const f32 upArrowEndX = fieldsize*15+spheresize;
  const f32 upArrowStartY = fieldsize*4-spheresize;
  const f32 upArrowEndY = fieldsize*5+spheresize;
  
  const f32 forwardArrowStartX = fieldsize*17-spheresize;
  const f32 forwardArrowEndX = fieldsize*18+spheresize;
  const f32 forwardArrowStartY = fieldsize*10-spheresize;
  const f32 forwardArrowEndY = fieldsize*11+spheresize;
  
  const f32 randTileStart = fieldsize*2-spheresize;
  const f32 randTileEnd = fieldsize*3+spheresize;
  
  const f32 stopTileStartX = fieldsize*10-spheresize;
  const f32 stopTileEndX = fieldsize*11+spheresize;
  const f32 stopTileStartY = fieldsize*11-spheresize;
  const f32 stopTileEndY = fieldsize*12+spheresize;
  
  bool isAllowed = true;
  const int maxVelocity = 400;
  int random;

  // Loading a texture to put on the squares
  io::path texturepath="base-example.app/Contents/Resources/";
  video::ITexture *texture=driver->getTexture(texturepath+"fl-acblack.png"); // Default
  video::ITexture *texture1=driver->getTexture(texturepath+"st-blue-sand.png"); // Creating new blue tile
  video::ITexture *texture2=driver->getTexture(texturepath+"Back.png");
  video::ITexture *texture3=driver->getTexture(texturepath+"Go_up.png"); // Up is down cus of camera
  video::ITexture *texture4=driver->getTexture(texturepath+"Go_down.png"); // Down is up cus of camera
  video::ITexture *texture5=driver->getTexture(texturepath+"Forward.png");
  video::ITexture *texture6=driver->getTexture(texturepath+"True_color.png");
  video::ITexture *texture7=driver->getTexture(texturepath+"No.png");
  video::ITexture *texture8=driver->getTexture(texturepath+"Pixels.png");
 
  // drawing one block for each field
  for(int i=0; i<dimx; i++){
    for(int j=0; j<dimy; j++){
      scene::ISceneNode *block = smgr->addCubeSceneNode(fieldsize);

      // For starters, all inner stones of the playground are "floor", only the outermost stones
      // form a sourrounding wall. Thus the vertical position of each stone is determined by 
      // whether it is an outer stone or not. 
      f32 vpos = i==0 || i==dimx-1 || j==0 || j==dimy-1 ? fieldsize : 0.f;

      block->setPosition(core::vector3df(fieldsize*j+halffieldsize,vpos,fieldsize*i+halffieldsize));
	  if(i==5 && j==5) {
		block->setMaterialTexture(0,texture1); // Put the blue tile texture on
	  } else if(i==10 && j==5) {
		block->setMaterialTexture(0,texture2);
	  } else if(i==4 && j==8) {
		block->setMaterialTexture(0,texture3);
	  } else if(i==14 && j==4) {
		block->setMaterialTexture(0,texture4);
	  } else if(i==17 && j==10) {
		block->setMaterialTexture(0,texture5);
	  } else if(i==2 && j==2) {
		block->setMaterialTexture(0,texture6);
	  } else if(i==10 && j==11) {
		block->setMaterialTexture(0,texture7);
	  } else {
		block->setMaterialTexture(0,texture); // Put the default texture on
	  }
      block->setMaterialFlag(video::EMF_LIGHTING, false);
    }
  }

  // the sphere (in previous version called "node")
  scene::ISceneNode * sphere = smgr->addSphereSceneNode(spheresize,32);
  sphere->setPosition(core::vector3df(offsety,spheresize+fieldsize*.5f,offsetx));
  sphere->setMaterialFlag(video::EMF_LIGHTING
			  , false);
  sphere->setMaterialTexture(0,driver->getTexture(texturepath+"fl-abyss.png")); // put a black texture on the sphere

  // add a camera from where we are looking at the scene
  scene::ICameraSceneNode* camera=smgr->addCameraSceneNode(NULL,core::vector3df(offsety+50.f,100.f,offsetx),
							        core::vector3df(offsety,0.f,offsetx));
  // to change the camera position use: 
  //    camera->setPosition(core::vector3df(...));
  // see docmentation of  ICameraSceneNode  for more (like setting target, rotation, aspect)

  // hide the mouse cursor
  device->getCursorControl()->setVisible(true); //Changed from false to true
  
  // record the current time
  u32 then = device->getTimer()->getTime();

  // set the initial velocity of the sphere
  core::vector3df velocity(30.f,0.f,10.f);

  // the friction factor, to slow down the sphere over time
  const f32 friction=.4f; //Tweaking it abit, default = 0.2f

  // remember current mouse position
  core::position2di RefPosition=receiver.Position;

  // the main loop (basically running forever)
  while(device->run())
    {
      if(receiver.IsKeyDown(irr::KEY_KEY_Q)) exit(0); // quit game on key Q
      
      // Adapt speed by the difference in mouse position
      core::position2di mousemove;
      mousemove.X=(receiver.Position.X-RefPosition.X);
      mousemove.Y=(receiver.Position.Y-RefPosition.Y);
      // eliminating too rapid movements of the mouse
      if (fabs(mousemove.X)>10) mousemove.X=0;
      if (fabs(mousemove.Y)>10) mousemove.Y=0;
      // update velocity 
      velocity.X += mousemove.Y;
      velocity.Z += mousemove.X;
      // remember current mouse position
      RefPosition=receiver.Position;

      // Measure the time that has passed since last drawing 
      const u32 now = device->getTimer()->getTime();
      const f32 frameDeltaTime = (f32)(now - then) / 1000.f; 
      then = now;

      // Friction
      velocity.X *=1-(friction*frameDeltaTime);
      velocity.Z *=1-(friction*frameDeltaTime);

      // Detect collision with wall and change speed accordingly
      core::vector3df spherePosition = sphere->getPosition();
      if (velocity.X<0){
		if (spherePosition.X<minbordery){
		  velocity.X = -velocity.X;
		}
      } else {
		if (spherePosition.X>maxbordery){
		  velocity.X = -velocity.X;
		}
      }
      if (velocity.Z<0){
		if (spherePosition.Z<minborderx){
		  velocity.Z = -velocity.Z;
		}
      } else {
		if (spherePosition.Z>maxborderx){
		  velocity.Z = -velocity.Z;
		}
      }
	  // Detect if on blue tile pos
	  if(spherePosition.Z <= blueTileEnd && spherePosition.Z >= blueTileStart 
	  && spherePosition.X <= blueTileEnd && spherePosition.X >= blueTileStart) {
		sphere->setMaterialTexture(0,driver->getTexture(texturepath+"blue.png"));
	  }
	  // Detect if on rand tile pos
	  if(spherePosition.Z <= randTileEnd && spherePosition.Z >= randTileStart 
	  && spherePosition.X <= randTileEnd && spherePosition.X >= randTileStart) {
		srand(time(NULL));
		random = rand() % 5 + 1;
		switch(random) {
			case 1:
				sphere->setMaterialTexture(0,driver->getTexture(texturepath+"fl-abyss.png"));
				break;
			case 2:
				sphere->setMaterialTexture(0,driver->getTexture(texturepath+"blue.png"));
				break;
			case 3:
				sphere->setMaterialTexture(0,driver->getTexture(texturepath+"yellow.png"));
				break;
			case 4:
				sphere->setMaterialTexture(0,driver->getTexture(texturepath+"green.png"));
				break;
			case 5:
				sphere->setMaterialTexture(0,driver->getTexture(texturepath+"red.png"));
				break;
		}
	  }
	  // Detect if on back arrow pos
	  if(spherePosition.Z <= backArrowEndX && spherePosition.Z >= backArrowStartX 
	  && spherePosition.X <= blueTileEnd && spherePosition.X >= blueTileStart) {
		if(velocity.Z < 0) {
			velocity.Z = -velocity.Z * 1.50;			
		} else {
			velocity.Z = velocity.Z * 1.05;		
		}
	  }	
	  // Detect if on forward arrow pos
	  if(spherePosition.Z <= forwardArrowEndX && spherePosition.Z >= forwardArrowStartX 
	  && spherePosition.X <= forwardArrowEndY && spherePosition.X >= forwardArrowStartY) {
		if(velocity.Z > 0) {
			velocity.Z = -velocity.Z * 1.50;			
		} else {
			velocity.Z = velocity.Z * 1.05;		
		}
	  }	
	  // Detect if on down arrow pos
	  if(spherePosition.Z <= downArrowEndX && spherePosition.Z >= downArrowStartX 
	  && spherePosition.X <= downArrowEndY && spherePosition.X >= downArrowStartY) {
		if(velocity.X < 0) {
			velocity.X = -velocity.X * 1.50;			
		} else {
			velocity.X = velocity.X * 1.05;		
		}
	  }	
	  // Detect if on up arrow pos
	  if(spherePosition.Z <= upArrowEndX && spherePosition.Z >= upArrowStartX 
	  && spherePosition.X <= upArrowEndY && spherePosition.X >= upArrowStartY) {
		if(velocity.X > 0) {
			velocity.X = -velocity.X * 1.50;			
		} else {
			velocity.X = velocity.X * 1.05;		
		}
	  }	
	  // Detect if on stop pos
	  if(spherePosition.Z <= stopTileEndX && spherePosition.Z >= stopTileStartX 
	  && spherePosition.X <= stopTileEndY && spherePosition.X >= stopTileStartY) {
		if(isAllowed) {
		  velocity.X = 0;
		  velocity.Z = 0;
		  isAllowed = false;
		} 
	  } else {
		  isAllowed = true;
		}
	  
	  // Makes sure the velocity does not get out of control
	  if(velocity.Z > maxVelocity) {
		velocity.Z = maxVelocity;		
	  }
	  if(velocity.X > maxVelocity) {
		velocity.X = maxVelocity;
	  }
		
      // Update position
      spherePosition.X += velocity.X*frameDeltaTime;
      spherePosition.Z += velocity.Z*frameDeltaTime;
      sphere->setPosition(spherePosition);
     
      // Draw the picture anew
      driver->beginScene(true, true, video::SColor(255,113,113,133));
      smgr->drawAll();
      driver->endScene();
    }
  device->drop();
  return 0;
}