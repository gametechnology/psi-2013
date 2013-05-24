#ifndef PLAYER_DATA
#define PLAYER_DATA

#include "Stations\Station.h"

struct PlayerData
{
public
		static int		uniqueId = 0;
        int				id;			//only sync this
        int				team_id;
		ENetPeer		peer;
        const wchar_t	*name;
		StationType		stationType;

		PlayerData( ) { };
		PlayerData( const wchar_t *name, int team_id, ENetPeer peer ) 
		{
			this ->	id				= uniqueId++;
			this -> name			= name;
			this -> team_id			= team_id;
			this -> peer			= peer;
			this -> stationType		= StationType :: ST_HALLWAY;
		}
};
#endif