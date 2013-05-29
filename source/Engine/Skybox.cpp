#include <Engine/Skybox.h>

using namespace irr;
using namespace irr::scene;
using namespace irr::video;

Skybox::Skybox(ISceneManager* smgr, IVideoDriver* driver, std::string imagePrefix) : Component("Skybox"), _smgr(smgr)
{
	basePath = "../assets/Skyboxes/";
	basePath.append(imagePrefix);

	_skybox = smgr->addSkyBoxSceneNode(
		driver->getTexture((basePath+"_up.png").c_str()),
		driver->getTexture((basePath+"_dn.png").c_str()),
		driver->getTexture((basePath+"_lf.png").c_str()),
		driver->getTexture((basePath+"_rt.png").c_str()),
		driver->getTexture((basePath+"_ft.png").c_str()),
		driver->getTexture((basePath+"_bk.png").c_str()));
}

Skybox::~Skybox()
{
	_smgr->addToDeletionQueue(_skybox);

	_smgr = NULL;
}