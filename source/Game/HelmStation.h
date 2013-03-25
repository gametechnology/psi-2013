#include "Engine\Entity.h"
#include "Irrlicht\irrlicht.h"

class HelmStation : public Entity
{
public:
	HelmStation(Composite* parent);
	virtual ~HelmStation();

	virtual void draw();
private:
	video::ITexture* _stationTexture;
};