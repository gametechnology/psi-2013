#ifndef PLAYER_DATA
#define PLAYER_DATA

#include "Stations\Station.h"

struct PlayerData
{
public:
        int				id;			//only sync this
        int				team_id;		
        const wchar_t	*name;
		StationType		stationType;

		PlayerData( ) { };
		PlayerData( int id, const wchar_t *name, int team_id ) 
		{
			this ->	id				= id;
			this -> name			= name;
			this -> team_id			= team_id;
			this -> stationType		= StationType :: ST_HALLWAY;
		}
};
#endif