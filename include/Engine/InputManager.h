/*
 *	https://github.com/gametechnology/psi-2013/wiki/InputManager
*/

#pragma once
#include "Irrlicht\irrlicht.h"
#include "Irrlicht\IEventReceiver.h"

using namespace irr;

#define NUMBER_OF_KEYBOARD_BUTTONS KEY_KEY_CODES_COUNT
#define NUMBER_OF_MOUSE_BUTTONS MOUSE_BUTTON_COUNT

enum ButtonState
{
	BS_UP,
	BS_DOWN,
	BS_PRESSED,
	BS_RELEASED
};

enum MouseButton
{
	LEFT_MB,
	MIDDLE_MB,
	RIGHT_MB,
	MOUSE_BUTTON_COUNT
};

struct MouseData
{
	s32 x, y;
	f32 wheel;
};

enum ProcessEventState
{
	STARTED,
	ENDED
};

class InputManager : public IEventReceiver
{
public:
	InputManager();
	~InputManager();

	// Keyboard events.
	bool isKeyboardButtonUp(EKEY_CODE key);
	bool isKeyboardButtonDown(EKEY_CODE key);
	bool isKeyboardButtonPressed(EKEY_CODE key);
	bool isKeyboardButtonReleased(EKEY_CODE key);

	// Mouse events.
	bool isMouseButtonUp(MouseButton mouseButton);
	bool isMouseButtonDown(MouseButton mouseButton);
	bool isMouseButtonPressed(MouseButton mouseButton);
	bool isMouseButtonReleased(MouseButton mouseButton);

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

	s32 getMouseX();
	s32 getMouseY();
	f32 getMouseWheel();

	bool OnEvent(const SEvent &event);
protected:
	ButtonState keys[NUMBER_OF_KEYBOARD_BUTTONS];
	ButtonState mouse[NUMBER_OF_MOUSE_BUTTONS];
	MouseData mouseData;
	ProcessEventState processState;

	IEventReceiver* customEventReceiver;

	bool mouseHasMoved;
};