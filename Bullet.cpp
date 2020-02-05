#include "Bullet.h"
#include "UGFW.h"

Bullet::Bullet(float x, float y, bool bMovingDown)
{
	//takes the position given and gets bMovingDown value
	bMoveDown = bMovingDown;
	fPosX = x;
	fPosY = y;
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	//if its moving down means enemies are shooting so the bullet goes down, else means the player is the one shooting so it goes up
	if (bMoveDown) {
		fPosY -= 4;
	}
	else {
		fPosY += 4;
	}

	//if the bullet reaches the edges of the screen it sets its bool to dead and deletes itself
	if (fPosY >= 768 || fPosX <= 0) {
		bDead = true;
	}

	//draws the bullet
	UG::DrawLine(fPosX, fPosY, fPosX, fPosY + 20, 3.5f,1);
}
