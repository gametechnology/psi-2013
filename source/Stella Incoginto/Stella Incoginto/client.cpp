#include "stdafx.h"
using namespace irr;
using namespace core;
class Client
{
	public:
		int Ipadress;
		int lastpackageid;
		list<int> lastimportantsendpackages;
		list<int> lastimportantrecievedpackages;
		int Playernumber;
		std::string Name;
		Client(int, int ,std::string);
};

Client::Client(int ipadress,int playernumber,std::string name)
{
	Ipadress = ipadress;
	Playernumber = playernumber;
	Name = name;
}