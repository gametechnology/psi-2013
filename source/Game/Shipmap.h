#ifndef SHIPMAP
#define SHIPMAP

class Shipmap
{
private:
	bool _map[5][10];
public:
	Shipmap();
	bool GetTile(int x, int y);
};

#endif