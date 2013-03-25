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
#include "CalculateRotation.h"

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
//ILightSceneNode* light;

//SkyBox Manager
SkyBoxManager* skyBoxMgr;

//Planet Manager
PlanetManager* planetMgr;
//Station
Station* helmStation;

unsigned scale = 1;

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

//	light = smgr->addLightSceneNode(0,vector3df(5000,5000,5000),SColor(100,100,100,255),100000);
	//the the GUI
	guienv = device->getGUIEnvironment();

	//Make a velocityTextbox
	IGUIStaticText* velocityTextBox = guienv->addStaticText(L"this is text", rect<s32>(10,10,90,22), false,true,0,-1,false); 
	velocityTextBox->setRelativePosition(vector2di(878,655));

	//Make a energytextbox	
	IGUIStaticText* energyTextBox = guienv->addStaticText(L"this is text", rect<s32>(10,10,100,22), false,true,0,-1,false); 
	energyTextBox->setRelativePosition(vector2di(276,653));
	
	//SkyBoxManager
	skyBoxMgr = new SkyBoxManager();
	skyBoxMgr->loadTexture(smgr, driver);

	//PlanetManager
	planetMgr = new PlanetManager();
	planetMgr->InitializeMeshes(smgr);
	planetMgr->PlacePlanets();
	planetMgr->LetThereBeLights(smgr);

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
	 f32 accelerationUnit = 2;
	 u32 then = device->getTimer()->getTime();

	 //sets the force of the small and big thrusters
	 Thruster::bigThrusterForce = 1000;
	 Thruster::smallThrusterForce = 200;
	//creates all the thrusters for the rotation
	Thruster thruster = Thruster(vector3df(0, 0, 0), vector3df(0,0,5), Thruster::Left);
	Thruster thruster2 = Thruster(vector3df(0,0,0), vector3df(0, 0, 5), Thruster::Right);
	Thruster thruster3 = Thruster(vector3df(0,0,0), vector3df(0, 0, 5), Thruster::Up);
	Thruster thruster4 = Thruster(vector3df(0,0,0), vector3df(0, 0, 5), Thruster::Down);
	Thruster thruster5 = Thruster(vector3df(0,0,0), vector3df(2, -1, 0), Thruster::RollLeft);
	Thruster thruster6 = Thruster(vector3df(0,0,0), vector3df(-2, -1, 0), Thruster::RollRight);
	
	//creates a big thruster at the back, and two small thrusters up front
	Thruster bigThruster = Thruster(vector3df(0,0,0), vector3df(0, 0, -5), Thruster::Forward);
	Thruster smallThruster1 = Thruster(vector3df(0,0,0), vector3df(1, 0, 7), Thruster::Backward);
	Thruster smallThruster2 = Thruster(vector3df(0,0,0), vector3df(-1, 0, 7), Thruster::Backward);

	//vector for the rotation
	vector3df rotationY = vector3df(0,0,0);
	vector3df rotationX = vector3df(0,0,0);

	//used for the momentum of inertia, currently not used, only m is used (mass)
	CalculateRotation mathRotation;
	float h, w, d, m;

	m = 500;
	h = 50;
	w = 35;
	d = 100;

	float inertiaData[16];

	for(unsigned i = 0; i < 16; i++)
	{
		inertiaData[i] = 0.0f;
	}

	inertiaData[0] = (((1.0f / 5.0f) * m) * (pow(w, 2) + pow(d, 2)));
	inertiaData[5] = (((1.0f / 5.0f) * m) * (pow(h, 2) + pow(d, 2)));
	inertiaData[10] = (((1.0f / 5.0f) * m) * (pow(h, 2) + pow(w, 2)));
	inertiaData[15] = 1.0f;

	matrix4 inertiaMatrix;
	inertiaMatrix.setM(inertiaData);



	//while the program is running, it will perform this
	while(device->run())
	{
		//if the window is active
		if(device->isWindowActive())
		{
			// Text for Textbox
			stringw velocitystr = L"Velocity: ";
			velocitystr += s32(velocity.X);
			velocitystr += ",";
			velocitystr += s32(velocity.Y);
			velocitystr += ",";
			velocitystr += s32(velocity.Z);
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

						//rotates the ship Left
			if(input.IsKeyDown(KEY_KEY_A))
			{
				//mathRotation.calcAngularMotion returns the acceleration which needs to be converted to velocity which then can be add to thsi rotation
				rotationY += mathRotation.calcAngularMotion(inertiaMatrix, thruster.UseThruster());
			}
			//rotates the ship Right
			if(input.IsKeyDown(KEY_KEY_D))
			{
				//mathRotation.calcAngularMotion returns the acceleration which needs to be converted to velocity which then can be add to thsi rotation
				rotationY += mathRotation.calcAngularMotion(inertiaMatrix, thruster2.UseThruster());
			}
			
			//rotates the ship Down
			if(input.IsKeyDown(KEY_KEY_W))
			{
				//mathRotation.calcAngularMotion returns the acceleration which needs to be converted to velocity which then can be add to thsi rotation
				rotationX += mathRotation.calcAngularMotion(inertiaMatrix, thruster3.UseThruster());
			}
			
			//rotates the ship Up
			if(input.IsKeyDown(KEY_KEY_S))
			{
				//mathRotation.calcAngularMotion returns the acceleration which needs to be converted to velocity which then can be add to thsi rotation
				rotationX += mathRotation.calcAngularMotion(inertiaMatrix, thruster4.UseThruster());
			} 
		
			/*//rotates the ship Rolling Right
			if(input.IsKeyDown(KEY_KEY_Q))
			{
				//mathRotation.calcAngularMotion returns the acceleration which needs to be converted to velocity which then can be add to thsi rotation
				rotation += mathRotation.calcAngularMotion(inertiaMatrix, thruster5.UseThruster());
			}
			
			//rotates the ship Rolling Left
			if(input.IsKeyDown(KEY_KEY_E))
			{
				//mathRotation.calcAngularMotion returns the acceleration which needs to be converted to velocity which then can be add to thsi rotation
				rotation += mathRotation.calcAngularMotion(inertiaMatrix, thruster6.UseThruster());
			}*/

			matrix4 rotationMatrixY = mathRotation.CreateFromQuaternion(mathRotation.CreateFromYawPitchRoll(rotationY.X, rotationY.Y, rotationY.Z));
			matrix4 rotationMatrixX = mathRotation.CreateFromQuaternion(mathRotation.CreateFromYawPitchRoll(rotationX.X, rotationX.Y, rotationX.Z));
			matrix4 rotationMatrix = rotationMatrixX;
			rotationMatrix *= rotationMatrixY;

			//Check if the C key is pressed, if so activate booster by changing the booster multiplier
			if(input.IsKeyDown(KEY_KEY_C) && boostUnit > 0.0f)
			{
			  boosterMP = 5;
			  boostUnit -= 1;
			}

			//If Z key is pressed , go forward. If X key, go backwards.
			if(input.IsKeyDown(KEY_UP) && velocity.Z < MAX_SPEED)
			{
				accelerationUnit = bigThruster.UseThruster(m);
			}
			else if(input.IsKeyDown(KEY_DOWN) && velocity.Z > MIN_SPEED)
			{
				accelerationUnit = -(smallThruster1.UseThruster(m) + smallThruster2.UseThruster(m));
		    }
			else
			{
				accelerationUnit = 0;
			}

			//Change velocity and position if no key is pressed. This is to maintain speed, because there is no resistance in space
				velocity.Z = ((accelerationUnit * boosterMP) *frameDeltaTime) + initialVelocity.Z;
				nodePosition.Z = (0.5f*accelerationUnit* pow(frameDeltaTime,2)) + (initialVelocity.Z*frameDeltaTime) + initialPos.Z;
				initialVelocity = velocity;
				initialPos = nodePosition;
			boosterMP = 1;

			csn->setViewMatrixAffector(rotationMatrix);
		    csn->setPosition(nodePosition);

			//draw the scene
			driver->endScene();
		}//end if isWindowActive
	 }//end while devince running
	 
	device->drop();
	return 0;
}