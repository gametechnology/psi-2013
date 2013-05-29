#ifndef PSI_INPUT
#define PSI_INPUT

#define NUMBER_OF_KEYS irr::KEY_KEY_CODES_COUNT
#define NUMBER_OF_MOUSE_BUTTONS 3

#include <Irrlicht/irrlicht.h>

enum MouseButton
{
	LEFT_MB,
	MIDDLE_MB,
	RIGHT_MB
};

struct MouseData
{
	irr::s32 x, y;
	irr::f32 wheel;
};

class InputManager : public irr::IEventReceiver
{
public:
	InputManager();
	~InputManager();

	// Keyboard events.
	bool isKeyboardButtonDown(irr::EKEY_CODE key);

	// Mouse events.
	bool isMouseButtonDown(MouseButton mouseButton);

	bool mouseMoved();

	// Processing functions.
	void startInputProcess();
	void endInputProcess();

	/*
	* Add a custom event receiver to the input manager. 
	* For example an event receiver for GUI elements.
	*/
	void setCustomEventReceiver(IEventReceiver* eventReceiver);

	/*
	* Unset the custom event receiver. Call this when your custom event receiver is no longer needed or deleted.
	*/
	void unsetCustomEventReceiver();

	irr::s32 getMouseX();
	irr::s32 getMouseY();
	irr::f32 getMouseWheel();

	bool OnEvent(const irr::SEvent &event);
protected:
	bool keys[NUMBER_OF_KEYS];
	bool mouse[NUMBER_OF_MOUSE_BUTTONS];
	MouseData mouseData;

	IEventReceiver* customEventReceiver;

	bool mouseHasMoved;
};



#endif