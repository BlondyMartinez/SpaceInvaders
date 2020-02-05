#pragma once
class ShieldPart;
class Bullet;
class Shield
{
public:
	Shield(float fposX, float fposY);
	~Shield();
	void Update();
	float fPosX, fPosY;
	void Hit(Bullet* enemyBullet, Bullet* playerBullet);
	ShieldPart* Parts[3][4];
};

