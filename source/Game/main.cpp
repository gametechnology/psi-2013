#include <Engine/Core.h>
#include <Engine/Interface.h>
#include <Irrlicht/driverChoice.h>

#include "MainMenuScene.h"

using namespace irr;

void packetDistributor()
{
	while(true)
		Network::GetInstance()->DistributeReceivedPackets();
}

int main()
{
	Core* core = new Core(1280, 720, 32);

	Interface* f_interface = new Interface(core->getGuiEnv(), core->getDriver());

	core->setActiveScene(new MainMenuScene(core, f_interface));	

	irr::u32 then = core->getDevice()->getTimer()->getTime();
	irr::gui::IGUIStaticText* text = core->getGuiEnv()->addStaticText(L"", irr::core::rect<s32>(10, 10, 50, 50), true, true, 0, -1, true);
	int fps = 0;

	// If the network function for packet distribution is used within the game loop thread, it will decrease the FPS by 50%.
	sf::Thread packetDistThread(&packetDistributor);
	packetDistThread.launch();

	while (core->getDevice()->run())
	{
		const irr::u32 now = core->getDevice()->getTimer()->getTime();
		const irr::s32 frameDeltaTime = (now - then) / 1000.f; // Time in seconds
		then = now;

		if (core->getDevice()->isWindowActive())
		{
			fps = core->getDriver()->getFPS();
			wchar_t fn[16];
			wsprintf(fn, L"%i", fps);
			text->setText(fn);

			core->update(frameDeltaTime);
			core->draw(255, 100, 101, 140);			
		}
		else
			core->getDevice()->yield();
	}

	core->getDevice()->drop();
	packetDistThread.terminate();

	return 0;
}