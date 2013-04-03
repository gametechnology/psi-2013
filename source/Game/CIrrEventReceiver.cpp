/******************************************************************************
 * CIrrEventReceiver
 * =================
 *
 * CIrrEventReceiver has no restrictions. Credit would be appreciated, but not
 * required.
 ******************************************************************************/
 
#include <stdio.h>
#include "CIrrEventReceiver.h"

CIrrEventReceiver::CIrrEventReceiver()
{
	for(u32 i = 0; i < NUMBER_OF_KEYS; i++)
     Keys[i] = BS_UP;

	// Mouse Key States
	for(u32 i = 0; i < NUMBER_OF_MOUSE_BUTTONS; i++)
		 Mouse[i] = MBS_UP;
   
	MouseData.x = MouseData.y = MouseData.lx = MouseData.ly = MouseData.cx = MouseData.cy = 0;
	MouseData.wheelPos = MouseData.lwheelPos = 0;

	deltaMouseX = deltaMouseY = 0;

	mouseHasMoved = false; 

	generalCallerID = menuItemSelectedID = 0;

	menu = NULL;

	elementStatus[EGET_ELEMENT_FOCUS_LOST] = elementStatus[EGET_ELEMENT_FOCUSED] = 
	elementStatus[EGET_ELEMENT_HOVERED] = elementStatus[EGET_ELEMENT_LEFT] =
	elementStatus[EGET_ELEMENT_CLOSED] = elementStatus[EGET_BUTTON_CLICKED] = 
	elementStatus[EGET_SCROLL_BAR_CHANGED] = elementStatus[EGET_CHECKBOX_CHANGED] =
	elementStatus[EGET_LISTBOX_CHANGED] = elementStatus[EGET_LISTBOX_SELECTED_AGAIN] = 
	elementStatus[EGET_FILE_SELECTED] = elementStatus[EGET_FILE_CHOOSE_DIALOG_CANCELLED] =
	elementStatus[EGET_MESSAGEBOX_YES] = elementStatus[EGET_MESSAGEBOX_NO] = 
	elementStatus[EGET_MESSAGEBOX_OK] = elementStatus[EGET_MESSAGEBOX_CANCEL] = 
	elementStatus[EGET_EDITBOX_ENTER] = elementStatus[EGET_TAB_CHANGED] = 
	elementStatus[EGET_MENU_ITEM_SELECTED] = elementStatus[EGET_COMBO_BOX_CHANGED] = 
	elementStatus[EGET_SPINBOX_CHANGED] = FALSES; // << set all gui elements to false
}

CIrrEventReceiver::~CIrrEventReceiver() 
{ 
}

bool CIrrEventReceiver::isKeyUp(EKEY_CODE key)
{
   if (Keys[key] == BS_UP)
      return true;
   return false;
}

bool CIrrEventReceiver::isKeyDown(EKEY_CODE key)
{
   if (Keys[key] == BS_DOWN)
      return true;
   return false;
}

bool CIrrEventReceiver::isKeyPressed(EKEY_CODE key)
{
  if(Keys[key] == BS_PRESSED)
    return true;
  return false;
}

bool CIrrEventReceiver::isKeyReleased(EKEY_CODE key)
{
  if(Keys[key] == BS_RELEASED)
    return true;
  return false;
}

bool CIrrEventReceiver::isMouseButtonUp(mouseButton mb)
{
   if (Mouse[mb] == MBS_UP)
      return true;
   return false;
}

bool CIrrEventReceiver::isMouseButtonDown(mouseButton mb)
{
   if (Mouse[mb] == MBS_DOWN)
      return true;
   return false;
}

bool CIrrEventReceiver::isMouseButtonPressed(mouseButton mb)
{
   if (Mouse[mb] == MBS_PRESSED)
      return true;
   return false;
}

bool CIrrEventReceiver::isMouseButtonReleased(mouseButton mb)
{
   if (Mouse[mb] == MBS_RELEASED)
      return true;
   return false;
}

int CIrrEventReceiver::getDeltaMousePosX()
{
   return deltaMouseX;
}

int CIrrEventReceiver::getDeltaMousePosY()
{
   return deltaMouseY;
}

bool CIrrEventReceiver::mouseMoved()
{
   if(mouseHasMoved)
   {
      // set its state back to false.
      mouseHasMoved = false;
      return true;
   }

	 return false;
}

bool CIrrEventReceiver::getEventCallerByElement(EGUI_EVENT_TYPE guiEventType)
{
	if(elementStatus[guiEventType] == TRUES)
		return true;
	return false;
}

// This function will be used to get the ID of a gui element.
// This is a general function for getting the ID.
// It works for a lot of gui events but not all.
// Like getting the ID of the context menu wont work with this function
// Instead, use this function: getEventCallerOfMenuByID()
int CIrrEventReceiver::getEventCallerByID()
{
	return generalCallerID;
}

// meant for event: EGET_MENU_ITEM_SELECTED
// because IGUIContextMenu does not have the function: getID()
// in this line: event.GUIEvent.Caller->getID()
// So I had to make a custome one for the EGET_MENU_ITEM_SELECTED events.
int CIrrEventReceiver::getEventCallerOfMenuByID()
{
	return menuItemSelectedID;
}

// This is used so that the Key States will not be changed during execution of your Main game loop.
// Place this function at the END of your Main Loop.
void CIrrEventReceiver::startEventProcess()
{
	procesState = STARTED;
	
	// Keyboard Key States
	for(int i = 0; i < KEY_KEY_CODES_COUNT; i++)
	{
		if(Keys[i] == BS_RELEASED)
			 Keys[i] = BS_UP;

		if(Keys[i] == BS_PRESSED)
		 Keys[i] = BS_DOWN;
	}

	// Mouse Key States
	for(int i = 0; i < NUMBER_OF_MOUSE_BUTTONS; i++)
	{
		if(Mouse[i] == MBS_RELEASED)
			 Mouse[i] = MBS_UP;

		if(Mouse[i] == MBS_PRESSED)
		 Mouse[i] = MBS_DOWN;
	}

	elementStatus[EGET_ELEMENT_FOCUS_LOST] = elementStatus[EGET_ELEMENT_FOCUSED] = 
	elementStatus[EGET_ELEMENT_HOVERED] = elementStatus[EGET_ELEMENT_LEFT] =
	elementStatus[EGET_ELEMENT_CLOSED] = elementStatus[EGET_BUTTON_CLICKED] = 
	elementStatus[EGET_SCROLL_BAR_CHANGED] = elementStatus[EGET_CHECKBOX_CHANGED] =
	elementStatus[EGET_LISTBOX_CHANGED] = elementStatus[EGET_LISTBOX_SELECTED_AGAIN] = 
	elementStatus[EGET_FILE_SELECTED] = elementStatus[EGET_FILE_CHOOSE_DIALOG_CANCELLED] =
	elementStatus[EGET_MESSAGEBOX_YES] = elementStatus[EGET_MESSAGEBOX_NO] = 
	elementStatus[EGET_MESSAGEBOX_OK] = elementStatus[EGET_MESSAGEBOX_CANCEL] = 
	elementStatus[EGET_EDITBOX_ENTER] = elementStatus[EGET_TAB_CHANGED] = 
	elementStatus[EGET_MENU_ITEM_SELECTED] = elementStatus[EGET_COMBO_BOX_CHANGED] = 
	elementStatus[EGET_SPINBOX_CHANGED] = FALSES; // << set all gui elements to false
}

// This is used so that the Key States will not be changed during execution of your Main game loop.
// Place this at the very START of your Main Loop
void CIrrEventReceiver::endEventProcess()
{
	procesState = ENDED;
}

bool CIrrEventReceiver::OnEvent(const SEvent& event)
{
	switch (event.EventType) 
	{
		case EET_KEY_INPUT_EVENT:
    {
			 if(procesState == STARTED)
			 {
					if(event.KeyInput.PressedDown)
					{
						 // If key was not down before
						 if(Keys[event.KeyInput.Key] != BS_DOWN)
								Keys[event.KeyInput.Key] = BS_PRESSED; // Set key to Pressed
						 else
								Keys[event.KeyInput.Key] = BS_DOWN;

						 break;
					}
	        
					else
					{
						 // if the key is down
						 if(Keys[event.KeyInput.Key] != BS_UP)   
								Keys[event.KeyInput.Key] = BS_RELEASED; // Set key to Released
						 else
								Keys[event.KeyInput.Key] = BS_UP;

						 break;
					}
			 }
    }

		break;

    case EET_MOUSE_INPUT_EVENT:
    {
       switch(event.MouseInput.Event)
       {
					case EMIE_MOUSE_MOVED:
					{
						 deltaMouseX = event.MouseInput.X - MouseData.lx;
						 deltaMouseY = event.MouseInput.Y - MouseData.ly;

						 MouseData.x = event.MouseInput.X;
						 MouseData.y = event.MouseInput.Y;

						 MouseData.lx = MouseData.x;
						 MouseData.ly = MouseData.y;
	           
						 mouseHasMoved = true;

						 break;
					}
          
          case EMIE_MOUSE_WHEEL:
          {
             MouseData.lwheelPos = MouseData.wheelPos;
             MouseData.wheelPos += event.MouseInput.Wheel;
          
             break;
          }
          
          // Left Mouse Button Pressed
					case EMIE_LMOUSE_PRESSED_DOWN:
          {
             if(Mouse[MBLEFT] == MBS_UP || Mouse[MBLEFT] == MBS_RELEASED)
                Mouse[MBLEFT] = MBS_PRESSED;
             
             else
                Mouse[MBLEFT] = MBS_DOWN;

						 break;
          }

          // Left Mouse Button Rleased
					case EMIE_LMOUSE_LEFT_UP:
          {
             if(Mouse[MBLEFT] != MBS_UP)
                Mouse[MBLEFT] = MBS_RELEASED;

						 break;
          }

          // Middle Mouse Button Pressed
					case EMIE_MMOUSE_PRESSED_DOWN:
          {
             if(Mouse[MBMIDDLE] == MBS_UP || Mouse[MBMIDDLE] == MBS_RELEASED)
                Mouse[MBMIDDLE] = MBS_PRESSED;
             
             else
                Mouse[MBMIDDLE] = MBS_DOWN;

						 break;
          }

          // Middle Mouse Button Rleased
					case EMIE_MMOUSE_LEFT_UP:
          {
						if (Mouse[MBMIDDLE] != MBS_UP)
                Mouse[MBMIDDLE] = MBS_RELEASED;

						 break;
          }

          // Right Mouse Button Pressed
					case EMIE_RMOUSE_PRESSED_DOWN:
          {
             if (Mouse[MBRIGHT] == MBS_UP || Mouse[MBRIGHT] == MBS_RELEASED)
                Mouse[MBRIGHT] = MBS_PRESSED;

             else
                Mouse[MBRIGHT] = MBS_DOWN;

						 break;
          }

          // Right Mouse Button Rleased
					case EMIE_RMOUSE_LEFT_UP:
          {
             if(Mouse[MBRIGHT] != MBS_UP)
                Mouse[MBRIGHT] = MBS_RELEASED;

						 break;
          }

          default:
             break;
       }
    }

		break;

		case EET_GUI_EVENT:
		{
			generalCallerID = event.GUIEvent.Caller->getID();
			
			switch(event.GUIEvent.EventType)
			{
				case EGET_ELEMENT_FOCUS_LOST:
				case EGET_ELEMENT_FOCUSED:
				case EGET_ELEMENT_HOVERED:
				case EGET_ELEMENT_LEFT:
				case EGET_ELEMENT_CLOSED:
				case EGET_BUTTON_CLICKED:
				case EGET_SCROLL_BAR_CHANGED:
				case EGET_CHECKBOX_CHANGED:
				case EGET_LISTBOX_CHANGED:
				case EGET_LISTBOX_SELECTED_AGAIN:
				case EGET_FILE_SELECTED:
				case EGET_FILE_CHOOSE_DIALOG_CANCELLED:
				case EGET_MESSAGEBOX_YES:
				case EGET_MESSAGEBOX_NO:
				case EGET_MESSAGEBOX_OK:
				case EGET_MESSAGEBOX_CANCEL:
				case EGET_EDITBOX_ENTER:
				case EGET_TAB_CHANGED:
				case EGET_COMBO_BOX_CHANGED:
				case EGET_SPINBOX_CHANGED:
					elementStatus[event.GUIEvent.EventType] = TRUES;
				
				break;

				case EGET_MENU_ITEM_SELECTED:
					elementStatus[EGET_MENU_ITEM_SELECTED] = TRUES;
					menu = (IGUIContextMenu*)event.GUIEvent.Caller; 
					menuItemSelectedID = menu->getItemCommandId(menu->getSelectedItem());
				break;
			}
		}

		default:
			break;
	}
	
	return false;
}