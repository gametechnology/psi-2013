
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
#ifndef BASICOBJECT_H
#define BASICOBJECT_H

class BasicObject {
    public:
		//variables
		static ISceneManager* smgr;
		static IVideoDriver* driver;

		float inverseMass;
		//functions
		BasicObject();  // parameterless default constructor
		BasicObject(vector3df position);  // position constructor
		BasicObject(const io::path & meshFilename,const io::path & textureFilename);  // mesh & texture constructor
		BasicObject(vector3df position, const io::path & meshFilename,const io::path & textureFilename);  // position & mesh & texture constructor
		void setMesh(const io::path & filename);
		void setTexture(const io::path & filename);
		void drawall();
		IAnimatedMesh* getMesh();
		IAnimatedMeshSceneNode* getNode();
    private:
		//variables
		IAnimatedMesh* mesh;
		IAnimatedMeshSceneNode* node;
		scene::IParticleSystemSceneNode* ps;
		vector3df forceAccumulated;

};
#endif