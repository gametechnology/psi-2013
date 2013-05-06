#ifndef MIST
#define MIST

#include "Engine/Entity.h"
#include "Engine/Game.h"

class Mist : public Entity {
public:
	Mist(video::SColor color = video::SColor(255, 0, 0, 0), float nearDistance = 100000, float farDistance = 1000000, video::E_FOG_TYPE fogType = video::EFT_FOG_LINEAR);
	virtual void		init();
	virtual void		update();
	void				SetColor(video::SColor color);
	void				SetNearDistance(float nearDistance);
	void				SetFarDistance(float farDistance);
	void				SetFogType(video::E_FOG_TYPE fogType);
	virtual ~Mist();
private:
	bool				_valueChanged;
	video::SColor		_color;
	float				_nearDistance;
	float				_farDistance;
	video::E_FOG_TYPE	_fogType;
};
	
#endif