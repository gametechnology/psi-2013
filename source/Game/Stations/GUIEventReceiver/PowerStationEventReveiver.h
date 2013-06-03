#ifndef PSI_MYEVENT_RECEIVER
#define PSI_MYEVENT_RECEIVER

#include <Irrlicht/irrlicht.h>

#include "../PowerStationData.h"

class PowerStationEventReveiver : public irr::IEventReceiver
{
public:
	irr::IrrlichtDevice *device;

	PowerStationEventReveiver(PowerStationData& context, irr::IrrlichtDevice *device);

	virtual bool OnEvent(const irr::SEvent& event);
private:
	PowerStationData & _context;
};

#endif