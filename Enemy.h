#pragma once
class Bullet;
class Game;

class Enemy
{
public:
	Enemy(const char* texturePath, const char* texturePath2, float width, float height, int iPointsGiven);
	~Enemy();
	void Shoot();
	bool bDead = false;
	void Update(Bullet* pBullet, Game* game);
	void SetPosition(float fX,float fY);
	float fPosX, fPosY, fWidth, fHeight;
	bool bDeathShown = false;
	bool OnEdge();
	void Draw();
	Bullet* enemyBullet;
private:
	bool bMovingRight = true, bAlreadyDone = false;
	int iMoves = 0;
	bool bMoveDown = false;
	float fTime = 0;
	int iEnemySprite = 0;
	int iEnemySprite2 = 0;
	int iDeathID = 0;
	int iPoints;
	bool bSprite1Drawn = true;
	float fSpeed = .7f;
};

