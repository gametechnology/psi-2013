#include <irrlicht.h>
#include "networking.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
	IrrlichtDevice *device;
	IGUIListBox*	listbox;
	ClientHandler*		client;
	IGUIEditBox* ipBox;
	IGUIEditBox* dataBox;
	IGUIButton* connect;
};

// Define some values that we'll use to identify individual GUI controls.
enum
{
	GUI_ID_CONNECT_BUTTON = 101,
	GUI_SEND_PACKET,
	GUI_ID_IPBAR
};

class MainEventReceiver : public IEventReceiver
{
public:
	MainEventReceiver(SAppContext& context) : Context(context) { }

	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Context.device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{
			case EGET_BUTTON_CLICKED:
				switch(id)
				{
				case GUI_ID_CONNECT_BUTTON:
					{
						// because the text of the GUI textbar is a w_char, we need to convert it to a std::string
						// therefore we need this magic code piece

						std::string* sOutput = new std::string();
						size_t* nbOfChar = new size_t; 
						char* cOut = new char[1023];
						size_t sizeInBytes = 1023;

						wcstombs_s( nbOfChar, cOut, sizeInBytes, Context.ipBox->getText(), 1023);
						*sOutput += cOut;

						delete nbOfChar;

						Context.client->setupClient(sOutput->data());

						delete[] cOut;
						delete sOutput;
					}
					break;
				case GUI_SEND_PACKET:
					{
						// because the text of the GUI textbar is a w_char, we need to convert it to a std::string
						// therefore we need this magic code piece

						std::string* sOutput = new std::string();
						size_t* nbOfChar = new size_t; 
						char* cOut = new char[1023];
						size_t sizeInBytes = 1023;

						wcstombs_s( nbOfChar, cOut, sizeInBytes, Context.dataBox->getText(), 1023);
						*sOutput += cOut;

						delete nbOfChar;

						Context.client->sendPacket(sOutput->data());

						delete[] cOut;
						delete sOutput;
					}
					break;
				default:
					return false;
				}
				break;

			case EGET_FILE_SELECTED:
				{
					// show the model filename, selected in the file dialog
					IGUIFileOpenDialog* dialog =
						(IGUIFileOpenDialog*)event.GUIEvent.Caller;
					Context.listbox->addItem(dialog->getFileName());
				}
				break;

			default:
				break;
			}
		}

		return false;
	}

private:
	SAppContext & Context;
};