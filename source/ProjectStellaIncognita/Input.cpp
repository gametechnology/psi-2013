#include "Input.h"

#define FORWARDINPUT false;

bool KeyIsDown[KEY_KEY_CODES_COUNT];

bool Input::OnEvent(const SEvent& event)
{
		// Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

    return !FORWARDINPUT;
}

bool Input::IsKeyDown(EKEY_CODE keyCode)
{
    return KeyIsDown[keyCode];
}

Input::Input()
{
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}