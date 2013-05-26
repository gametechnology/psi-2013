#ifndef PLAYER_DATA
#define PLAYER_DATA

#include "Stations\Station.h"

enum CLIENT_STATUS_UPDATE
{
	CHANGED_TEAM,
	LEFT_GAME
};

struct PlayerData
{
public:
		static int		uniqueId;
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
			this -> stationType		= StationType :: ST_NONE;
		}

		PlayerData( const wchar_t *name, int team_id ) 
		{
			this ->	id				= uniqueId++;
			this -> name			= name;
			this -> team_id			= team_id;
			this -> peer			= peer;
			this -> stationType		= StationType :: ST_NONE;
		}
};
#endif