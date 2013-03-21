/*
	Example entity for loading a model
*/

#ifndef SKYBOX
#define SKYBOX

#include "Engine/Entity.h"
#include "Engine/Game.h"
class Skybox : public Entity  {
public:
	Skybox(irr::io::IReadFile* filePath, Composite* parent);
	virtual ~Skybox();
};

#endif
