/*
	Example entity for loading a model
*/

#ifndef SKYBOX
#define SKYBOX

#include "Entity.h"
#include "Game.h"
class Skybox : public Entity  {
public:
	Skybox(const io::path & filePath, Composite* parent);
	virtual ~Skybox();
};

#endif
