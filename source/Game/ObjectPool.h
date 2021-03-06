#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include "Engine/Entity.h"
#include "NetworkInterface.h"

template<class T> class ObjectPool 
{
private:
	std::vector<T*> _objectList; 
	int _objectCount;

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

	ObjectPool(Entity& parent, int count)
	{
		_objectList = std::vector<T*>();
		_objectCount = count;

		for(int i = 0; i < _objectCount; i++)
		{
			_objectList.push_back(new T());
			_objectList.back()->disable();
			parent.addChild(_objectList.back());
		}

		FreeAll();
	}

	//returns the list of the objects in the pool
	std::vector<T*> getAllObjects()
	{
		return this->_objectList;
	}

	//only sets the list when it is a client
	void setAllObjects(std::vector<T*> lazerList)
	{
		if(!Network::GetInstance()->IsServer())
		{
			this->_objectCount = lazerList.size();
			this->_objectList = lazerList;
		}
	}

	/* TODO:
	Make sure the destructor is only called once
	*/
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