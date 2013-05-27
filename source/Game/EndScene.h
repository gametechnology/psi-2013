#ifndef ENDSCENE_H
#define ENDSCENE_H

#include <Engine\Core.h>
#include "EndSceneEventReceiver.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class EndScene : public Scene
{
public:
	EndScene(bool lostGame);
	~EndScene();
	void init();
	void update();
	void BackToMainMenu();
	virtual void addGuiElements();

	//GUI
	IGUIEnvironment* guiEnv;
	IGUIWindow* endGameWindow;
	IGUIStaticText* winOrLoseMessage;
	IGUIButton* backbutton;
	EndSceneEventReceiver* eventReceiver;

private:
	bool _didWeLose;
};
#endif