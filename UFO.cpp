#include "UFO.h"
#include <random>
#include "UGFW.h"
#include "UG_Defines.h"
#include "Bullet.h"
#include "Game.h"
#include "Sound.h"

UFO::UFO()
{
	//creates the ufo sprite
	iUfoID = UG::CreateSprite("./build/images/ufo.png", 500 / 8, 219 / 8, true);

	//generates a random number so the ufo starting position is either on the left or on the right edge of the screen
	iRandom = rand() % 100;
	if (iRandom < 50) {
		UG::SetSpritePosition(iUfoID, fPos1X, 660);
	}
	else {
		UG::SetSpritePosition(iUfoID, fPos2X, 660);
	}

	//generates a random number to set the points the ufo will give the player
	iRandom2 = rand() % 90;
	if (iRandom2 < 30) {
		iPoints = 50;
	}
	else if (iRandom2 >= 30 && iRandom2 < 60) {
		iPoints = 100;
	}
	else {
		iPoints = 150;
	}
}


UFO::~UFO()
{

}

//checks if the ufo has been hit by the player bullet comparing it's positions and size
//if it is hit sets the bullet to dead, adds the points to the game score, plays a sound and sets
//itself to dead
void UFO::Hit(Bullet* bullet, Game* game)
{
	if (bullet && !bullet->bDead) {
		if ((bullet->fPosY + 20) >= (700 - 219 / 8)) {
			if (iRandom < 50) {
				if (bullet->fPosX + 1.75f >= (fPos1X - 500/8) && bullet->fPosX - 1.75f <= (fPos1X + 500 / 8)) {
					bullet->bDead = true;
					game->score += iPoints;
					Sound::GetInstance()->PlaySound("./build/sounds/ufo_highpitch.wav");
					bDead = true;
				}
			}
			else {
				if (bullet->fPosX + 1.75f >= (fPos2X - 500/8) && bullet->fPosX - 1.75f <= (fPos2X + 500 / 8)) {
					bullet->bDead = true;
					game->score += iPoints;
					Sound::GetInstance()->PlaySound("./build/sounds/ufo_highpitch.wav");
					bDead = true;
				}
			}
		}
	}
}

void UFO::Update()
{
	//depending on the initial position moves to the left or to the right
	if (!bDead) {
		if (iRandom < 50) {
			fPos1X += 1.5f;
			UG::SetSpritePosition(iUfoID, fPos1X, 660);
		}
		else {
			fPos2X -= 1.5f;
			UG::SetSpritePosition(iUfoID, fPos2X, 660);
		}

	}
}

//draws ufo sprite
void UFO::Draw() {
	if (!bDead) {
		UG::DrawSprite(iUfoID);
	}
}
