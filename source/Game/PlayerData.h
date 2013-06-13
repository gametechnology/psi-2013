#ifndef PLAYER_DATA
#define PLAYER_DATA

#include "Engine\INetworkListener.h"
#include "Engine\NetworkPacket.h"
#include "NetworkInterface.h"
#include "Stations\Station.h"

enum CLIENT_STATUS_UPDATE
{
	CHANGED_TEAM,
	LEFT_GAME,
	UPDATE_STATION
};

struct PlayerData
{
public:
		static int		uniqueId;
		int				pingCounter;
		int				id;			//only sync this
        int				team_id;		
		char			*name;
		StationType		stationType;
		bool			isConnected;


		PlayerData( ) { };
		
		PlayerData( char *name, int team_id ) 
		{
			SetValues( this -> uniqueId++, name, team_id );			
		}

		PlayerData( char *name, int team_id, int player_id ) 
		{
			SetValues( player_id, name, team_id );			
		}

		void SetValues( int player_id, char *name, int team_id )
		{
			this ->	id				= player_id;
			this -> name			= name;
			this -> team_id			= team_id;
			this -> stationType		= StationType :: ST_NONE;
			this -> isConnected		= true;

			if ( Network :: GetInstance( ) -> IsServer( ) )
			{
				pingCounter = 0;
			}
		}

		PlayerData* PlayerData :: operator = ( const PlayerData &pd )
		{
			return new PlayerData( pd.name, pd.team_id, pd.id );
		}

		friend std :: ostream& operator << ( std :: ostream &os, const PlayerData &pd )
		{
			os << "\tName:\t\t" << pd.name << std :: endl;
			os << "\tID:\t\t" << pd.id << std :: endl;
			os << "\tTeam id:\t" << pd.team_id << std :: endl;

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
			os << "\tStation:\t" << stationInfo << std :: endl;
			return os;
		}
};
#endif