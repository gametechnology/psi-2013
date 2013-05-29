#include <Engine\InputManager.h>

using namespace irr;

InputManager::InputManager()
{
	// Default keyboard button states.
	for(u32 i = 0; i < NUMBER_OF_KEYS; i++)
		keys[i] = false;

	// Default mouse button states.
	for(u32 i = 0; i < NUMBER_OF_MOUSE_BUTTONS; i++)
		mouse[i] = false;

	// Default mouse position.
	mouseData.x = mouseData.y = 0;
	mouseData.wheel = 0;

	mouseHasMoved = false;

	customEventReceiver = NULL;
}

InputManager::~InputManager()
{

}

bool InputManager::isKeyboardButtonDown(EKEY_CODE key)
{
	if (keys[key])
		return true;
	return false;
}

bool InputManager::isMouseButtonDown(MouseButton mb)
{
	if (mouse[mb])
		return true;
	return false;
}

bool InputManager::mouseMoved()
{
	if(mouseHasMoved)
	{
		mouseHasMoved = false;
		return true;
	}
	return false;
}

s32 InputManager::getMouseX()
{
	return mouseData.x;
}

s32 InputManager::getMouseY()
{
	return mouseData.y;
}

f32 InputManager::getMouseWheel() 
{ 
	return mouseData.wheel; 
}

void InputManager::setCustomEventReceiver(IEventReceiver* eventReceiver)
{
	if(customEventReceiver != NULL)
	{
		printf("Custom receiver already set, unset first. \n");
	}
	customEventReceiver = eventReceiver;
}

void InputManager::unsetCustomEventReceiver()
{
	delete customEventReceiver;
	customEventReceiver = NULL;
}

bool InputManager::OnEvent(const SEvent &event)
{
	switch (event.EventType) 
	{
	case EET_KEY_INPUT_EVENT: // Keyboard event.
		keys[event.KeyInput.Key] = event.KeyInput.PressedDown;	
		break;

	case EET_MOUSE_INPUT_EVENT: // Mouse event.
		switch(event.MouseInput.Event)
		{
		case EMIE_MOUSE_MOVED: // Mouse movement.
			mouseData.x = event.MouseInput.X;
			mouseData.y = event.MouseInput.Y;
			mouseHasMoved = true;
			break;

		case EMIE_MOUSE_WHEEL: // Mouse wheel.
			mouseData.wheel += event.MouseInput.Wheel;
			break;

		case EMIE_LMOUSE_PRESSED_DOWN: // Left mouse button pressed.
		case EMIE_LMOUSE_LEFT_UP: // Left mouse button released
			mouse[LEFT_MB] = event.MouseInput.isLeftPressed();
			break;

		case EMIE_MMOUSE_PRESSED_DOWN: // Middle mouse button pressed.
		case EMIE_MMOUSE_LEFT_UP: // Middle mouse button released.
			mouse[MIDDLE_MB] = event.MouseInput.isMiddlePressed();
			break;

		case EMIE_RMOUSE_PRESSED_DOWN: // Right mouse button pressed.
		case EMIE_RMOUSE_LEFT_UP: // Right mouse button released.
			mouse[RIGHT_MB] = event.MouseInput.isRightPressed();
			break;

		default:
			break;

		}
		break;
	default:
		break;
	}

	if(customEventReceiver != NULL)
		if(customEventReceiver->OnEvent(event))
			return true;

	return false;
}