#pragma once
class Bullet;
class ShieldPart
{
public:
	ShieldPart(const char* texture1, const char* texture2, const char* texture3, const char* texture4);
	~ShieldPart();
	void Update();
	bool bDead = false;
	void SetPosition(float fX, float fY);
	void Hit(Bullet* enemyBullet, Bullet* playerBullet);
	int i4LivesPartID = 0, i3LivesPartID = 0, i2LivesPartID = 0, i1LivePartID = 0;
private:
	float fPosY, fPosX;
	int iLives = 4;
};

