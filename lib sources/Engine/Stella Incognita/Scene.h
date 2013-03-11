#include "Composite.h"
#include "Entity.h"

#ifndef SCENE
#define SCENE

using namespace std;

#pragma once
class Scene : Composite
{
public:
	Scene();
	~Scene(void);

	int state;
};

#endif
