#pragma once
class Bullet;
class Game;
class UFO
{
public:
	UFO();
	~UFO();
	void Update();
	bool bDead = false;
	void Hit(Bullet* bullet, Game* game);
	void Draw();
	float fPos1X = 0, fPos2X = 1024;
private:
	int iUfoID = 0;
	int iRandom, iPoints, iRandom2;
};

