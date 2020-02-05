#include "Player.h"
#include "UGFW.h"
#include "UG_Defines.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Game.h"
#include "Sound.h"

Player::Player()
{
	//Creates player's sprite and sets initial position
	iPlayerID = UG::CreateSprite("./build/images/player.png", 144 / 2.6f, 76 / 2.6f, true);
	UG::SetSpritePosition(iPlayerID, 203, 768 * 0.07f);
}


Player::~Player()
{
	bullet = nullptr;
}

//if there's no other player bullet in screen, player shoots when the function is called playing shoot sound
void Player::Shoot()
{
	if (!bullet) {
		bullet = new Bullet(fPlayerPosX, fPlayerPosY, false);

		Sound::GetInstance()->PlaySound("./build/sounds/shoot.wav");
	}
}

void Player::Update()
{
	//gets sprite position
	UG::GetSpritePosition(iPlayerID, fPlayerPosX, fPlayerPosY);

	//checks if the player is on the left edge, just letting it move left if it's not on it
	if (fPlayerPosX > ((166 / 2.6f) / 2)) {
		if (UG::IsKeyDown(UG::KEY_LEFT)) {
			UG::SetSpritePosition(iPlayerID, fPlayerPosX - 2, fPlayerPosY);
		}
	}

	//checks if the player is on the right edge, just letting it move right if it's not on it
	if (fPlayerPosX < (1024 - ((166 / 2.6f) / 2))) {
		if (UG::IsKeyDown(UG::KEY_RIGHT)) {
			UG::SetSpritePosition(iPlayerID, fPlayerPosX + 2, fPlayerPosY);
		}
	}

	//if there's a player bullet on the screen it updates it, but if it is dead it deletes it
	if (bullet) {
		bullet->Update();
		if (bullet->bDead) {
			delete bullet;
			bullet = nullptr;
		}
	}

	//calls player function to shoot
	if (UG::IsKeyDown(UG::KEY_SPACE)) {
		Shoot();
	}
}

//controls player collisions checking if any part of the enemies bullet is on the same position any player part is
//and if it is hit, lowers player lives, sets player position as the initial position and sets the enemy bullet to dead
void Player::Hit(Bullet* enemyBullet, Game* game)
{
	if (enemyBullet && !enemyBullet->bDead) {
		if ((enemyBullet->fPosX + 1.75f) >= (fPlayerPosX - 144 / 2.6f/2) && (enemyBullet->fPosX - 1.75f) < (fPlayerPosX + 144 / 2.6f / 2)
			&& enemyBullet->fPosY - 20 >= fPlayerPosY - 76 / 2.6f/2 && enemyBullet->fPosY - 20 <= fPlayerPosY + 76 / 2.6f/2) {
			game->lives--;
			UG::SetSpritePosition(iPlayerID, 203, 768 * 0.07f);
			enemyBullet->bDead = true;
		}
	}
}

//draws player
void Player::Draw() {
	UG::DrawSprite(iPlayerID);
}

