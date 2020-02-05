#pragma once
class Bullet
{
public:
	Bullet(float x, float y, bool bMovingDown);
	~Bullet();
	void Update();
	float fPosX, fPosY;
	bool bDead = false;
private:
	bool bMoveDown;
};

