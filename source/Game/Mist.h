#ifndef MIST
#define MIST

#include <Engine/GameObject.h>
#include <Engine/Core.h>

class Mist : public GameObject 
{
public:
	Mist(Core* core, irr::video::SColor color = irr::video::SColor(255, 0, 0, 0), float nearDistance = 100000, float farDistance = 1000000, irr::video::E_FOG_TYPE fogType = irr::video::EFT_FOG_LINEAR);
	virtual ~Mist();

	virtual void init();
	virtual void update();

	virtual void handleMessage(unsigned int, void* data = 0) { };

	void setColor(irr::video::SColor color);
	void setNearDistance(float nearDistance);
	void setFarDistance(float farDistance);
	void setFogType(irr::video::E_FOG_TYPE fogType);	
private:
	Core* _core;

	bool _valueChanged;
	irr::video::SColor _color;
	float _nearDistance;
	float _farDistance;
	irr::video::E_FOG_TYPE _fogType;
};
	
#endif