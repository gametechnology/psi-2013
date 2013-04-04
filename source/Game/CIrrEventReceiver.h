/******************************************************************************
 * CIrrEventReceiver
 * =================
 ******************************************************************************/
 
#ifndef __CIRREVENTRECEIVER_H__
#define __CIRREVENTRECEIVER_H__

#include "Irrlicht\irrlicht.h"
#include <iostream>
#include <sstream>

using namespace irr;
using namespace core;
using namespace gui;
using namespace io;
using namespace std;

#define NUMBER_OF_KEYS KEY_KEY_CODES_COUNT
#define NUMBER_OF_MOUSE_BUTTONS 2
#define NUMBER_OF_GUI_ELEMENTS 21

enum buttonState
{
	BS_UP,
	BS_DOWN,
	BS_PRESSED,
	BS_RELEASED
};

enum mouseButton
{
	MBLEFT,
	MBMIDDLE,
	MBRIGHT
};

enum mouseButtonState
{
	MBS_UP,
	MBS_DOWN,
	MBS_PRESSED,
	MBS_RELEASED
};

struct mouseInformation
{
	s32 x, y, lx, ly, cx, cy;
	f32 wheelPos, lwheelPos;
};

// Enumeration for Event Handling State.
enum ProcessEventState
{
	STARTED, 
	ENDED
};

// this enum is for setting the gui events to true or false.
enum ElementStatus
{
	TRUES,
	FALSES
};

class CIrrEventReceiver : public IEventReceiver
{
	public:
		CIrrEventReceiver();
		~CIrrEventReceiver();

		// GUI events:
		bool getEventCallerByElement(EGUI_EVENT_TYPE);

		int getEventCallerOfMenuByID();
		int getEventCallerByID();

		// Keyboard events:
    bool isKeyUp(EKEY_CODE key);
    bool isKeyDown(EKEY_CODE key);
    bool isKeyPressed(EKEY_CODE key);
    bool isKeyReleased(EKEY_CODE key);
    
    // Mouse events:
		bool isMouseButtonUp(mouseButton mb);
		bool isMouseButtonDown(mouseButton mb);
    bool isMouseButtonPressed(mouseButton mb);
    bool isMouseButtonReleased(mouseButton mb);

    bool mouseMoved();
    
    // Processing functions:
    void startEventProcess();
    void endEventProcess();

    int getDeltaMousePosX();
    int getDeltaMousePosY();
    
    inline int getMouseX() { return MouseData.x; }
    inline int getMouseY() { return MouseData.y; }
    inline int getLastMouseX() { return MouseData.lx; }
    inline int getLastMouseY() { return MouseData.ly; }

    inline s32 getDeltaMouseX()
    {
       s32 a = MouseData.x - MouseData.lx;
       return (s32)(a < 0 ? -a : a);
    }

    inline s32 getDeltaMouseY()
    {
       s32 a = MouseData.y - MouseData.ly;
       return (s32)(a < 0 ? -a : a);
    }

    inline u32 getClickedMouseX() { return MouseData.cx; }
    inline u32 getClickedMouseY() { return MouseData.cy; }

    inline f32 getMouseWheelPosition() { return MouseData.wheelPos; }
    inline f32 getLastMouseWheelPosition() { return MouseData.lwheelPos; }

    inline f32 getDeltaMouseWheelPosition()
    {
       f32 a = MouseData.wheelPos - MouseData.lwheelPos;
       return (f32)(a < 0 ? -a : a);
    }


		bool OnEvent(const SEvent& event);

	protected:
		buttonState Keys[NUMBER_OF_KEYS];
    mouseButtonState Mouse[NUMBER_OF_MOUSE_BUTTONS];
    ElementStatus elementStatus[NUMBER_OF_GUI_ELEMENTS];
    mouseInformation MouseData;
    ProcessEventState procesState;
    
		IGUIContextMenu* menu;
		s32 menuItemSelectedID;
		s32 generalCallerID;

    int deltaMouseX;
    int deltaMouseY;
    
    bool mouseHasMoved;
    
    // for converting anything to string (good for debug to console).
    template <class T>
    inline std::string ToString(const T& t)
    {
       std::stringstream ss;
       ss << t;
       return ss.str();
    } 
};

#endif /* __CIRREVENTRECEIVER_HEADER__ */