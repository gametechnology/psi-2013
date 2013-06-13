#include "SectorManager.h"
#include "Messages.h"
#include <algorithm>
#include  "AsteroidSector.h"
#include  "NebulaSector.h"
#include  "SectorHomeBase.h"
#include  "BaseSector.h"

SectorManager::SectorManager(GalaxyMap* map,Ship* ship) : Component() {
	Network::GetInstance()->AddListener(PacketType::CLIENT_REQUEST_NEXTSECTOR,this);
	Network::GetInstance()->AddListener(PacketType::SERVER_SEND_NEXTSECTOR,this);
	Network::GetInstance()->AddListener(PacketType::CLIENT_REQUEST_BEGINSECTOR,this);

	_map=map;
	_ship=ship;
	this->_mapSector = _map->sectors[0];

}

void SectorManager::onAdd() {
	printf("\n[SectorManager] ONADD\n\n");
	if(Network::GetInstance()->IsServer()){
		this->_mapSector = SearchBeginMapSector(0);
		this->_mapSector->connectionSize = this->_mapSector->connections.size();
	}
	//Creating an first scene
	activeSceneName = "SectorHomeBase";
	//printf("[SectorManager] %s",_mapSector->skyboxTexture);
	if (_ship->getTeamId() == 1)
		this->getGame()->sceneManager->addScene(activeSceneName, new SectorHomeBase(this,_mapSector->skyboxTexture,2000.0,_mapSector->connections.size(), HOME_BLUE));
	else 
		this->getGame()->sceneManager->addScene(activeSceneName, new SectorHomeBase(this,_mapSector->skyboxTexture,2000.0,_mapSector->connections.size(), HOME_RED));

	
	
	Component::onAdd();
	init();
}
void SectorManager::init(){
	printf("\n[SectorManager] INIT\n\n");
	if(!Network::GetInstance()->IsServer()){
		//asking for fist sector
		NetworkPacket packet = NetworkPacket(PacketType::CLIENT_REQUEST_BEGINSECTOR);
		packet << 1; // TODO: pass the teamNumber through here
		Network::GetInstance()->SendPacket(packet,true);
	}

	Component::init();
}
void SectorManager::handleMessage(unsigned int message, void* data) {
	switch(message) {
		case NEXT_SECTOR: //Switch Sector 
	printf("[SectorManager] handleMessage NEXT_SECTOR\n");
			
			/////
			NetworkPacket sendpacket = NetworkPacket(PacketType::CLIENT_REQUEST_NEXTSECTOR);
			//we send a vector with 3 data in it. teamnumber, mapsector ID, wormHole ID
			irr::core::vector3df currentSectorVector = irr::core::vector3df(1,_mapSector->getId(),(int)data);
			sendpacket << currentSectorVector;
			Network::GetInstance()->SendPacket(sendpacket,false);
			/////


			break;
	}
	//delete data;
}



void SectorManager::HandleNetworkMessage(NetworkPacket packet){
	irr::core::vector3df packetdata;
	NetworkPacket sendToClientPacket = NetworkPacket(PacketType::SERVER_SEND_NEXTSECTOR);
	MapSector* tempSec;
	switch(packet.GetType()){
		case PacketType::CLIENT_REQUEST_BEGINSECTOR:
			printf("\n [SectorManager] CLIENT_REQUEST_BEGINSECTOR recieved \n\n");
			tempSec = SearchBeginMapSector(0);

			sendToClientPacket << *tempSec;//made operator;TODO: make extra parrameter for team filtering
			Network::GetInstance()->SendServerPacket(sendToClientPacket, true);
			if(Network::GetInstance()->IsServer()){
			printf("[SectorManager]  is server setBeginSector\n");
				tempSec->connectionSize = tempSec->connections.size();
				SetNextSector(*tempSec);

			}
			break;
		case PacketType::CLIENT_REQUEST_NEXTSECTOR:
			printf("\n[SectorManager] CLIENT_REQUEST_NEXTSECTOR recieved\n\n");
			packet >> packetdata;
			tempSec = SearchNextMapSector(packetdata.Y,packetdata.Z);
			//Send message to clients what there new sector is;
			
			sendToClientPacket << *tempSec;//made operator;TODO: make extra parrameter for team filtering
			Network::GetInstance()->SendServerPacket(sendToClientPacket, true);
			if(Network::GetInstance()->IsServer()){
			printf("[SectorManager]  is server setNextSector\n");
				tempSec->connectionSize = tempSec->connections.size();
				SetNextSector(*tempSec);

			}
			
			break;
		case PacketType::SERVER_SEND_NEXTSECTOR:
			printf("\n[SectorManager] SERVER_SEND_NEXTSECTOR recieved\n\n");
			packet >> *this->_mapSector;
			SetNextSector(*_mapSector);
			break;

	}
}
//looking through the map list and search the next sector in the conectionlist
MapSector* SectorManager::SearchNextMapSector(int currMapId, int connectionId){
				printf("[SectorManager] SearchNextMapSector( %i , %i)\n",currMapId,connectionId);
	//Determen which is the new sector
	int index = connectionId;
	std::vector<MapSector*>::iterator temp = SearchMapSector(currMapId)->connections.begin();//Looking through mapSectors 
	
	try{
		std::advance(temp,index);
	}catch(char * str){
		printf("[SectorManager] Something went wrong... : %c", str);
	}
	MapSector* tempSect = *temp;
	return tempSect;//change the _mapSector to the sector the data tells him to be
			
}
MapSector* SectorManager::SearchBeginMapSector(int teamID){
				printf("[SectorManager] SearchBeginMapSector()\n");
	//TODO: Search based on teamID to say which sector you need
	MapSector* temp;
	for (unsigned int i = 0; i < _map->sectors.size(); i++) {
		if(this->_ship->getTeamId() == 1){
			if(_map->sectors[i]->type == HOME_BLUE){
				//delete _mapSector;
				temp = _map->sectors[i];
			}
		}else{
			if(_map->sectors[i]->type == HOME_RED){
				//delete _mapSector;
				temp = _map->sectors[i];
			}
		}
	}

	return temp;
}
//gets a sector and loads the new scene etc. basicly splitting up the funtionality of handlemessage
void SectorManager::SetNextSector(MapSector& nextsector){
				printf("[SectorManager] SetNextSector\n");
	char * tempName = activeSceneName;
	printf("[SectorManager] MapID %i",nextsector.getId());
	// Checks if the scene is destroyed 
	if ( this->getGame()->sceneManager->destroyScene( tempName ) ) {
		
		// Turn Around the ship and place it closer to the center so it does not come in a endless loop of wormhole transitions
		_ship->transform->position->setLength( _ship->transform->position->getLength() * 0.8 );
		_ship->transform->rotation->rotateXZBy( PI * 180 );


		//Creates new Sector
		switch (nextsector.type){ 
			case EMPTY:
				//delete _currentSector;
				printf("[SectorTemplate] EMPTY \n");
				activeSceneName = "BaseSector";
				this->getGame()->sceneManager->addScene(activeSceneName,new BaseSector(this,nextsector.skyboxTexture,2000.0,nextsector.connectionSize));
				break;
			case ASTEROID:
				printf("[SectorTemplate] ASTEROID \n");
				//delete _currentSector;
				activeSceneName = "AsteroidSector";
				this->getGame()->sceneManager->addScene(activeSceneName,new AsteroidSector(this,nextsector.skyboxTexture,2000.0,nextsector.connectionSize));
				break;
			case NEBULA:
				printf("[SectorTemplate] NEBULA \n");
				//delete _currentSector;
				activeSceneName = "NebulaSector";
				this->getGame()->sceneManager->addScene(activeSceneName,new NebulaSector(this,nextsector.skyboxTexture,2000.0,nextsector.connectionSize));
				break;
			case SOLAR: 
				printf("[SectorTemplate] SOLAR \n");
				//delete _currentSector;
				activeSceneName = "BaseSector";
				this->getGame()->sceneManager->addScene(activeSceneName,new BaseSector(this,nextsector.skyboxTexture,2000.0,nextsector.connectionSize));
				break;
			case HOME_BLUE:
				printf("[SectorTemplate] HOME_BLUE \n");
				//delete _currentSector;
				activeSceneName = "SectorHomeBase";
						this->getGame()->sceneManager->addScene(activeSceneName,new SectorHomeBase(this,_mapSector->skyboxTexture,2000.0,_mapSector->connections.size(), HOME_BLUE));
				break;
			case HOME_RED:
				printf("[SectorTemplate] HOME_RED \n");
				//delete _currentSector;
				activeSceneName = "SectorHomeBase";
						this->getGame()->sceneManager->addScene(activeSceneName,new SectorHomeBase(this,_mapSector->skyboxTexture,2000.0,_mapSector->connections.size(), HOME_RED));
				break;
		}		
	}
}
//Search a mapSector out of the map, mostly used by the server when NetworkMessageHandled
MapSector* SectorManager::SearchMapSector(int currMapId){
	printf("[SectorManager] SearchMapSector \n");
	for (unsigned int i = 0; i < _map->sectors.size(); i++) {
		if(_map->sectors[i]->getId() == currMapId){
			//delete _mapSector;
			return _map->sectors[i];
			break;
		}
	}
}
Ship* SectorManager::getShip(){
	return _ship;
}
SectorManager::~SectorManager() {
	
}

//OPERATORS FOR MAPSECTORS
sf::Packet& operator <<(sf::Packet& out, MapSector& in)
{
	
	std::string tempC = in.skyboxTexture.c_str();
	printf("operator << skybox: %s \n",&tempC);
	int id = in.getId();
	return out << in.name << (int)in.type << in.explored << in.radius << in.distToBlueBase << in.skyboxTexture.c_str() << id <<in.connections.size() ;
	
}

sf::Packet& operator >>(sf::Packet& in, MapSector& out)
{
	int id;
	int temp;
	char tempC[64];
	in >> out.name >> temp >> out.explored >> out.radius >> out.distToBlueBase >> tempC >> id >> out.connectionSize ;
	out.type = (typeSector)temp;
	out.setId(id);
	printf("operator >> skybox: %s \n", &tempC);
	out.SetSkyboxTexture(tempC);
	return in;
}
