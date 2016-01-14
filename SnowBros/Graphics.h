#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "Globals.h"
class Animation;

class Graphics{
public:
	Graphics();
	void LoadGraphics();
	void UnloadGraphics();
public:
	//Textures
	SDL_Texture* playerGraphics = nullptr;
	SDL_Texture* enemyGraphics = nullptr;
	SDL_Texture* miscGraphics = nullptr;

	//Player
	SDL_Rect playerIdleLeft;
	SDL_Rect playerIdleRight;
	Animation playerMoveLeft;
	Animation playerMoveRight;
	Animation playerFastLeft;
	Animation playerFastRight;
	Animation playerJumpLeft;
	Animation playerJumpRight;
	SDL_Rect playerFallingLeft;
	SDL_Rect playerFallingRight;
	Animation playerShootingLeft;
	Animation playerShootingRight;
	Animation playerChangingLevel;
	Animation playerLandingLeft;
	Animation playerLandingRight;
	Animation playerPushingLeft;
	Animation playerPushingRight;
	Animation playerFastPushingLeft;
	Animation playerFastPushingRight;
	SDL_Rect playerLastPushLeft;
	SDL_Rect playerLastPushRight;
	Animation playerInBall;
	Animation playerDying;
	SDL_Rect playerDestroying1;
	SDL_Rect playerDestroying2;
	SDL_Rect playerDestroying3;
	SDL_Rect playerDestroying4;

	//Enemy
	Animation enemyMoveLeft;
	Animation enemyMoveRight;
	Animation enemyJumpLeft;
	Animation enemyJumpRight;
	SDL_Rect enemyFallingLeft;
	SDL_Rect enemyFallingRight;
	Animation enemyTakingOff;
	Animation enemyFlying;
	Animation enemySnowBalled1Left;
	Animation enemySnowBalled2Left;
	Animation enemySnowBalled3Left;
	Animation snowBall;
	Animation snowBallDestroying1;
	Animation snowBallDestroying2;
	Animation snowBallDestroying3;
	Animation snowBallDestroying4;


	//Shots
	Animation playerShotLeft;
	Animation playerShotRight;
	Animation playerBigShotLeft;
	Animation playerBigShotRight;
	Animation playerShotDying;
	Animation enemyShotLeft;
	Animation enemyShotLeftDying;
	Animation enemyShotRight;
	Animation enemyShotRightDying;

	//MISC
	SDL_Rect livesFace;
	Animation livesNumbers;
	Animation pointsNumbers;
	SDL_Rect player1;
	SDL_Rect player2;
	SDL_Rect hi;
	Animation pushButton;
	Animation insertCoin;
	Animation redPowerUp;
	Animation bluePowerUp;
	Animation yellowPowerUp;
	Animation greenPowerUp;
};
#endif //__GRAPHIC_H__