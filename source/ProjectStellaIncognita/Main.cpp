/**
Project Stella Incognita
Hogeschool van Amsterdam
Helm Station
*/

#include <irrlicht.h>
#include "SkyBoxManager.h"
#include "PlanetManager.h"
#include "Station.h"
#include "Input.h"
#include "Thruster.h"

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

//initiation of te device
IrrlichtDevice* device;

//initiation of the driver
IVideoDriver* driver;

//initiation of the scene Manager
ISceneManager* smgr;

//Initiation of the GUI environment
IGUIEnvironment* guienv;

//Initiation of a mesh
//IMesh* mesh[8];

//Initiation of a node
//ISceneNode* node[20];

//Initiation of the camera
ICameraSceneNode* csn;

//Initiation of light
ILightSceneNode* light;

//SkyBox Manager
SkyBoxManager* skyBoxMgr;

//Planet Manager
PlanetManager* planetMgr;
//Station
Station* helmStation;

unsigned scale = 100;

//input currently only keyboard
Input input;

int main()
{
	//create the window
	device = createDevice(EDT_DIRECT3D9, dimension2d<u32>(1280, 720), false, false, false);
	device->setEventReceiver(&input);
	//get the driver from the device
	driver = device->getVideoDriver();

	//get the scene
	smgr = device->getSceneManager();

	//add the camera to the scene
	csn = smgr->addCameraSceneNodeFPS();

	light = smgr->addLightSceneNode(0,vector3df(5000,5000,5000),SColor(100,100,100,255),100000);
	//the the GUI
	guienv = device->getGUIEnvironment();

	//Make a velocityTextbox
	IGUIStaticText* velocityTextBox = guienv->addStaticText(L"this is text", rect<s32>(10,10,90,22), false,true,0,-1,false); 
	velocityTextBox->setRelativePosition(vector2di(878,655));

	//Make a energytextbox	
	IGUIStaticText* energyTextBox = guienv->addStaticText(L"this is text", rect<s32>(10,10,100,22), false,true,0,-1,false); 
	energyTextBox->setRelativePosition(vector2di(276,653));

	//the mesh gets the model with the scene manager
	/* mesh[0] = smgr->getMesh("../../assets/Models/floor.3ds");
	 mesh[1] = smgr->getMesh("../../assets/Models/Cube.3ds");
	 mesh[2] = smgr->getMesh("../../assets/Models/teapot.3ds");
	 mesh[3] = smgr->getMesh("../../assets/Models/UnknownAst.3ds");
	 mesh[0]->getBoundingBox();
	 mesh[1]->getBoundingBox();
	 mesh[2]->getBoundingBox();
	 mesh[3]->getBoundingBox();

	 //add the mesh to a scene node
 
	 bool rerun = true;
	 unsigned i = 0;
	 while (rerun)
	 {
		node[i] = smgr->addMeshSceneNode(mesh[rand() % 3+1]);
		signed v1 = (rand() % 1000 + 1)-1000;
		signed v2 = (rand() % 1000 + 1)-1000;
		signed v3 = (rand() % 1000 + 1)-1000;
		node[i]->setPosition(vector3df(v1,v2,v3));
		node[i]->setScale(vector3df(scale,scale,scale));
	
		if (i+1>=20)
		{
			rerun = false;
		}
		i++;
	 }*/

	
	//SkyBoxManager
	skyBoxMgr = new SkyBoxManager();
	skyBoxMgr->loadTexture(smgr, driver);

	//PlanetManager
	planetMgr = new PlanetManager();
	planetMgr->InitializeMeshes(smgr);
	planetMgr->PlacePlanets();

	//HelmStation
	helmStation = new Station();
	helmStation->loadTexture(smgr, driver);

	//Variables for calculating velocity and position . Also difference between frames is calculated
	 f32 boosterMP = 1.0f;
	 f32 boostUnit = 5000;
	 const f32 MAX_SPEED = 200;
	 const f32 MIN_SPEED = -(MAX_SPEED /4);
	 vector3df velocity = vector3df(0,0,0);
	 vector3df initialVelocity;
	 vector3df initialPos;
	 f32 accelerationUnit = 1;
	 u32 then = device->getTimer()->getTime();


	//creates all the thrusters for the rotation
	Thruster thruster = Thruster(vector3df(0, 0, 0), vector3df(2,0,5), Thruster::Left, 10.0f);
	Thruster thruster2 = Thruster(vector3df(0,0,0), vector3df(-2, 0, 5), Thruster::Right, 10.0f);
	Thruster thruster3 = Thruster(vector3df(0,0,0), vector3df(0, -1, 5), Thruster::Up, 10.0f);
	Thruster thruster4 = Thruster(vector3df(0,0,0), vector3df(0, 1, 5), Thruster::Down, 10.0f);
	Thruster thruster5 = Thruster(vector3df(0,0,0), vector3df(2, -1, 0), Thruster::RollLeft, 10.0f);
	Thruster thruster6 = Thruster(vector3df(0,0,0), vector3df(-2, -1, 0), Thruster::RollRight, 10.0f);
	
	//vector for the rotation
	vector3df rotation = vector3df(0,0,0);

	//while the program is running, it will perform this
	while(device->run())
	{
		//if the window is active
		if(device->isWindowActive())
		{
			// Text for Textbox
			stringw velocitystr = L"Velocity: ";
			velocitystr += u32(velocity.Z);
			stringw energystr = L"Energy: ";
			energystr += u32(boostUnit);
			velocityTextBox->setText(velocitystr.c_str());
			energyTextBox->setText(energystr.c_str());

			// Work out a frame delta time.
			const u32 now = device->getTimer()->getTime();
			const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
			then = now;
			core::vector3df nodePosition = csn->getPosition();


			driver->beginScene(true,true, SColor(1,0,0,0));
			//draw with the scene manager
			smgr->drawAll();
			//draw everything in the scene manager
			helmStation->drawTexture();
			//draw in the gui environment
			guienv->drawAll();
			//make mouse invisible
			device->getCursorControl()->setVisible(false);

			//Check if the C key is pressed, if so activate booster by changing the booster multiplier
			if(input.IsKeyDown(KEY_KEY_C) && boostUnit > 0.0f)
			{
			  boosterMP = 5;
			  boostUnit -= 1;
			}

			//If Z key is pressed , go forward. If X key, go backwards.
			if(input.IsKeyDown(KEY_UP) && velocity.Z < MAX_SPEED)
			{
			  velocity.Z = ((accelerationUnit * boosterMP) *frameDeltaTime) + initialVelocity.Z;
			  nodePosition.Z = (0.5f*accelerationUnit* pow(frameDeltaTime,2)) + (initialVelocity.Z*frameDeltaTime) + initialPos.Z;
			  initialVelocity = velocity;
			  initialPos = nodePosition;
			}
			else if(input.IsKeyDown(KEY_DOWN) && velocity.Z > MIN_SPEED)
			{
			 velocity.Z = -((accelerationUnit * boosterMP) *frameDeltaTime) + initialVelocity.Z;
			 nodePosition.Z = -(0.5f*accelerationUnit* pow(frameDeltaTime,2)) + (initialVelocity.Z*frameDeltaTime) + initialPos.Z;
			 initialVelocity = velocity;
			 initialPos = nodePosition;
		    }

			//rotates the ship Left
			if(input.IsKeyDown(KEY_KEY_A))
			{
				rotation += thruster.UseThruster(100);
			}
			//rotates the ship Right
			if(input.IsKeyDown(KEY_KEY_D))
			{
				rotation += thruster2.UseThruster(100);
			}
			
			//rotates the ship Down
			if(input.IsKeyDown(KEY_KEY_S))
			{
				rotation += thruster3.UseThruster(100);
			}
			
			//rotates the ship Up
			if(input.IsKeyDown(KEY_KEY_W))
			{
				rotation += thruster4.UseThruster(100);
			}
		
			//rotates the ship Rolling Right
			if(input.IsKeyDown(KEY_KEY_E))
			{
				rotation += thruster5.UseThruster(100);
			}
			
			//rotates the ship Rolling Left
			if(input.IsKeyDown(KEY_KEY_Q))
			{
				rotation += thruster6.UseThruster(100);
			}

			//Change velocity and position if no key is pressed. This is to maintain speed, because there is no resistance in space
			velocity.Z = initialVelocity.Z;
			nodePosition.Z = (initialVelocity.Z*frameDeltaTime) + initialPos.Z;
			initialVelocity = velocity;
			initialPos = nodePosition;
			boosterMP = 1;
		    csn->setPosition(nodePosition);
			csn->setRotation(rotation);

			//draw the scene
			driver->endScene();
		}//end if isWindowActive
	 }//end while devince running
	 
	device->drop();
	return 0;
}