
#include "stdafx.h"
using namespace std;

#include "BasicObject.h"

	ISceneManager* BasicObject::smgr;
	IVideoDriver* BasicObject::driver;
	
	//default constructor
	BasicObject::BasicObject()
	{
		//is empty 
	}

	//default constructor where you need to set the filename for mesh and texture
	BasicObject::BasicObject(const io::path & meshFilename,const io::path & textureFilename) {
		setMesh(meshFilename);
		if (!mesh) {
			//device->drop();
			//return 1;
		}
		node = smgr->addAnimatedMeshSceneNode( mesh );
	
		if (node) {
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(scene::EMAT_STAND);
			setTexture(textureFilename);
		}

	}
	// if we use this constructor you will get flags....
	// Base constructor with position and other atributes
	BasicObject::BasicObject(vector3df position) {
		//Shortend up the functution ;)

		// how we will import the pictures of the planets?
		BasicObject::BasicObject( position, "../Assets/r_flag.md3", "../Assets/r_flag2.tga");
	}


	// Lest have a look where the crane model is loaded < 
	// We will use this constructer to make our planets.
	// constructor with position and other atributes + filename of mesh and texture
	BasicObject::BasicObject(vector3df position,const io::path & meshFilename,const io::path & textureFilename) { 
		// oke lest start making planets!

		setMesh(meshFilename);
		if (!mesh) {
			//device->drop();
			//return 1;
		}
		node = smgr->addAnimatedMeshSceneNode( mesh );
	
		if (node) {
			node->setMaterialFlag(EMF_LIGHTING, false);
			if(textureFilename != ""){
				setTexture(textureFilename);
			}
			node->setPosition(position);
		}
	}

	// A setter so that the programmer has the ability to set the mesh after constructor
	void BasicObject::setMesh(const io::path & filename)
	{
		mesh = smgr->getMesh(filename);
	}
	// A setter so that the programmer has the ability to set the texture after constructor
	void BasicObject::setTexture(const io::path & filename)
	{
		node->setMaterialTexture(0, driver->getTexture(filename) );
	}
	// a getter that returns the mesh of this object
	IAnimatedMesh* BasicObject::getMesh()
	{
		return mesh;
	}
	// a getter that returns the node of this object, usefull for changing position and stuff
	IAnimatedMeshSceneNode* BasicObject::getNode()
	{
		return node;
	}
	//obsolete
	void BasicObject::drawall()
	{

	}