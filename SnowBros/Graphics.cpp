#include "Graphics.h"
#include "Application.h"
#include "ModuleTextures.h"

Graphics::Graphics(){

	playerIdleLeft = { 16, 6, 40, 52 };
	playerIdleRight = { 73, 6, 40, 52 };

	playerMoveLeft.frames.push_back({ 147, 6, 30, 52 });
	playerMoveLeft.frames.push_back({ 280, 4, 35, 54 });
	playerMoveLeft.frames.push_back({ 412, 4, 34, 54 });
	playerMoveLeft.speed = 0.1f;

	playerMoveRight.frames.push_back({ 217, 6, 30, 52 });
	playerMoveRight.frames.push_back({ 344, 4, 35, 54 });
	playerMoveRight.frames.push_back({ 479, 4, 34, 54 });
	playerMoveRight.speed = 0.1f;

	playerFastRight.frames.push_back({ 470, 335, 49, 55 });
	playerFastRight.frames.push_back({ 539, 335, 43, 53 });
	playerFastRight.frames.push_back({ 5, 401, 47, 53 });
	playerFastRight.speed = 0.1f;

	playerFastLeft.frames.push_back({ 406, 70, 49, 55 });
	playerFastLeft.frames.push_back({ 476, 70, 43, 53 });
	playerFastLeft.frames.push_back({ 541, 70, 47, 53 });
	playerFastLeft.speed = 0.1f;

	playerFastPushingLeft.frames.push_back({ 404, 269, 46, 54 });
	playerFastPushingLeft.frames.push_back({ 474, 269, 44, 52 });
	playerFastPushingLeft.speed = 0.1f;

	playerFastPushingRight.frames.push_back({ 408, 401, 46, 55 });
	playerFastPushingRight.frames.push_back({ 472, 401, 44, 53 });
	playerFastPushingRight.speed = 0.1f;

	playerJumpLeft.frames.push_back({ 8, 70, 42, 52 });
	playerJumpLeft.frames.push_back({ 79, 68, 37, 44 });
	playerJumpLeft.frames.push_back({ 145, 70, 38, 42 });
	playerJumpLeft.frames.push_back({ 209, 70, 38, 52 });
	playerJumpLeft.frames.push_back({ 280, 74, 37, 46 });
	playerJumpLeft.frames.push_back({ 344, 74, 44, 44 });
	playerJumpLeft.frames.push_back({ 541, 0, 38, 59 });
	playerJumpLeft.speed = 0.07f;
	playerJumpLeft.loop = false;

	playerJumpRight.frames.push_back({ 78, 335, 42, 52 });
	playerJumpRight.frames.push_back({ 144, 333, 37, 44 });
	playerJumpRight.frames.push_back({ 211, 335, 38, 42 });
	playerJumpRight.frames.push_back({ 279, 335, 38, 52 });
	playerJumpRight.frames.push_back({ 341, 339, 37, 46 });
	playerJumpRight.frames.push_back({ 404, 339, 44, 44 });
	playerJumpRight.frames.push_back({ 14, 331, 38, 59 });
	playerJumpRight.speed = 0.07f;
	playerJumpRight.loop = false;

	playerShootingRight.frames.push_back({ 12, 464, 38, 58 });
	playerShootingRight.frames.push_back({ 76, 470, 54, 52 });
	playerShootingRight.frames.push_back({ 142, 464, 41, 57 });
	playerShootingRight.frames.push_back({ 207, 468, 57, 54 });
	playerShootingRight.speed = 1.0f;

	playerShootingLeft.frames.push_back({ 11, 265, 38, 58 });
	playerShootingLeft.frames.push_back({ 64, 271, 54, 52 });
	playerShootingLeft.frames.push_back({ 144, 265, 41, 57 });
	playerShootingLeft.frames.push_back({ 196, 269, 57, 54 });
	playerShootingLeft.speed = 1.0f;

	playerChangingLevel.frames.push_back({ 275, 265, 42, 67 });
	playerChangingLevel.frames.push_back({ 341, 265, 42, 63 });
	playerChangingLevel.speed = 0.1f;

	playerFallingLeft = { 541, 0, 38, 59 };
	playerFallingRight = { 14, 331, 38, 59 };

	playerInBall.frames.push_back({ 16, 532, 82, 46 });
	playerInBall.frames.push_back({ 116, 535, 82, 49 });
	playerInBall.frames.push_back({ 218, 540, 82, 36 });
	playerInBall.speed = 0.1f;

	playerPushingLeft.frames.push_back({ 271, 203, 38, 54 });
	playerPushingLeft.frames.push_back({ 340, 205, 40, 52 });
	playerPushingLeft.frames.push_back({ 408, 205, 38, 52 });
	playerPushingLeft.speed = 0.1f;

	playerPushingRight.frames.push_back({ 85, 402, 37, 54 });
	playerPushingRight.frames.push_back({ 147, 404, 39, 52 });
	playerPushingRight.frames.push_back({ 213, 404, 38, 52 });
	playerPushingRight.speed = 0.1f;

	playerFastPushingLeft.frames.push_back({ 404, 269, 46, 55 });
	playerFastPushingLeft.frames.push_back({ 474, 269, 44, 53 });
	playerFastPushingLeft.speed = 0.1f;

	playerFastPushingRight.frames.push_back({ 408, 401, 46, 55 });
	playerFastPushingRight.frames.push_back({ 472, 401, 44, 53 });
	playerFastPushingRight.speed = 0.1f;

	playerLastPushLeft = { 462, 203, 57, 54 };

	playerLastPushRight = { 339, 402, 57, 54 };

	playerDying.frames.push_back({ 70, 132, 56, 65 });
	playerDying.frames.push_back({ 134, 134, 59, 59 });
	playerDying.frames.push_back({ 203, 149, 54, 50 });
	playerDying.frames.push_back({ 331, 149, 63, 31 });
	playerDying.frames.push_back({ 398, 149, 63, 23 });
	playerDying.frames.push_back({ 462, 149, 67, 13 });
	playerDying.speed = 0.05f;

	playerDestroying1 = { 533, 135, 25, 27 };
	playerDestroying2 = { 566, 134, 25, 28 };
	playerDestroying3 = { 533, 168, 25, 27 };
	playerDestroying4 = { 566, 167, 25, 28 };



	//ENEMY
	enemyMoveLeft.frames.push_back({ 148, 8, 34, 49 });
	enemyMoveLeft.frames.push_back({ 214, 6, 35, 51 });
	enemyMoveLeft.frames.push_back({ 18, 71, 35, 51 });
	enemyMoveLeft.speed = 0.1f;

	enemyMoveRight.frames.push_back({ 79, 399, 34, 49 });
	enemyMoveRight.frames.push_back({ 12, 397, 35, 51 });
	enemyMoveRight.frames.push_back({ 208, 462, 35, 51 });
	enemyMoveRight.speed = 0.1f;

	enemyJumpLeft.frames.push_back({ 14, 132, 41, 59 });
	enemyJumpLeft.speed = 0.07f;
	enemyJumpLeft.loop = false;

	enemyJumpRight.frames.push_back({ 10, 587, 41, 59 });
	enemyJumpRight.speed = 0.07f;
	enemyJumpRight.loop = false;

	enemyFallingLeft = { 202, 199, 57, 58 };
	enemyFallingRight = { 2, 524, 57, 58 };

	enemyTakingOff.frames.push_back({ 65, 132, 66, 60});
	enemyTakingOff.frames.push_back({ 132, 130, 62, 64 });
	enemyTakingOff.speed = 0.2f;

	enemyFlying.frames.push_back({ 69, 264, 58, 54 });
	enemyFlying.frames.push_back({ 142, 262, 50, 60 });
	enemyFlying.frames.push_back({ 199, 269, 58, 53 });
	enemyFlying.frames.push_back({ 4, 330, 49, 59 });
	enemyFlying.speed = 0.3f;

	enemyFlying.frames.push_back({ 69, 330, 56, 53 });
	enemyFlying.frames.push_back({ 132, 334, 52, 49 });
	enemyFlying.frames.push_back({ 197, 346, 54, 37 });
	enemyFlying.speed = 0.3f;

	enemySnowBalled1Left.frames.push_back({ 8, 891, 54, 48 });
	enemySnowBalled1Left.frames.push_back({ 8, 960, 48, 42 });
	enemySnowBalled1Left.speed = 0.01f;

	enemySnowBalled2Left.frames.push_back({ 67, 890, 54, 48 });
	enemySnowBalled2Left.frames.push_back({ 71, 955, 50, 47 });
	enemySnowBalled2Left.speed = 0.01f;

	enemySnowBalled3Left.frames.push_back({ 127, 888, 53, 51 });
	enemySnowBalled3Left.frames.push_back({ 135, 952, 51, 50 });
	enemySnowBalled3Left.speed = 0.01f;

	snowBall.frames.push_back({ 8, 1006, 51, 61 });
	snowBall.frames.push_back({ 71, 1008, 53, 59 });
	snowBall.frames.push_back({ 136, 1006, 51, 61 });
	snowBall.frames.push_back({ 201, 1006, 53, 59 });
	snowBall.speed = 0.04f;

	snowBallDestroying1.frames.push_back({ 191, 880, 29, 28 });
	snowBallDestroying1.frames.push_back({ 191, 943, 29, 29 });
	snowBallDestroying1.speed = 0.05f;

	snowBallDestroying2.frames.push_back({ 221, 878, 31, 30 });
	snowBallDestroying2.frames.push_back({ 221, 941, 31, 31 });
	snowBallDestroying3.speed = 0.05f;

	snowBallDestroying3.frames.push_back({ 190, 909, 30, 31 });
	snowBallDestroying3.frames.push_back({ 193, 977, 25, 24 });
	snowBallDestroying3.speed = 0.05f;

	snowBallDestroying4.frames.push_back({ 227, 911, 25, 26 });
	snowBallDestroying4.frames.push_back({ 227, 975, 25, 26 });
	snowBallDestroying4.speed = 0.05f;

	//PARTICLES
	playerShotLeft.frames.push_back({ 270, 465, 17, 25 });
	playerShotLeft.frames.push_back({ 304, 465, 17, 25 });
	playerShotLeft.speed = 0.25f;

	playerShotRight.frames.push_back({ 304, 493, 17, 25 });
	playerShotRight.frames.push_back({ 270, 493, 17, 25 });
	playerShotRight.speed = 0.25f;

	playerBigShotLeft.frames.push_back({ 474, 463, 24, 26 });
	playerBigShotLeft.frames.push_back({ 502, 463, 24, 26 });
	playerBigShotLeft.speed = 0.25f;

	playerBigShotRight.frames.push_back({ 474, 490, 24, 26 });
	playerBigShotRight.frames.push_back({ 502, 490, 24, 26 });
	playerBigShotRight.speed = 0.25f;

	playerShotDying.frames.push_back({436,497,16,20});
	playerShotDying.frames.push_back({404,495,20,23});
	playerShotDying.frames.push_back({399,461,30,31});
	playerShotDying.frames.push_back({429,461,30,31});
	playerShotDying.speed = 0.1f;


	enemyShotLeft.frames.push_back({ 161, 608, 29, 19 });
	enemyShotLeft.frames.push_back({ 216, 602, 39, 29 });
	enemyShotLeft.frames.push_back({ 68, 663, 51, 35 });
	enemyShotLeft.frames.push_back({ 190, 661, 63, 39 });
	enemyShotLeft.frames.push_back({ 127, 659, 63, 41 });
	enemyShotLeft.speed = 0.1f;
	enemyShotLeft.loop = false;

	enemyShotRight.frames.push_back({ 205, 726, 29, 19 });
	enemyShotRight.frames.push_back({ 152, 720, 39, 29 });
	enemyShotRight.frames.push_back({ 2, 663, 51, 35 });
	enemyShotRight.frames.push_back({ 2, 716, 63, 39 });
	enemyShotRight.frames.push_back({ 61, 714, 63, 41 }); 
	enemyShotRight.speed = 0.1f;
	enemyShotRight.loop = false;

	enemyShotLeftDying.frames.push_back({ 15, 764, 43, 53 });
	enemyShotLeftDying.frames.push_back({ 80, 760, 32, 55 });
	enemyShotLeftDying.frames.push_back({ 19, 821, 31, 55 });
	enemyShotLeftDying.frames.push_back({ 91, 825, 22, 47 });
	enemyShotLeftDying.speed = 0.1f;

	enemyShotRightDying.frames.push_back({ 193, 764, 43, 53 });
	enemyShotRightDying.frames.push_back({ 139, 760, 32, 55 });
	enemyShotRightDying.frames.push_back({ 201, 821, 31, 55 });
	enemyShotRightDying.frames.push_back({ 138, 825, 22, 47 });
	enemyShotRightDying.speed = 0.1f;

	//MISC
	livesFace = { 531, 265, 27, 33 };

	livesNumbers.frames.push_back({ 335, 466, 16, 16 });
	livesNumbers.frames.push_back({ 372, 466, 11, 16 });
	livesNumbers.frames.push_back({ 335, 501, 16, 16 });
	livesNumbers.frames.push_back({ 370, 501, 16, 16 });
	livesNumbers.speed = 0;

	pointsNumbers.frames.push_back({ 0, 7, 16, 17 });
	pointsNumbers.frames.push_back({ 33, 7, 12, 17 });
	pointsNumbers.frames.push_back({ 62, 7, 16, 17 });
	pointsNumbers.frames.push_back({ 93, 7, 17, 17 });
	pointsNumbers.frames.push_back({ 0, 38, 16, 17 });
	pointsNumbers.frames.push_back({ 31, 38, 16, 17 });
	pointsNumbers.frames.push_back({ 62, 38, 16, 17 });
	pointsNumbers.frames.push_back({ 93, 38, 17, 17 });
	pointsNumbers.frames.push_back({ 0, 69, 16, 17 });
	pointsNumbers.frames.push_back({ 31, 69, 16, 17 });
	pointsNumbers.speed = 0;

	player1 = { 66, 70, 28, 16 };
	player2 = { 94, 70, 31, 16 };
	hi = { 2, 163, 28, 17 };

	pushButton.frames.push_back({ 15, 124, 95, 32 });
	pushButton.frames.push_back({ 15, 124, 0, 0 });
	pushButton.speed = 0.075f;

	insertCoin.frames.push_back({ 15, 93, 95, 31 });
	insertCoin.frames.push_back({ 15, 93, 0, 0 });
	insertCoin.speed = 0.075f;

	redPowerUp.frames.push_back({ 36, 158, 21, 27 });
	redPowerUp.frames.push_back({ 67, 158, 21, 27 });
	redPowerUp.speed = 0.1f;

	bluePowerUp.frames.push_back({ 99, 158, 20, 27 });
	bluePowerUp.frames.push_back({ 6, 189, 20, 27 });
	bluePowerUp.speed = 0.1f;

	yellowPowerUp.frames.push_back({ 36, 189, 21, 27 });
	yellowPowerUp.frames.push_back({ 67, 189, 20, 27 });
	yellowPowerUp.speed = 0.1f;

	greenPowerUp.frames.push_back({ 98, 189, 20, 27 });
	greenPowerUp.frames.push_back({ 5, 220, 21, 27 });
	greenPowerUp.speed = 0.1f;
}

void Graphics::LoadGraphics(){
	//Loading player, enemy and miscellaneous
	miscGraphics = App->textures->Load("sprites/misc/misc.png"); 
	enemyGraphics = App->textures->Load("Sprites/Enemy/enemySprites.png");
	playerGraphics = App->textures->Load("Sprites/Player/playerSprites.png");
}

void Graphics::UnloadGraphics(){
	//Unloading player, enemy and miscellaneous
	App->textures->Unload(miscGraphics);
	App->textures->Unload(enemyGraphics);
	App->textures->Unload(playerGraphics);
}
