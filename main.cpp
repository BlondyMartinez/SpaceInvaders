#include "Game.h"
#include <stdlib.h> 

void main() {
	Game game;
	srand(17);
	bool bSuccess = game.Initialise();
	if(bSuccess) {
		bool bStillRunning = true;

		while (bStillRunning) {
			bStillRunning = game.Update();
			game.Draw();
		}
	}

	game.Deinitialise();
}
