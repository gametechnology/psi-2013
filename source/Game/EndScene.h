#ifndef ENDSCENE_H
#define ENDSCENE_H

#include "Engine\Game.h"

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

	//GUI
	IGUIEnvironment* guiEnv;
	IGUIWindow* endGameWindow;
	IGUIButton* backbutton;
};
#endif