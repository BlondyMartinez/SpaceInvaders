#pragma once
class Bullet;
class Enemy;
class Game;
class Player
{
public:
	Player();
	~Player();
	void Shoot();
	void Update();
	void Hit(Bullet* enemyBullet, Game* game);
	void Draw();
	Bullet* bullet;
private:
	int iPlayerID = 0;
	float fPlayerPosX, fPlayerPosY;
};