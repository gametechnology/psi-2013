#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

template <class T>
class ArrayList
{
private:
	int size, cap;
	T* myList[5];

	void resize()
	{
		cap *= 2;
		T temp[cap];
		for (unsigned i = 0; i < size; i++)
		{
			temp[i] = *myList[i];
		}
		*myList = temp;
	}

public:
	void add(T addVariable)
	{
		if(size>= cap/2)
		{
			resize();
		}
		*myList[size] = addVariable;
		size++;
	}

	int getSize()
	{
		return size;
	}

	ArrayList()
	{
		size = 0;
		cap = 5;
	}

};

#endif