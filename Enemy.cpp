#include "Enemy.h"
#include "UGFW.h"
#include "UG_Defines.h"
#include "Bullet.h"
#include "Game.h"
#include "Sound.h"

Enemy::Enemy(const char* texturePath, const char* texturePath2, float width, float height, int iPointsGiven)
{
	//creates 2 sprites, one for each enemy animated sprite
	iEnemySprite = UG::CreateSprite(texturePath, width, height, true);
	iEnemySprite2 = UG::CreateSprite(texturePath2, width, height, true);

	//gets the amount of points an instance of enemy is going to give
	iPoints = iPointsGiven;

	//gets its size
	fWidth = width;
	fHeight = height;

	//creates death sprite
	iDeathID = UG::CreateSprite("./build/images/death.png", 273 / 6.5f, height, true);
}


Enemy::~Enemy()
{
}

//shoots a bullet when the function is called
void Enemy::Shoot()
{
	enemyBullet = new Bullet(fPosX, fPosY - fHeight / 2, true);
}

void Enemy::Update(Bullet* pBullet, Game* game)
{
	//if any enemy reaches this position sets bLose to true, and a lose screen will be shown
	if (fPosY <= 200) {
		game->bLose = true;
	}

	//if there is an enemy bullet on screen and it's not dead, updates it
	if (enemyBullet && !enemyBullet->bDead) {
		enemyBullet->Update();
	}

	//moves enemies after fSpeed time
	if (fTime >= fSpeed) {
		//sets time to 0
		fTime = 0;

		//plays a sound each time enemies move
		Sound::GetInstance()->PlaySound("./build/sounds/fastinvader2.wav");

		//sets bSprite1Drawn to its opposite value
		bSprite1Drawn = !bSprite1Drawn;

		//if the enemy is dead, sets bDeathShown to true
		if (bDead) bDeathShown = true;

		//if the enemies are moving down and they still haven't moved down, makes them move down
		//lowers fSpeed so every time they go down they move faster and sets bMovingRight to its opposite value
		if (Game::bMovingDown) {
			if (!bAlreadyDone) {
				fPosY -= 20;

				if (fSpeed > .2f) {
					fSpeed -= .1f;
				}

				bMovingRight = !bMovingRight;

				bAlreadyDone = true;
			}
		}

		//if it is not moving down, checks bMovingRight value and depending on it enemies move right or left
		if (!Game::bMovingDown) {
			if (bMovingRight) {
				fPosX += 10;
				iMoves++;
			}
			else {
				fPosX -= 10;
				iMoves--;
			}
			bAlreadyDone = false;
		}
	}

	if (!bDead) {
		//if it is not dead there is a player bullet on screen checks if the player bullet position and size coincide with the enemy position and size
		//if it does, sets player bullet to dead, adds points to the game score, lowers enemy count, plays death sounds and sets dead to
		//true
		if (pBullet) {
			if ((pBullet->fPosY + 20) >= (fPosY - fHeight / 2) && pBullet->fPosX + 1.75f > (fPosX - (fWidth / 2) - 2)
				&& pBullet->fPosX + 1.75f < (fPosX + (fWidth / 2) + 2) && (pBullet->fPosY + 20) <= (fPosY + fHeight / 2)) {
				pBullet->bDead = true;
				game->score += iPoints;
				game->enemyCount--;
				Sound::GetInstance()->PlaySound("./build/sounds/invaderkilled.wav");
				bDead = true;
			}
		}

		//depending on bSprite1Down value, it sets the position for either the first sprite or the second one
		if (!bSprite1Drawn) {
			UG::SetSpritePosition(iEnemySprite, fPosX, fPosY);
		}
		else {
			UG::SetSpritePosition(iEnemySprite2, fPosX, fPosY);
		}
	}
	else {													//if it is dead, shows death sprite
		UG::SetSpritePosition(iDeathID, fPosX, fPosY);
	}

	//adds deltatime to time value
	fTime += UG::GetDeltaTime();
}

//function to set enemy position
void Enemy::SetPosition(float fX, float fY)
{
	fPosX = fX;
	fPosY = fY;
}

//draws enemy sprites
void Enemy::Draw()
{
	if (!bDead) {
		if (!bSprite1Drawn) {
			UG::DrawSprite(iEnemySprite);
		}
		else {
			UG::DrawSprite(iEnemySprite2);
		}
	}
	else {
		UG::DrawSprite(iDeathID);
	}
}

//checks if the enemy is on the edges and if they haven't moved down already, sets the bool to true, if they did, to false
bool Enemy::OnEdge() {
	if (fPosX <= 24 || fPosX >= 1000) {
		if (!bAlreadyDone) {
			return true;
		}
	}
	return false;
}
