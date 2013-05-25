#include "EndScene.h"


EndScene::EndScene(bool lostGame)
{
	this->_didWeLose = lostGame;
}

void EndScene::init()
{
	guiEnv = game->guiEnv;

	this->addGuiElements();
	
	// Then create the event receiver, giving it that context structure.
	eventReceiver = new EndSceneEventReceiver(this->game);

	// And tell the device to use our custom event receiver.
	game->input->setCustomEventReceiver(eventReceiver);
}

void EndScene::addGuiElements()
{
	endGameWindow = guiEnv->addWindow(rect<s32>(position2di(80, 30),dimension2di(600, 550)),false,L"End of Game",0,100);
	endGameWindow->getCloseButton()->remove();

	if(this->_didWeLose)
	{
		winOrLoseMessage = guiEnv->addStaticText(L"Your team lost",rect<s32>(position2di(300,165),dimension2di(200,25)),false,true,endGameWindow);
	}else
	{
		winOrLoseMessage = guiEnv->addStaticText(L"Your team won!",rect<s32>(position2di(300,165),dimension2di(200,25)),false,true,endGameWindow);
	}

	backbutton	= guiEnv->addButton(rect<s32>(position2di(50,105),dimension2di(200,25)),endGameWindow,0, L"Back to Main Menu");
}

void EndScene::update()
{

}

void EndScene::BackToMainMenu()
{
	endGameWindow->setVisible(false);
}

EndScene::~EndScene()
{
	Scene::~Scene();
}