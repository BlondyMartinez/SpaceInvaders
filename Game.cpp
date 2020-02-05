#include "Game.h"
#include "UGFW.h"
#include "UG_Defines.h"
#include <string>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include "Sound.h"

bool Game::bMovingDown = false;

Game::Game()
{
	m_CurrentGameState = MENU;
}

Game::~Game()
{
	player = nullptr;
	Ufo = nullptr;
}

bool Game::Initialise()
{
	bool bSuccess = UG::Create(1024, 768, false, "Space Invaders", 100, 100);

	if (bSuccess) {
		//calls a function that creates sprites used in this cpp
		CreateNewSprites();

		//Adds the font I'll be using in game.
		m_Font = UG::AddFont("./build/fonts/font.ttf", 30);
		UG::SetFont(m_Font);

		//Adds the four shields and sets their positions.
		for (int k = 0; k < 4; k++) {
			shield[k] = new Shield((float)(k + 1) * 200 - 40, 80);
		}

		//Creates sound class instance and loads all the sounds the game will use
		Sound::CreateInstance();
		Sound::GetInstance()->LoadSound("./build/sounds/invaderkilled.wav");
		Sound::GetInstance()->LoadSound("./build/sounds/fastinvader2.wav");
		Sound::GetInstance()->LoadSound("./build/sounds/ufo_highpitch.wav");
		Sound::GetInstance()->LoadSound("./build/sounds/shoot.wav");
	}

	return bSuccess;
}

bool Game::Update()
{
	UG::ClearScreen();

	switch (m_CurrentGameState) {
	case MENU:
		//Gets mouse position so I can checked wether or not is the same as the button sprite, and clicking, changes the state to PLAY.
		int iMousePosX, iMousePosY;
		UG::GetMousePos(iMousePosX, iMousePosY);

		if (iMousePosX > (fScreenWidth / 2 - 653 * .6f) && iMousePosX < (fScreenWidth / 2 + 653 * .6f)
			&& iMousePosY >(fScreenHeight * 0.4f - 40 * .6f) && iMousePosY < (fScreenHeight *0.4f + 40 * .6f)) {
			UG::DrawSprite(iHighlightedButtonID);

			if (UG::IsMouseButtonDown(0)) {
				//Creates a new wave and sets the waves count to 0
				iWaves = 0;
				lives = 3;
				score = 0;
				NewWave();
				m_CurrentGameState = PLAY;
			}
		}

		//Closes the game
		if (UG::IsKeyDown(UG::KEY_ESCAPE)) {
			UG::Close();
		}

		break;
	case PLAY:
		//updates player
		player->Update();

		//generates a random number for the ufo to appear
		iRandom2 = rand() % 10000;
		if (iRandom2 >= 9999) {
			Ufo = new UFO();
		}

		//checks if there's an ufo on screen and if it's not dead to update it and check if the player's bullet hits it.
		if (Ufo && !Ufo->bDead) {
			Ufo->Update();
			Ufo->Hit(player->bullet, this);
		}

		//checks if an enemy is on the edge of the screen to set its movement to down
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 11; j++) {
				if (enemies[i][j]->OnEdge()) {
					Game::bMovingDown = true;
				}
			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 11; j++) {
				//Generates a random number so the enemies shoot if the number is bigger to the one specified.
				iRandom = rand() % 10000;

				//If the death sprite has not been shown updates the player and  makes it shoot with the random number generated above
				if (!enemies[i][j]->bDeathShown) {
					enemies[i][j]->Update(player->bullet, this);

					if (i == 0 && !enemies[0][j]->bDead && iRandom >= 9997) {
						enemies[0][j]->Shoot();
					}
					if (i != 0 && enemies[i - 1][j]->bDead && iRandom >= 9997) {
						enemies[i][j]->Shoot();
					}
				}

				//checks if the player has been hit by the enemy bullet
				player->Hit(enemies[i][j]->enemyBullet, this);

				//checks if the shields have been hit by the enemy or player bullets
				for (int k = 0; k < 4; k++) {
					shield[k]->Hit(enemies[i][j]->enemyBullet, player->bullet);
				}
			}
		}

		//sets movement of the enemies down to false
		if (Game::bMovingDown) {
			Game::bMovingDown = false;
		}

		//pauses the game
		if (UG::WasKeyPressed(UG::KEY_P)) {
			m_CurrentGameState = PAUSE;
		}

		//changes state to exit
		if (UG::IsKeyDown(UG::KEY_ESCAPE)) {
			m_CurrentGameState = EXIT;
		}

		//if the enemies count reaches 0 then calls newwave to start a new wave
		if (enemyCount == 0) {
			iWaves++;									//Adds one to the waves count.
			NewWave();
			if (lives < 8) {							//In case lives are lower than 8, one is added
				lives++;
			}
		}

		//checks if lifes is = 0 to set lose to true
		if (lives == 0) {
			bLose = true;
		}

		//checks if lose is true and depending on player's choice the game is restarted creating a newwave, setting its count to 0 and setting lives to 3
		//or the state changes to menu
		if (bLose) {
			if (UG::IsKeyDown(UG::KEY_Y)) {
				lives = 3;
				iWaves = 0;
				score = 0;
				NewWave();
			}
			else if (UG::IsKeyDown(UG::KEY_N)) {
				m_CurrentGameState = MENU;
			}
		}
		break;
	case PAUSE:
		//changes state to play when p is pressed
		if (UG::WasKeyPressed(UG::KEY_P)) {
			m_CurrentGameState = PLAY;
		}
		break;
	case EXIT:
		//changes the state to menu or play depending on the player's choice
		if (UG::IsKeyDown(UG::KEY_Y)) {
			m_CurrentGameState = MENU;
		}
		else if (UG::IsKeyDown(UG::KEY_N)) {
			m_CurrentGameState = PLAY;
		}
		break;
	}

	bool bStillRunning = UG::Process();

	return bStillRunning;
}

void Game::Draw()
{
	UG::DrawSprite(iBackgroundID);
	if (m_CurrentGameState == MENU) {
		//draws menu sprites
		UG::DrawSprite(iBlondyID);
		UG::DrawSprite(iLogoID);

		UG::DrawSprite(iButtonID);
	}
	else {

		//draws lives text
		UG::DrawString("LIVES", 660, 720, 0);

		//draws in game things + pause and quit screen
		switch (lives) {
		case 8:
			UG::DrawSprite(iLive8ID);
			break;
		case 7:
			UG::DrawSprite(iLive7ID);
			break;
		case 6:
			UG::DrawSprite(iLive6ID);
			break;
		case 5:
			UG::DrawSprite(iLive5ID);
			break;
		case 4:
			UG::DrawSprite(iLive4ID);
			break;
		case 3:
			UG::DrawSprite(iLive3ID);
			break;
		case 2:
			UG::DrawSprite(iLive2ID);
			break;
		case 1:
			UG::DrawSprite(iLive1ID);
			break;
		}

		//draws the bottom line
		UG::DrawLine(0, .01f, fScreenWidth, 0.1f, 10, 1, UG::SColour(0x0, 0xFF, 0x0, 0xFF));

		//draws the ufo
		if (Ufo) {
			Ufo->Draw();
		}

		//draws the player
		player->Draw();

		//draws the shields
		for (int z = 0; z < 4; z++) {
			shield[z]->Update();
		}

		//draws score text and score value on screen
		UG::DrawString("SCORE ", 10, 720, 0);
		std::string Text = std::to_string(score);
		UG::DrawString(Text.c_str(), 130, 720, 0, UG::SColour(0x0, 0xFF, 0x0, 0xFF));

		//draws enemies 
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 11; j++) {
				if (!enemies[i][j]->bDeathShown) {
					enemies[i][j]->Draw();
				}
			}
		}

		//draws lose screen text and paused background
		if (bLose) {
			UG::DrawString("PLAY AGAIN? Y/N", 450, 384, 2);

			UG::DrawSprite(iPausedBackgroundID);
		}

		//draws paused text and background
		if (m_CurrentGameState == PAUSE) {
			UG::DrawString("PAUSED", 450, 384, 2);

			UG::DrawSprite(iPausedBackgroundID);
		}

		//draws exit text and background
		if (m_CurrentGameState == EXIT) {
			UG::DrawString("QUIT GAME? Y/N", 400, 384, 2);

			UG::DrawSprite(iPausedBackgroundID);
		}
	}

}

void Game::Deinitialise()
{
	//deletes all the enemies
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 11; j++) {
			delete enemies[i][j];
			enemies[i][j] = nullptr;
		}
	}

	//deletes all the shields
	for (int k = 0; k < 4; k++) {
		delete shield[k];
		shield[k] = nullptr;
	}

	//deletes sound instance
	Sound::Delete();

	UG::Dispose();
}

void Game::NewWave()
{
	bLose = false;								//Sets lose to false.

	enemyCount = 55;							//Sets enemy count back to 55
	for (int i = 0; i < 5; i++) {				//Creates the 55 enemies adding the textures path, size and the points
		for (int j = 0; j < 11; j++) {			//the different enemies types give and sets their starting position lowering
			switch (i) {						//it each time a new wave starts. 
			case 0:
			case 1:
				enemies[i][j] = new Enemy("./build/images/medusa1.png", "./build/images/medusa2.png", 244 / 6.5f, 167 / 6.5f, 10);
				break;
			case 2:
			case 3:
				enemies[i][j] = new Enemy("./build/images/enemy1.png", "./build/images/enemy2.png", 229 / 6.5f, 167 / 6.5f, 20);
				break;
			case 4:
				enemies[i][j] = new Enemy("./build/images/octopus2.png", "./build/images/octopus1.png", 168 / 6.5f, 167 / 6.5f, 40);
				break;
			}

			enemies[i][j]->SetPosition((float)(j + 1) * 50 + 210, (float)(i + 1) * 55 + 335 - (iWaves * 20));
		}
	}

	//Adds the player.
	player = new Player();
}

void Game::CreateNewSprites()
{
	//Creates all static sprites setting their texture path, size, position and layer.
	iBackgroundID = UG::CreateSprite("./build/images/background.jpg", fScreenWidth, fScreenHeight, true);
	UG::SetSpritePosition(iBackgroundID, fScreenWidth / 2, fScreenHeight / 2);

	iPausedBackgroundID = UG::CreateSprite("./build/images/pause.png", fScreenWidth, fScreenHeight, true);
	UG::SetSpritePosition(iPausedBackgroundID, fScreenWidth / 2, fScreenHeight / 2);
	UG::SetSpriteLayer(iPausedBackgroundID, 1);

	iLogoID = UG::CreateSprite("./build/images/logo.png", 892 * .6f, 631 * .6f, true);
	UG::SetSpritePosition(iLogoID, fScreenWidth / 2, fScreenHeight *.7f);

	iBlondyID = UG::CreateSprite("./build/images/blondysymbol.png", 300, 300, true);
	UG::SetSpritePosition(iBlondyID, fScreenWidth / 2, 130);

	iButtonID = UG::CreateSprite("./build/images/button.png", 653 * .6f, 40 * .6f, true);
	UG::SetSpritePosition(iButtonID, fScreenWidth / 2, fScreenHeight *0.4f);

	iHighlightedButtonID = UG::CreateSprite("./build/images/button_highlighted.png", 653 * .6f, 40 * .6f, true);
	UG::SetSpritePosition(iHighlightedButtonID, fScreenWidth / 2, fScreenHeight * .4f);

	iLive1ID = UG::CreateSprite("./build/images/1life.png", 544 / 2.5f, 152 / 2.5f, true);
	UG::SetSpritePosition(iLive1ID, 870, 710);

	iLive2ID = UG::CreateSprite("./build/images/2lifes.png", 544 / 2.5f, 152 / 2.5f, true);
	UG::SetSpritePosition(iLive2ID, 870, 710);

	iLive3ID = UG::CreateSprite("./build/images/3lifes.png", 544 / 2.5f, 152 / 2.5f, true);
	UG::SetSpritePosition(iLive3ID, 870, 710);

	iLive4ID = UG::CreateSprite("./build/images/4lifes.png", 544 / 2.5f, 152 / 2.5f, true);
	UG::SetSpritePosition(iLive4ID, 870, 710);

	iLive5ID = UG::CreateSprite("./build/images/5lifes.png", 544 / 2.5f, 152 / 2.5f, true);
	UG::SetSpritePosition(iLive5ID, 870, 730);

	iLive6ID = UG::CreateSprite("./build/images/6lifes.png", 544 / 2.5f, 152 / 2.5f, true);
	UG::SetSpritePosition(iLive6ID, 870, 730);

	iLive7ID = UG::CreateSprite("./build/images/7lifes.png", 544 / 2.5f, 152 / 2.5f, true);
	UG::SetSpritePosition(iLive7ID, 870, 730);

	iLive8ID = UG::CreateSprite("./build/images/8lifes.png", 544 / 2.5f, 152 / 2.5f, true);
	UG::SetSpritePosition(iLive6ID, 870, 730);
}
