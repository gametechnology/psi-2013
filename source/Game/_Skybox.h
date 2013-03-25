#include "Engine/Game.h"

class Skybox : public Entity  
{
public:
	Skybox(Composite* parent);
	~Skybox();

	void handleTextures(int curMap);
private:
	ITexture* _skyBoxTexture;
	stringw _currentTexture;
};
