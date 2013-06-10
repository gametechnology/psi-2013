#ifndef ISHIPLISTENER
#define ISHIPLISTENER

enum ShipMessage {
	LEAVESTATION = 0
};


class IShipListener
{
public:
	virtual void handleShipMessage(ShipMessage message) = 0;

	~IShipListener()
	{
	}
};

#endif