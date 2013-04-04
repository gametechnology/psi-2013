#pragma once
#include "Irrlicht\irrlicht.h"
#include "Irrlicht\driverChoice.h"
#include "Irrlicht\IEventReceiver.h"
using namespace irr;

class Input : public IEventReceiver
{
public:
	Input(void);
	~Input(void);

	virtual bool OnEvent(const SEvent& event);
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;

	static bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

