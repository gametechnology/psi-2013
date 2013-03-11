#ifndef Net_H
#define Net_H
class Net{
	private:
		static BOOLEAN isServer;
		static std::string serverip;
		static BOOLEAN isrunning;
		static int playernumber;
		static irr::core::list<int> clientip;
		static void senderthread(void * var);
		static void  revieverthread(void * var);
	public:
		Net();		
		Net(std::string);
		void StartGame();
			
};
#endif