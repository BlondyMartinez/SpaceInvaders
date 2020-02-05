#ifndef GAME_H
#define GAME_H
#include "Enemy.h"
#include "Player.h"
#include "Shield.h"
#include "ShieldPart.h"
#include "UFO.h"

enum GAME_STATE {
	MENU,
	PLAY,
	PAUSE,
	EXIT,
};

class Game
{
public:
	Game();
	~Game();

	static bool bMovingDown;
	bool Initialise();
	bool Update();
	void Draw();
	void Deinitialise();
	int score = 0;
	int lives = 3;
	bool bLose = false;
	int enemyCount;

private:
	int iBlondyID = 0;
	int iRandom, iRandom2;
	int iLive1ID = 0, iLive2ID=0, iLive3ID = 0, iLive4ID = 0, iLive5ID = 0, iLive6ID = 0, iLive7ID = 0, iLive8ID = 0;
	bool bPaused = false;
	float fTime = 0;
	Player* player;
	UFO* Ufo;
	GAME_STATE m_CurrentGameState;
	int m_Font;
	Enemy* enemies[5][11];
	int iBackgroundID = 0, iLogoID = 0, iButtonID = 0, iHighlightedButtonID= 0, iPausedBackgroundID = 0;
	float fScreenWidth = 1024, fScreenHeight = 768;
	Shield* shield[4];
	void NewWave();
	int iWaves = 0;
	void CreateNewSprites();
};

#endif // GAME_H
