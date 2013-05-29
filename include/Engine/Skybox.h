#ifndef SKYBOX_COMP
#define SKYBOX_COMP

#include <Engine/Component.h>
#include <Irrlicht/irrlicht.h>
#include <string>

class Skybox : public Component
{
public:
	Skybox(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, std::string imagePrefix);
	~Skybox();

	virtual void handleMessage(unsigned int, void* data = 0) { };
private:
	irr::scene::ISceneManager* _smgr;
	irr::scene::ISceneNode* _skybox;
	std::string basePath;
};

#endif