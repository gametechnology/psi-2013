#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include "Engine/Entity.h"
#include "SendAndReceivePackets.h"
#include "NetworkInterface.h"

template<class T> class ObjectPool 
{
private:
	std::vector<T*> _objectList; 
	int _objectCount, _top;

	void FreeAll()
	{
		for(int i = 0; i < _objectCount; i++)
		{
			_objectList[i]->disable();
		}
	}

public:

	
	T* GetFreeObject()
	{
		for(int i = 0; i < _objectCount; i++)
		{
			if(!_objectList[i]->enabled)
			return _objectList[i];
		}
		return 0;
	}

	ObjectPool() {};

	ObjectPool(int count)
	{
		_objectList = std::vector<T*>();
		_objectCount = count;

		for(int i = 0; i < _objectCount; i++)
		{
			_objectList.push_back(new T());
		}

		FreeAll();
	}

	//currently only handles the lasers
	void sendObjectPacket()
	{
		if(Network::GetInstance()->IsServer())
		{
			if(dynamic_cast<Laser*>(this->_objectList[0]))
			{
				SendAndReceivePackets::sendLazerPacket(this->_objectList);
			}
		}
	}

	void receivePacket(NetworkPacket& packet)
	{
		if(!Network::GetInstance()->IsServer())
		{
			if(dynamic_cast<Laser*>(this->_objectCount[0]))
			{
				this->_objectList = SendAndReceivePackets::receiveLaserPacket(packet, this->_objectList);
			}
		}
	}

	virtual ~ObjectPool()
	{
		FreeAll();

		for(unsigned i = 0; i < _objectList.size(); i++)
		{
			delete _objectList[i];
		}
	}
};

#endif