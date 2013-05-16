#ifndef PLAYER_DATA
#define PLAYER_DATA

#include "Station.h"

struct PlayerData
{
public:
        bool            localFlag; //No need to sync this
        int             id;			//only sync this
        int             teamId;		
        wchar_t         *ipAddress;
        wchar_t         *name;
		Station :: StationType		*stationType;
};
#endif