#include "PowerStationEventReveiver.h"


PowerStationEventReveiver::PowerStationEventReveiver(PowerStationData& context, irr::IrrlichtDevice *device) : _context(context) 
{ 
	this->device = device; 
}

bool PowerStationEventReveiver::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_GUI_EVENT)
	{
		irr::s32 id = event.GUIEvent.Caller->getID();
		irr::gui::IGUIEnvironment* env = this->device->getGUIEnvironment();

		switch(event.GUIEvent.EventType)
		{
			/*
			If a scrollbar changed its scroll position, and it is
			'our' scrollbar (the one with id GUI_ID_SCROLL_BAR), then we update the power usage of that station.
			*/
		case irr::gui::EGET_SCROLL_BAR_CHANGED:
			irr::s32 pos;

			if(_context.selectedStation == 1)
			{
				pos = ((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();					
				_context.UpdatePowerUsage(ST_HELM, POWER_MAX - pos, false );
			}
			else if(_context.selectedStation == 2){
				pos = ((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
				_context.UpdatePowerUsage(ST_DEFENCE, POWER_MAX - pos, false );
			}
			else if(_context.selectedStation == 3){
				pos = ((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
				_context.UpdatePowerUsage(ST_NAVIGATION, POWER_MAX - pos, false );
			}
			else if(_context.selectedStation == 4){
				pos = ((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();

				((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller)->setPos( irr :: s32( ) );
				_context.UpdatePowerUsage(ST_WEAPON, POWER_MAX - pos, false );
			}
			break;

			//If the user selected a button, check to see which button was clicked.
		case irr::gui::EGET_BUTTON_CLICKED:
			switch(id)
			{
			case GUI_ID_LEAVE_BUTTON:
				this->device->closeDevice();
				return true;
			}
			break;
		}
	}

	return false;
}