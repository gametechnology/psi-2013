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
		char			*name;
		StationType		stationType;

		PlayerData( ) { };
		PlayerData( char *name, int team_id, ENetPeer peer ) 
		{
			this ->	id				= uniqueId++;
			this -> name			= name;
			this -> team_id			= team_id;
			this -> stationType		= StationType :: ST_NONE;
		}

		PlayerData( char *name, int team_id ) 
		{
			this ->	id				= uniqueId++;
			this -> name			= name;
			this -> team_id			= team_id;
			this -> peer			= peer;
			this -> stationType		= StationType :: ST_NONE;
		}

		friend std :: ostream& operator << ( std :: ostream &os, const PlayerData &pd )
		{
			os << "name:\t" << pd.name << std :: endl;
			os << "id:\t" << pd.id << std :: endl;
			os << "\tteam id:\t" << pd.team_id << std :: endl;

			char *stationInfo;
			switch ( pd.stationType ) 
			{
				case -1:
					stationInfo = "Hallway";
					break;
				case 0:
					stationInfo = "Power Station";
					break;
				case 1:
					stationInfo = "Defence Station";
					break;
				case 2:
					stationInfo = "Weapon Station";
					break;
				case 3:
					stationInfo = "Helm Station";
					break;
				case 4:
					stationInfo = "Navigation Station";
					break;
			}
			os << "\tstation" << stationInfo << std :: endl;
			return os;
		}
};
#endif