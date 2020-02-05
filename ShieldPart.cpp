#include "ShieldPart.h"
#include "UGFW.h"
#include "UG_Defines.h"
#include "Bullet.h"
#include <string>

ShieldPart::ShieldPart(const char* texture1, const char* texture2, const char* texture3, const char* texture4)
{
	//Creates the different sprites later used to change the look of each shield part depending on the lives it has
	i4LivesPartID = UG::CreateSprite(texture1, 20, 20, true);
	i3LivesPartID = UG::CreateSprite(texture2, 20, 20, true);
	i2LivesPartID = UG::CreateSprite(texture3, 20, 20, true);
	i1LivePartID = UG::CreateSprite(texture4, 20, 20, true);
}

ShieldPart::~ShieldPart()
{

}

void ShieldPart::Update()
{
	if (!bDead) {
		//changes sprite depending on the lives it has
		switch (iLives) {
		case 4:
			UG::DrawSprite(i4LivesPartID);
			UG::GetSpritePosition(i4LivesPartID, fPosX, fPosY);
			break;
		case 3:
			UG::DrawSprite(i3LivesPartID);
			break;
		case 2:
			UG::DrawSprite(i2LivesPartID);
			break;
		case 1:
			UG::DrawSprite(i1LivePartID);
			break;
		case 0:
			bDead = true;
			break;
		}
	}
}

//checks if the shield part has been hit by either enemy's or player's bullet comparing its positions and lowers its lives if it is hit
void ShieldPart::Hit(Bullet * enemyBullet, Bullet * playerBullet)
{
	if (!bDead) {
		if (playerBullet && !playerBullet->bDead) {
			if ((playerBullet->fPosY + 20) >= (fPosY - 10)) {
				if (playerBullet->fPosX + 1.75f >= (fPosX - 10) && playerBullet->fPosX - 1.75f <= (fPosX + 10)) {
					playerBullet->bDead = true;
					iLives--;
				}
			}
		}

		if (enemyBullet && !enemyBullet->bDead) {
			if ((enemyBullet->fPosY + 20) >= (fPosY - 10) && enemyBullet->fPosX + 1.75f > (fPosX - 10)
				&& enemyBullet->fPosX + 1.75f < (fPosX + 10) && (enemyBullet->fPosY - 20) <= fPosY + 10) {
				enemyBullet->bDead = true;
				iLives--;
			}
		}
	}
}


