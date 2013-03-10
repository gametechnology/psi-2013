#ifndef Net_H
#define Net_H
class Net{
	private:
		static void senderthread(void * var);
		static void  revieverthread(void * var);
	public:
		Net(void *, void *);
			
};
#endif