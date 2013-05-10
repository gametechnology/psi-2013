#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include "Engine/Scene.h"

template<class OPDataType> class ObjectPool 
{
protected:
	OPDataType* _objectData;
	OPDataType** _objectFree;
	int _objectCount, _top;
	Scene* scene;

	void FreeAll()
	{
		int i = (_objectCount - 1);
		for(_top = 0; _top < _objectCount; _top++)
		{
			_objectFree[_top] = &_objectData[i--];
		}
	}

public:
	void FreeInstance(OPDataType* instance)
	{
		if((instance) && (_top < _objectCount) && (instance >= &_objectData[0]) &&
			(instance <= &_objectData[_objectCount-1]))
		{
			_objectFree[_top++] = instance;
		}
	}

	OPDataType* NewInstance()
	{
		if(_top > 0)
		{
			return _objectFree[--_top];
		}
		return 0;
	}

	ObjectPool() {};

	ObjectPool(int count, Scene* scene)
	{
		this->scene = scene;
		_objectData = new OPDataType[count];
		_objectFree = new OPDataType*[count];

		FreeAll();
	}

	virtual ~ObjectPool()
	{
		delete[] _objectData;
		delete[] _objectFree;
	}
};

#endif