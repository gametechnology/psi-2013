#include "Game.h"
#include "Play.h"
#include "Entity.h"

int main()
{
	Game game = Game();
	Play* playScene = new Play();
	game.addScene(playScene);
	game.run();

	


	return 0;
}