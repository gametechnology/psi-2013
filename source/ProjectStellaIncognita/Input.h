#ifndef INPUT_H
#define INPUT_H
/*
	Hugo Mater
*/
#include <irrlicht.h>

using namespace irr;

class Input : public IEventReceiver
{
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event);

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode);
    
    Input();

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};
#endif
