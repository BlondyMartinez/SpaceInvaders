#pragma once
#include "Player.h"

class PlayerBullet
{
public:
	PlayerBullet(Player* player);
	~PlayerBullet();
	void Update();
	int iBulletID = 0;
	float fPosX, fPosY;
	Player* player;
};

