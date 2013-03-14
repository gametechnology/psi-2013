#ifndef Net_H
#define Net_H
class Net{
	private:
		static BOOLEAN isServer;
		static std::string serverip;
		static BOOLEAN isrunning;
		static list<Client> clientlist;
		static Client mypc;
		static int lastpackageidrecieved;
		// 0 = connecting, 1 = inlobby, 2 = loading 3 = ingame
		static int stagegame;
		static void senderthread(void * var);
		static void  revieverthread(void * var);
		static Client * GetClientByIp(std::string);
	public:
		Net();		
		Net(std::string);
		void StartGame();
		
			
};
#endif