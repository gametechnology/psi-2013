
#include "stdafx.h"
using namespace std;

#include "StandardObject.h"

	ISceneManager* StandardObject::smgr;
	IVideoDriver* StandardObject::driver;
	const f32 MOVEMENT_SPEED= 500.0f;
	const f32 ROTATION_SPEED= 1.0f;

	// Velocity for speed
	float currentVelocity = 0;
	float maxVelocity = 100;
	float AcceleratePer= 0.1f; 

	// Velocity for rolling
	float currentRollVelocity = 0; 
	float maxRollVelocity = 100; 
	float RollAcceleratePer = 0.1f; 

	// Velocity for pitching
	float currentPitchVelocity = 0; 
	float maxPitchVelocity = 100; 
	float PitchAcceleratePer = 0.1f; 


	//default constructor
	StandardObject::StandardObject()
	{
		//is empty 
	}
	//default constructor where you need to set the filename for mesh and texture
	StandardObject::StandardObject(const io::path & meshFilename,const io::path & textureFilename)
	{
		setMesh(meshFilename);
		if (!mesh)
		{
			//device->drop();
			//return 1;
		}
		node = smgr->addAnimatedMeshSceneNode( mesh );
	
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(scene::EMAT_STAND);
			setTexture(textureFilename);
		}

	}
	// constructor with position and other atributes
	StandardObject::StandardObject(vector3df position)
	{
		setMesh("../Assets/r_flag.md3");
		if (!mesh)
		{
			//device->drop();
			//return 1;
		}
		node = smgr->addAnimatedMeshSceneNode( mesh );
	
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(scene::EMAT_STAND);
			setTexture("../Assets/r_flag2.tga");
			node->setPosition(position);
			
		}

	}
	
	// constructor with position and other atributes + filename of mesh and texture
	StandardObject::StandardObject(vector3df position,const io::path & meshFilename,const io::path & textureFilename)
	{ 
		setMesh(meshFilename);
		if (!mesh)
		{
			//device->drop();
			//return 1;
		}
		node = smgr->addAnimatedMeshSceneNode( mesh );
	
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(scene::EMAT_STAND);
			setTexture(textureFilename);
			node->setPosition(position);
		}
		ps = smgr->addParticleSystemSceneNode(false);

		scene::IParticleEmitter* em = ps->createBoxEmitter(
		core::aabbox3d<f32>(-170,-170,0,170,170,10), // emitter size
		core::vector3df(0.0f,0.06f,0.0f),   // initial direction
		800,1000,                            // emit rate
		video::SColor(0,255,255,255),       // darkest color
		video::SColor(0,255,255,255),      // brightest color
		160,400,0,                         // min and max age, angle org+1 800,2000
		core::dimension2df(1.f,1.f),         // min size
		core::dimension2df(2.f,2.f));       // max size

		ps->setEmitter(em); // this grabs the emitter
		em->drop(); // so we can drop it here without deleting it

		scene::IParticleAffector* paf = ps->createFadeOutParticleAffector(irr::video::SColor(0,0,0,0),100U);

		ps->addAffector(paf); // same goes for the affector
		paf->drop();

		ps->setPosition(core::vector3df(-70,60,40));
		ps->setScale(core::vector3df(2,2,2));
		ps->setMaterialFlag(video::EMF_LIGHTING, false);
		ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		ps->setMaterialTexture(0, driver->getTexture("../Assets/Star2.bmp"));
		ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		//ps->setDebugDataVisible(irr::scene::E_DEBUG_SCENE_TYPE::EDS_FULL);
	}
	/*Update function
	*/
	void StandardObject::Update(bool input[], f32 deltaTime)
	{
		vector3df tempPosition = node->getPosition();
		vector3df tempRotation = node->getRotation();

		core::vector3df forward = core::vector3df(0, 0, 1);
		core::vector3df right = core::vector3df(1, 0, 0);
		core::vector3df up = core::vector3df(0, 1, 0);
  
		core::matrix4 NodeRotation =
		core::matrix4().setRotationDegrees(tempRotation);

		NodeRotation.transformVect(forward);
		NodeRotation.transformVect(right);
		NodeRotation.transformVect(up);
		
		//Forward
		if(input[irr::KEY_UP]){
			if(currentVelocity < maxVelocity) {
				currentVelocity += AcceleratePer;
			}
		}
		else {
			if(currentVelocity >= 0) {
				currentVelocity -= AcceleratePer; 
			}
		}

		tempPosition -= forward*((MOVEMENT_SPEED/maxVelocity)*currentVelocity)*deltaTime;

		//BackWards
		if(input[irr::KEY_DOWN]){
			if(currentVelocity > -maxVelocity) {
				currentVelocity -= AcceleratePer;
			}
		}
		else {
			if(currentVelocity <= 0) {
				currentVelocity += AcceleratePer; 
			}
		}
		////Left
		//if(input[KEY_KEY_A]) {
		//	tempPosition += right * MOVEMENT_SPEED*deltaTime;
		//	
		//}
		////Right
		//if(input[KEY_KEY_D]) {
		//	tempPosition -= right * MOVEMENT_SPEED*deltaTime;\
		//}
		f32 yawChange = 0;
		f32 pitchChange = 0;
		f32 rollChange = 0;

		//PitchUP
		if(input[irr::KEY_KEY_S]) {
			if(currentPitchVelocity <= maxPitchVelocity) { 
				currentPitchVelocity += PitchAcceleratePer; 
			}
		}
		else if((currentPitchVelocity > 0)) { 
			currentPitchVelocity -= PitchAcceleratePer; 
			}
		
		pitchChange += ((ROTATION_SPEED/maxPitchVelocity)*currentPitchVelocity)*deltaTime;
		//PitchDown
		if(input[irr::KEY_KEY_W]) { 
			if(currentPitchVelocity >= -maxPitchVelocity) { 
				currentPitchVelocity -= PitchAcceleratePer; 
			}
		}
		else if((currentPitchVelocity < 0)) { 
			currentPitchVelocity += PitchAcceleratePer; 
		}
		pitchChange += ((ROTATION_SPEED/maxPitchVelocity)*currentPitchVelocity)*deltaTime;

		//rollLeft
		if(input[irr::KEY_KEY_A]) { 
			if(currentRollVelocity >= -maxRollVelocity) { 
				currentRollVelocity -= RollAcceleratePer; 
			}
		}
		else if((currentRollVelocity < 0)) { 
			currentRollVelocity += RollAcceleratePer; 
		}

		//rollRight
		if(input[irr::KEY_KEY_D]) {
			if(currentRollVelocity <= maxRollVelocity) {
				currentRollVelocity += RollAcceleratePer; 
			}
		}
		else if((currentRollVelocity > 0)) { 
			currentRollVelocity -= RollAcceleratePer; 
		}
		
		rollChange += ((ROTATION_SPEED/maxRollVelocity)*currentRollVelocity)*deltaTime;

		if(input[irr::KEY_KEY_D]) {
			if(currentRollVelocity <= maxRollVelocity) {
				currentRollVelocity += RollAcceleratePer; 
			}
		}
		else if((currentRollVelocity > 0)) { 
			currentRollVelocity -= RollAcceleratePer; 
		}
		
		rollChange += ((ROTATION_SPEED/maxRollVelocity)*currentRollVelocity)*deltaTime;

		// calculate the orientation from ypr
		 core::quaternion orientation (tempRotation * core::DEGTORAD); 

		// calculate the change in orientation
		 core::quaternion newOrientation (pitchChange, yawChange, rollChange);

		// apply change in orientation
		orientation *= newOrientation;

		// set new orientation
		orientation.toEuler(tempRotation * core::RADTODEG);
		core::vector3df newRotation; 
		orientation.toEuler(newRotation);
		//Setting the node's position
		node->setPosition(tempPosition);
		node->setRotation(newRotation * core::RADTODEG);
  
		//Creating the target
		core::vector3df target = core::vector3df();
		target += node->getPosition();
		target += forward;
  
		//Setting the camera
		smgr->getActiveCamera()->setTarget(target);
		smgr->getActiveCamera()->setUpVector(up);
		smgr->getActiveCamera()->setRotation(node->getRotation());

		//setting particles
		
		// calculate the change in orientation
		// core::quaternion particleOrientation (90, 0, 0);
		// particleOrientation*=orientation;
		//core::vector3df particleUp;
		//particleOrientation.toEuler(particleUp*core::RADTODEG);
		if(currentVelocity>=3.5||currentVelocity<=-3.5){
			ps->setVisible(true);
		}else{
			ps->setVisible(false);
		}
		ps->setPosition(target);
		//ps->setRotation(node->getRotation());newRotation * core::RADTODEG core::vector3df(90,0,90)+
		ps->setRotation(node->getRotation());
		ps->getEmitter()->setDirection((smgr->getActiveCamera()->getAbsolutePosition()-target).normalize()/1000);
		
		
	}

	//Unimportant crap Left over from Old project
	void StandardObject::AddForce(vector3df force)
	{
		this->forceAccumulated += force;
	}

	// A setter so that the programmer has the ability to set the mesh after constructor
	void StandardObject::setMesh(const io::path & filename)
	{
		mesh = smgr->getMesh(filename);
	}
	// A setter so that the programmer has the ability to set the texture after constructor
	void StandardObject::setTexture(const io::path & filename)
	{
		node->setMaterialTexture(0, driver->getTexture(filename) );
	}
	// a getter that returns the mesh of this object
	IAnimatedMesh* StandardObject::getMesh()
	{
		return mesh;
	}
	// a getter that returns the node of this object, usefull for changing position and stuff
	IAnimatedMeshSceneNode* StandardObject::getNode()
	{
		return node;
	}
	float StandardObject::getVelocity(){
		return currentVelocity;
	}
	float StandardObject::getPitchVelocity(){
		return currentPitchVelocity;
	}
	float StandardObject::getRollVelocity(){
		return currentRollVelocity;
	}
	//obsolete
	void StandardObject::drawall()
	{

	}