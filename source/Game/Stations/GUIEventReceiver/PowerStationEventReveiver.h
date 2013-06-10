#ifndef PSI_MYEVENT_RECEIVER
#define PSI_MYEVENT_RECEIVER

#include <Irrlicht/irrlicht.h>

#include "../PowerStationData.h"

class PowerStationEventReveiver : public irr::IEventReceiver
{
public:

	enum
	{
		GUI_ID_LEAVE_BUTTON = 101,
		GUI_ID_POWER_DEFENCE,
		GUI_ID_POWER_HELM,
		GUI_ID_POWER_WEAPON,
		GUI_ID_POWER_NAVIGATION,

		//Scroll bars
		GUI_ID_SCROLL_BAR_DEFENCE,
		GUI_ID_SCROLL_BAR_HELM,
		GUI_ID_SCROLL_BAR_NAVIGATION,
		GUI_ID_SCROLL_BAR_WEAPON,

		//static texts
		GUI_ID_TEXT_DEFENCE,
		GUI_ID_TEXT_HELM,
		GUI_ID_TEXT_NAVIGATION,
		GUI_ID_TEXT_WEAPON,

		POWER_POOL_STATUS,
		SELECTED_STATION
	};



	irr::IrrlichtDevice *device;

	PowerStationEventReveiver(PowerStationData& context, irr::IrrlichtDevice *device);

	virtual bool OnEvent(const irr::SEvent& event);
private:
	PowerStationData & _context;
};

#endif