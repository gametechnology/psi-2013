#include "EndScene.h"


EndScene::EndScene(bool lostGame)
{

}

void EndScene::init()
{
	guiEnv = game->guiEnv;

	endGameWindow = guiEnv->addWindow(rect<s32>(position2di(80, 30),dimension2di(600, 550)),false,L"End of Game",0,100);
	endGameWindow->getCloseButton()->remove();

	backbutton	= guiEnv->addButton(rect<s32>(position2di(50,105),dimension2di(200,25)),endGameWindow,2, L"Back to Main Menu");
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
	delete guiEnv;
	delete endGameWindow;
	delete backbutton;
}