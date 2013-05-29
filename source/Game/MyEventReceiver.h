#ifndef PSI_MYEVENT_RECEIVER
#define PSI_MYEVENT_RECEIVER


#include <Irrlicht/irrlicht.h>
/*
The Event Receiver is not only capable of getting keyboard and
mouse input events, but also events of the graphical user interface
(gui). There are events for almost everything: Button click,
Listbox selection change, events that say that a element was hovered
and so on. To be able to react to some of these events, we create
an event receiver.
We only react to gui events, and if it's such an event, we get the
id of the caller (the gui element which caused the event) and get
the pointer to the gui environment.
*/

#include "Stations/PowerStationData.h"

enum
{
	GUI_ID_LEAVE_BUTTON = 101,
	GUI_ID_POWER_DEFENCE,
	GUI_ID_POWER_HELM,
	GUI_ID_POWER_WEAPON,
	GUI_ID_POWER_NAVIGATION,
	GUI_ID_SCROLL_BAR
};

class MyEventReceiver : public irr::IEventReceiver
{
public:
	irr::IrrlichtDevice *device;

	MyEventReceiver(PowerStationData& context, irr::IrrlichtDevice *device);

	virtual bool OnEvent(const irr::SEvent& event);
private:
	PowerStationData & _context;
};

#endif