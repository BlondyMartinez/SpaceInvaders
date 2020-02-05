#include "Shield.h"
#include "ShieldPart.h"
#include "UGFW.h"
#include "UG_Defines.h"
#include <string>

float fx, fy;

Shield::Shield(float fposX, float fposY)
{
	//creates one shield of 3x4
	//depending on the part, changes the texture paths for each one of them, and depending on its position, rotates the sprite
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			switch (i) {
			case 0:
				Parts[i][j] = new ShieldPart("./build/images/square1.png", "./build/images/square2.png",
					"./build/images/square3.png", "./build/images/square4.png");
				if (j == 1 || j == 2) {
					//set to dead so they don't appear in the shield
					Parts[i][j]->bDead = true;
				}
				break;
			case 1:
				if (j == 0 || j == 3) {
					Parts[i][j] = new ShieldPart("./build/images/square1.png", "./build/images/square2.png",
						"./build/images/square3.png", "./build/images/square4.png");
				}
				else {
					Parts[i][j] = new ShieldPart("./build/images/bottomtriangle1.png", "./build/images/bottomtriangle2.png",
						"./build/images/bottomtriangle3.png", "./build/images/bottomtriangle4.png");
					if (j == 1) {
						UG::SetSpriteRotation(Parts[i][j]->i1LivePartID, 90);
						UG::SetSpriteRotation(Parts[i][j]->i2LivesPartID, 90);
						UG::SetSpriteRotation(Parts[i][j]->i3LivesPartID, 90);
						UG::SetSpriteRotation(Parts[i][j]->i4LivesPartID, 90);
					}
				}
				break;
			case 2:
				if (j == 1 || j == 2) {
					Parts[i][j] = new ShieldPart("./build/images/square1.png", "./build/images/square2.png",
						"./build/images/square3.png", "./build/images/square4.png");
				}
				else {
					Parts[i][j] = new ShieldPart("./build/images/toptriangle1.png", "./build/images/toptriangle2.png",
						"./build/images/toptriangle3.png", "./build/images/toptriangle4.png");
					if (j == 3) {
						UG::SetSpriteRotation(Parts[i][j]->i1LivePartID, 270);
						UG::SetSpriteRotation(Parts[i][j]->i2LivesPartID, 270);
						UG::SetSpriteRotation(Parts[i][j]->i3LivesPartID, 270);
						UG::SetSpriteRotation(Parts[i][j]->i4LivesPartID, 270);
					}
				}
				break;
			}

			//sets each part of the shield position
			Parts[i][j]->SetPosition((j + 1) * 20 + fposX, (i + 1) * 20 + fposY);
		}
	}
}


Shield::~Shield()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			delete Parts[i][j];
			Parts[i][j] = nullptr;
		}
	}
}

//sets the position for every sprite
void ShieldPart::SetPosition(float fX, float fY)
{
	UG::SetSpritePosition(i4LivesPartID, fX, fY);
	UG::SetSpritePosition(i3LivesPartID, fX, fY);
	UG::SetSpritePosition(i2LivesPartID, fX, fY);
	UG::SetSpritePosition(i1LivePartID, fX, fY);
}

//calls every part of the shield hit function
void Shield::Hit(Bullet * enemyBullet, Bullet * playerBullet)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			Parts[i][j]->Hit(enemyBullet, playerBullet);
		}
	}
}

//updates every part of the shield
void Shield::Update()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			Parts[i][j]->Update();
		}
	}
}
