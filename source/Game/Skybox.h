/*
	Example entity for loading a model
*/

#ifndef SKYBOX
#define SKYBOX

#include "Engine/Entity.h"
#include "Engine/Game.h"
class Skybox : public Entity  {
public:
	Skybox( const io::path & filePath );
	void init(void);
	virtual ~Skybox();

	irr::scene::ISceneNode *skydome;

private:
	io::path  _filePath;
};

#endif
