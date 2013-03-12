#include "scene.h"
#include "Entity.h"

#ifndef PLAY
#define PLAY

class Play :
	public Scene
{
public:
	Play();
	~Play();

	Entity* myModel;
};

#endif

