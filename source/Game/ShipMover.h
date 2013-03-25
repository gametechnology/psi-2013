#include "Engine\Game.h"
#include "Irrlicht\irrlicht.h"

class ShipMover : public Component
{
public:
	ShipMover(Composite* parent);
	~ShipMover();

	void init(){};
	void draw(){};
	void update(){};
	void handleMessage(unsigned int message, void* data = 0){};
private:
};