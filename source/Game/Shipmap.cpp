#include "Shipmap.h"

Shipmap::Shipmap()
{
	 bool map[5][10] = {
		{0,0,0,0,0,1,1,0,0,0},
		{0,0,0,0,0,0,1,0,0,0},
		{1,1,1,1,1,1,1,1,1,1},
		{0,0,0,1,0,0,1,0,0,0},
		{0,0,0,1,0,0,1,0,0,0}
	 };

	 for( int i = 0 ; i < 5 ; i++ )
		     for( int j = 0 ; j < 10 ; j++ )
		          _map[i][j] = map[i][j] ;
}

bool Shipmap::GetTile(int x, int y)
{
	return _map[x, y];
}