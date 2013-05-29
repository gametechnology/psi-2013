#include "EndScene.h"

EndScene::EndScene(Core* core, Interface* ui, bool lostGame) : Scene("EndScene")
{
	_core = core;
	_interface = ui;
	this->_didWeLose = lostGame;
}

void EndScene::init()
{	
	_interface->addWindow(80, 30, 520, 520, false, L"End of Game", 0, END_GAME_WINDOW);

	// Bit of a hack, sorry for that.
	dynamic_cast<irr::gui::IGUIWindow*>(_interface->getElementWithId(END_GAME_WINDOW))->getCloseButton()->remove();

	if(_didWeLose)
	{
		_interface->addStaticText(L"Your team lost", 300, 165, 100, 140, WIN_LOSE_MESSAGE, false, true, false, _interface->getElementWithId(END_GAME_WINDOW));
	}else
	{
		_interface->addStaticText(L"Your team won!", 300, 165, 100, 140, WIN_LOSE_MESSAGE, false, true, false, _interface->getElementWithId(END_GAME_WINDOW));
	}

	_interface->createButton(50, 105, 150, 80, BACK_BUTTON, _interface->getElementWithId(END_GAME_WINDOW), L"Back to Main Menu");

	// Then create the event receiver, giving it that context structure.
	eventReceiver = new EndSceneEventReceiver(_context);

	// And tell the device to use our custom event receiver.
	_core->addCustomReceiver(eventReceiver);
}

void EndScene::update()
{
}

void EndScene::notify(void* data)
{
}

void EndScene::requestNextScene()
{
}

void EndScene::requestPreviousScene()
{
	_interface->getElementWithId(END_GAME_WINDOW)->setVisible(false);
}

EndScene::~EndScene()
{
	Scene::~Scene();
}