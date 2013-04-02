#include "MainMenuScene.h"


MainMenuScene::MainMenuScene()
{
	//set the first menu
	currentWindow = MainMenuScene::Main;

	//Create the first 3 buttons
	createServerButton = guienv->addButton(rect<s32>(position2di(50,105),dimension2di(200,25)),window, 104, L"Button 1",L"Button 1");
	joinServerButton = guienv->addButton(rect<s32>(position2di(50,135),dimension2di(200,25)),window, 105, L"Button 2",L"Button 2");
	quitButton = guienv->addButton(rect<s32>(position2di(50,165),dimension2di(200,25)),window,106, L"Button 3",L"Button 3");

}


MainMenuScene::~MainMenuScene()
{
}
