#include <Engine/Core.h>
#include <Engine/Interface.h>
#include <Irrlicht/driverChoice.h>

#include "MainMenuScene.h"

using namespace irr;

int main()
{
	Core* core = new Core(1280, 720, 32);

	Interface* f_interface = new Interface(core->getGuiEnv(), core->getDriver());

	core->setActiveScene(new MainMenuScene(core, f_interface));	

	irr::u32 then = core->getDevice()->getTimer()->getTime();

	while (core->getDevice()->run())
	{
		const irr::u32 now = core->getDevice()->getTimer()->getTime();
		const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f; // Time in seconds
		then = now;

		if (core->getDevice()->isWindowActive())
		{
			core->update(frameDeltaTime);
			core->draw(255, 100, 101, 140);
			int fps = core->getDriver()->getFPS();
		}
		else
			core->getDevice()->yield();
	}
	core->getDevice()->drop();
	return 0;
}