#ifndef ENDSCENE_H
#define ENDSCENE_H

#include <Engine/Core.h>
#include <Engine/Interface.h>
#include <Engine/Scene.h>
#include "EndSceneEventReceiver.h"

class EndScene : public Scene
{
public:
	EndScene(Core*, Interface*, bool lostGame);

	virtual ~EndScene();
	virtual void init();
	virtual void update();

	virtual void requestNextScene();
	virtual void requestPreviousScene();

	virtual void notify(void* data);	
private:
	Core* _core;
	Interface* _interface;
	EndAppContext _context;

	bool _didWeLose;
	EndSceneEventReceiver* eventReceiver;
};
#endif