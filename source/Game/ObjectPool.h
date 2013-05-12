#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include "Engine/Entity.h"

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

	virtual ~ObjectPool()
	{
		FreeAll();

		for(int i = 0; i < _objectList.size(); i++)
		{
			delete _objectList[i];
		}
	}
};

#endif