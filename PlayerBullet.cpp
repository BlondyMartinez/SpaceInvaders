#include "PlayerBullet.h"
#include "UGFW.h"
#include "UG_Defines.h"

PlayerBullet::PlayerBullet(Player* player)
{
	iBulletID = UG::CreateSprite("./build/images/playerbullet.jpg", 15,5, true);
	UG::SetSpritePosition(iBulletID, player->fPlayerPosX, (768 * 0.07f)+(76/2.6f));
}


PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Update()
{

}
