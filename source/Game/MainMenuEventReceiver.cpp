#include "MainMenuEventReceiver.h"

using namespace irr;
using namespace irr::gui;
using namespace irr::core;

MainMenuEventReceiver::MainMenuEventReceiver(SAppContext & context) : context(context) 
{
}

bool MainMenuEventReceiver::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_GUI_EVENT)
	{
		s32 id = event.GUIEvent.Caller->getID();
		char* ipadress;
		wchar_t* inputwchar;

		char* playername;
		wchar_t* namewchar;

		stringc portInput;
		short port;

		NetworkPacket packet(START_GAME);
		NetworkPacket namepacket(CLIENT_JOIN);
		NetworkPacket quitpacket(CLIENT_QUIT);
		NetworkPacket hostquitpacket(HOST_DISCONNECT);

		switch(event.GUIEvent.EventType)
		{ 
		case EGET_BUTTON_CLICKED:
			switch(id)
			{
			case JOIN_GAME_BUTTON:
				inputwchar = (wchar_t*)context.u_interface->getElementWithId(IP_INPUT_BOX)->getText();
				ipadress = (char*)malloc(wcslen(inputwchar)+ 1);
				wcstombs(ipadress, inputwchar, wcslen(inputwchar));
				ipadress[wcslen(inputwchar)] = 0;

				portInput = context.u_interface->getElementWithId(PORT_INPUT_BOX)->getText();
				port = atof(portInput.c_str());

				namewchar = (wchar_t*)context.u_interface->getElementWithId(NAME_INPUT_BOX)->getText();
				playername = (char*)malloc(wcslen(namewchar)+ 1);
				wcstombs(playername, namewchar, wcslen(namewchar));
				playername[wcslen(namewchar)] = 0;

				if((*ipadress == ' ' || *ipadress == NULL) || (*playername == ' ' || *playername == NULL) || (port == 0)){
					if(*ipadress == ' ' || *ipadress == NULL || port == 0)
						context.u_interface->addMessageBox(L"Messsage", L"Fill in an Ipadress and port", true, 1, 0);
					else
						context.u_interface->addMessageBox(L"Message", L"Fill in an Name", true, 1, 0);
				}else{
					Network::GetInstance()->InitializeClient(ipadress, port);
					if(!Network::GetInstance()->IsConnected()){
						context.u_interface->addMessageBox(L"Messsage", L"Not able to connect to server", true, 1, 0);
					}else{
						namepacket << namewchar << Network::GetInstance()->GetPacketTypeChecksum();
						Network::GetInstance()->SendPacket(namepacket, true);
					}
				}
				return true;
			case CREATE_GAME_BUTTON:
				namewchar = (wchar_t*)context.u_interface->getElementWithId(NAME_INPUT_BOX)->getText();;
				playername = (char*)malloc(wcslen(namewchar)+ 1);
				wcstombs(playername, namewchar, wcslen(namewchar));
				playername[wcslen(namewchar)] = 0;

				if(*playername == ' ' || *playername == NULL){
					context.u_interface->addMessageBox(L"Message", L"Fill in a name", true, 1, 0);
					return false;
				} else {
					Network::GetInstance()->InitializeServer();
					return true;
				}
			case START_GAME_BUTTON:
				Network::GetInstance()->SendServerPacket(packet, true);
				return true;
			case QUIT_GAME_BUTTON:
				if(!Network::GetInstance()->IsServer())
				{
					Network::GetInstance()->SendPacket(quitpacket, true);
				}
				else
				{
					Network::GetInstance()->SendServerPacket(hostquitpacket, true);
				}
				Network::GetInstance()->DeInitialize();
				return true;
			default:
				return false;
			}
			break;
		}
	}

	return false;
}
