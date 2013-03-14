#ifndef Client_H
#define Client_H
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
#endif