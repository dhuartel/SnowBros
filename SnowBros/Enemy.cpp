#include "Application.h"
#include "ModuleEnemy.h"
#include "ModuleRender.h"
#include "ModuleParticle.h"
#include "ModuleCollision.h"
#include "Enemy.h"
#include "Graphics.h"
#include "SDL/include/SDL.h"
#include "ModulePlayer.h"

Enemy::Enemy(int number)
{
	//These animations come here, since knowing when do they end is needed,
	// and having them in graphics would make it impossible, since they would be shared
	enemyTurnLeft.frames.push_back({ 202, 399, 47, 50 });
	enemyTurnLeft.frames.push_back({ 201, 138, 52, 50 });
	enemyTurnLeft.frames.push_back({ 12, 8, 47, 50 });
	enemyTurnLeft.frames.push_back({ 81, 6, 32, 52 });
	enemyTurnLeft.frames.push_back({ 81, 6, 32, 52 });
	enemyTurnLeft.frames.push_back({ 81, 6, 32, 52 });
	enemyTurnLeft.frames.push_back({ 148, 8, 34, 50 });
	enemyTurnLeft.frames.push_back({ 148, 8, 34, 50 });
	enemyTurnLeft.speed = 0.05f;

	enemyTurnRight.frames.push_back({ 12, 8, 47, 50 });
	enemyTurnRight.frames.push_back({ 201, 138, 52, 50 });
	enemyTurnRight.frames.push_back({ 202, 399, 47, 50 });
	enemyTurnRight.frames.push_back({ 148, 397, 32, 52 });
	enemyTurnRight.frames.push_back({ 148, 397, 32, 52 });
	enemyTurnRight.frames.push_back({ 148, 397, 32, 52 });
	enemyTurnRight.frames.push_back({ 79, 399, 34, 50 });
	enemyTurnRight.frames.push_back({ 79, 399, 34, 50 });
	enemyTurnRight.speed = 0.05f;

	enemyLandingLeft.frames.push_back({ 8, 275, 53, 43 });
	enemyLandingLeft.frames.push_back({ 8, 275, 53, 43 });
	enemyLandingLeft.speed = 0.1f;

	enemyLandingRight.frames.push_back({ 69, 600, 53, 43 });
	enemyLandingRight.frames.push_back({ 69, 600, 53, 43 });
	enemyLandingRight.speed = 0.1f;

	enemyLandingDead.frames.push_back({ 69, 330, 56, 53 });
	enemyLandingDead.frames.push_back({ 132, 334, 55, 49 });
	enemyLandingDead.frames.push_back({ 197, 346, 56, 37 });
	enemyLandingDead.speed = 0.01f;

	enemynumber = number;
	//Setting the position of the enemy
	switch (number){
	case 1:
		position.x = 50;
		position.y = 774;
		break;
	case 2:
		position.x = 427;
		position.y = 774;
		lookingLeft = false;
		break;
	case 3:
		position.x = 50;
		position.y = 646;
		break;
	case 4:
		position.x = 427;
		position.y = 646;
		lookingLeft = false;
		break;
	case 5:
		position.x = 310;
		position.y = 259;
		lookingLeft = false;
		break;
	case 6:
		position.x = 310;
		position.y = 132;
		lookingLeft = false;
		break;

	}
	//Creating the collider
	SDL_Rect aux;
	//Body
	aux.x = (int)position.x;
	aux.y = ((int)position.y - App->graphics->enemyMoveLeft.GetCurrentFrame().h);
	aux.w = App->graphics->enemyMoveLeft.GetCurrentFrame().w;
	aux.h = App->graphics->enemyMoveLeft.GetCurrentFrame().h;
	myCollider = App->collisions->CreateCollider(aux, App->enemy, ENEMY);
	//Feet, x and width reused
	aux.y = position.y;
	aux.h = 2;
	myFeetCollider = App->collisions->CreateCollider(aux, App->enemy, PLAYERFEET);
	status = NONE;
	hitCounter = 0;
	srand(SDL_GetTicks());
}

Enemy::~Enemy(){
}

//LOGIC
update_status Enemy::PreUpdate(){
	switch (status){
	case SNOWROLLING:
	case SNOWDESTROYING:
	case TAKINGOFF:
	case FLYING:
	case LANDINGDEAD:
	case TOBEDESTROYED:
		break;
	default:
		if (snowHit){
			if (App->player->bluePowerUp){
				hitCounter += 2;
			}
			else{
				++hitCounter;
			}
			if (hitCounter > 6){
				hitCounter = 6;
			}
			hitTime = SDL_GetTicks();
			snowHit = false;
		}
		if (hitCounter == 6){
			if (SDL_GetTicks() > hitTime + 3000){
				--hitCounter;
				hitTime = SDL_GetTicks();
			}
		}
		else if (SDL_GetTicks() > hitTime + 800 && hitCounter>0){
			--hitCounter;
			hitTime = SDL_GetTicks();
			if (hitCounter == 0){
				status = NONE;
				myCollider->type = ENEMY;
			}
		}
		switch (hitCounter){
		case 1:
		case 2:
			status = SNOW1;
			myCollider->type = ENEMY;
			break;
		case 3:
		case 4:
			status = SNOW2;
			myCollider->type = ENEMY;
			break;
		case 5:
			status = SNOW3;
			myCollider->type = ENEMY;
			break;
		case 6:
			status = SNOW4;
			myCollider->type = SNOWBALL;
			break;
		}
		break;
	}

	switch (status)
	{
	case NONE:
		/*if (snowHit){
		status = SNOW1;
		hitCounter = 0;
		hitTime = SDL_GetTicks();
		}
		else*/ if (!myFeetCollider->colliding){
			status = FALLING;
			position.y += 2;
		}
		else{
			if (lookingLeft){
				position.x -= movementSpeed;
			}
			else{
				position.x += movementSpeed;;
			}
		}
		break;
	case JUMPING:
		jumpCommited += 3;
		if (jumpCommited <= 66)
			position.y -= 3;
		else if (myFeetCollider->colliding){
			status = LANDING;
		}
		else{
			position.y += 2;
		}
		/*if (snowHit){
		status = SNOW1;
		hitCounter = 0;
		hitTime = SDL_GetTicks();
		}*/
		break;
	case FALLING:
		if (myFeetCollider->colliding){
			status = LANDING;
		}
		else{
			position.y += 2;
		}
		/*if (snowHit){
		status = SNOW1;
		hitCounter = 0;
		hitTime = SDL_GetTicks();
		}*/
		break;
	case LANDING:
		jumpCommited = 0;
		turn = true;
		/*if (snowHit){
		status = SNOW1;
		hitCounter = 0;
		hitTime = SDL_GetTicks();
		}
		else*/{
			if (lookingLeft){
				if (enemyLandingLeft.hasFinished()){
					enemyLandingLeft.reset();
					status = NONE;
				}
			}
			else{
				if (enemyLandingRight.hasFinished()){
					enemyLandingRight.reset();
					status = NONE;
				}
			}
		}
		break;
	case SHOOTING:
		/*if (snowHit){
		status = SNOW1;
		hitCounter = 0;
		hitTime = SDL_GetTicks();
		}
		else*/{
			if (lookingLeft){
				if (enemyTurnLeft.shootMoment() && !shot){
					shoot(1);
				}
				if (enemyTurnLeft.hasFinished()){
					enemyTurnLeft.reset();
					shot = false;
					status = NONE;
				}
			}
			else{
				if (enemyTurnRight.shootMoment() && !shot){
					shoot(2);
				}
				if (enemyTurnRight.hasFinished()){
					enemyTurnRight.reset();
					shot = false;
					status = NONE;
				}
			}
	}
				 break;
	case SNOW1:
		/*if (snowHit){
		hitTime = SDL_GetTicks();
		snowHit = false;
		hitCounter++;
		if (hitCounter == 5){
		status = SNOW2;
		hitCounter = 0;
		}
		}
		else{
		if (SDL_GetTicks() > hitTime + 4000){
		status = NONE;
		hitTime = SDL_GetTicks();
		}
		}*/
		if (!myFeetCollider->colliding){
			position.y += 2;
		}
		break;
	case SNOW2:
		/*if (snowHit){
		hitTime = SDL_GetTicks();
		snowHit = false;
		hitCounter++;
		if (hitCounter == 5){
		status = SNOW3;
		hitCounter = 0;
		}
		}
		else{
		if (SDL_GetTicks() > hitTime + 4000){
		status = SNOW1;
		hitTime = SDL_GetTicks();
		}
		}*/
		if (!myFeetCollider->colliding){
			position.y += 2;
		}
		break;
	case SNOW3:
		/*if (snowHit){
		hitTime = SDL_GetTicks();
		snowHit = false;
		hitCounter++;
		if (hitCounter == 5){
		status = SNOW4;
		myCollider->type = SNOWBALL;
		hitCounter = 0;
		}
		}
		else{
		if (SDL_GetTicks() > hitTime + 4000){
		status = SNOW2;
		hitTime = SDL_GetTicks();
		}
		}*/
		if (!myFeetCollider->colliding){
			position.y += 2;
		}
		break;
	case SNOW4:
		/*if (snowHit){
		hitTime = SDL_GetTicks();
		snowHit = false;
		}
		else if (SDL_GetTicks() > hitTime + 8000){
		status = SNOW3;
		myCollider->type = ENEMY;
		hitTime = SDL_GetTicks();
		}*/
		if (!myFeetCollider->colliding){
			position.y += 2;
		}
		break;
	case SNOWROLLING:
		if (lookingLeft){
			position.x -= 4;
		}
		else{
			position.x += 4;
		}
		if (!myFeetCollider->colliding)
			position.y += 4;
		break;
	case SNOWDESTROYING:
		if (relativePositionsDestroying >= destroyingOffset){
			status = TOBEDESTROYED;
		}
		else{
			relativePositionsDestroying += 1;
			relativePositionsDestroyingState = (relativePositionsDestroyingState + 1) % 4;
		}
		break;
	case TAKINGOFF:
		jumpCommited += 4;
		if (lookingLeft){
			position.x -= 2;
		}
		else{
			position.x += 2;
		}
		if (jumpCommited <= 100){
			position.y -= 4;
		}
		else{
			status = FLYING;
		}
		break;
	case FLYING:
		jumpCommited += 4;
		if (lookingLeft){
			position.x -= 2;
		}
		else{
			position.x += 2;
		}
		if (flyingDown){
			position.y += 4;
		}
		else{
			position.y -= 4;
		}
		if (jumpCommited >= 300){
			flyingDown = true;
		}
		break;
	case LANDINGDEAD:
		if (enemyLandingDead.hasFinished()){
			if ((rand() % 100) < 20){
				dropPowerUp();
			}
			status = TOBEDESTROYED;
		}
		break;
	case TOBEDESTROYED:
		break;
	default:
		break;
	}
	return UPDATE_CONTINUE;
}


//DRAW
update_status Enemy::Update(){
	//I use the first frame of enemyMoveLeft as a standard for the collision box,
	//yet I change it for  the snowballs since they are bigger
	myCollider->collisionBox.x = position.x;
	myCollider->collisionBox.y = (position.y - App->graphics->enemyMoveLeft.GetFrame(0).h);
	myCollider->collisionBox.h = App->graphics->enemyMoveLeft.GetFrame(0).h;
	myCollider->collisionBox.w = App->graphics->enemyMoveLeft.GetFrame(0).w;
	myFeetCollider->collisionBox.x = position.x;
	myFeetCollider->collisionBox.y = position.y;
	switch (status)
	{
	case NONE:
		if (lookingLeft){
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - (App->graphics->enemyMoveLeft.GetCurrentFrame()).h, &(App->graphics->enemyMoveLeft.GetCurrentFrame())); // ryu animation
		}
		else{
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - (App->graphics->enemyMoveRight.GetCurrentFrame()).h, &(App->graphics->enemyMoveRight.GetCurrentFrame())); // ryu animation
		}
		break;
	case JUMPING:
		if (lookingLeft){
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - App->graphics->enemyJumpLeft.GetCurrentFrame().h, &App->graphics->enemyJumpLeft.GetCurrentFrame()); // ryu animation
		}
		else{
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - App->graphics->enemyJumpRight.GetCurrentFrame().h, &App->graphics->enemyJumpRight.GetCurrentFrame()); // ryu animation
		}
		break;
	case FALLING:
		if (lookingLeft){
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - App->graphics->enemyFallingLeft.h, &App->graphics->enemyFallingLeft);
		}
		else{
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - App->graphics->enemyFallingRight.h, &App->graphics->enemyFallingRight);
		}
		break;
	case LANDING:
		if (lookingLeft){
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - enemyLandingLeft.GetCurrentFrame().h, &enemyLandingLeft.GetCurrentFrame());
		}
		else{
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - enemyLandingRight.GetCurrentFrame().h, &enemyLandingRight.GetCurrentFrame());
		}
		break;
	case SHOOTING:
		if (lookingLeft){
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - enemyTurnLeft.GetCurrentFrame().h, &enemyTurnLeft.GetCurrentFrame());
		}
		else{
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - enemyTurnRight.GetCurrentFrame().h, &enemyTurnRight.GetCurrentFrame());
		}
		break;
	case SNOW1:
		myCollider->collisionBox.h = App->graphics->enemySnowBalled1Left.GetFrame(0).h;
		myCollider->collisionBox.w = App->graphics->enemySnowBalled1Left.GetFrame(0).w;
		if (lookingLeft){
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - App->graphics->enemySnowBalled1Left.GetCurrentFrame().h, &App->graphics->enemySnowBalled1Left.GetCurrentFrame());
		}
		else{
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - App->graphics->enemySnowBalled1Left.GetCurrentFrame().h, &App->graphics->enemySnowBalled1Left.GetCurrentFrame());
		}
		break;
	case SNOW2:
		myCollider->collisionBox.h = App->graphics->enemySnowBalled2Left.GetFrame(0).h;
		myCollider->collisionBox.w = App->graphics->enemySnowBalled2Left.GetFrame(0).w;
		if (lookingLeft){
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - App->graphics->enemySnowBalled2Left.GetCurrentFrame().h, &App->graphics->enemySnowBalled2Left.GetCurrentFrame());
		}
		else{
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - App->graphics->enemySnowBalled2Left.GetCurrentFrame().h, &App->graphics->enemySnowBalled2Left.GetCurrentFrame());
		}
		break;
	case SNOW3:
		myCollider->collisionBox.h = App->graphics->enemySnowBalled3Left.GetFrame(0).h;
		myCollider->collisionBox.w = App->graphics->enemySnowBalled3Left.GetFrame(0).w;
		if (lookingLeft){
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - App->graphics->enemySnowBalled3Left.GetCurrentFrame().h, &App->graphics->enemySnowBalled3Left.GetCurrentFrame());
		}
		else{
			App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - App->graphics->enemySnowBalled3Left.GetCurrentFrame().h, &App->graphics->enemySnowBalled3Left.GetCurrentFrame());
		}
		break;
	case SNOW4:
		myCollider->collisionBox.h = App->graphics->snowBall.GetFrame(0).h;
		myCollider->collisionBox.w = App->graphics->snowBall.GetFrame(0).w;
		App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - App->graphics->snowBall.GetFrame(0).h, &App->graphics->snowBall.GetFrame(0));
		break;
	case SNOWROLLING:
		myCollider->collisionBox.h = App->graphics->snowBall.GetFrame(0).h;
		myCollider->collisionBox.w = App->graphics->snowBall.GetFrame(0).w;
		App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - App->graphics->snowBall.GetCurrentFrame().h, &App->graphics->snowBall.GetCurrentFrame());
		break;
	case SNOWDESTROYING:
		displayEnemyDestruction();
		break;
	case TAKINGOFF:
		App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - App->graphics->enemyTakingOff.GetCurrentFrame().h, &App->graphics->enemyTakingOff.GetCurrentFrame());
		break;
	case FLYING:
		App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - App->graphics->enemyFlying.GetCurrentFrame().h, &App->graphics->enemyFlying.GetCurrentFrame());
		break;
	case LANDINGDEAD:
		App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - enemyLandingDead.GetCurrentFrame().h, &enemyLandingDead.GetCurrentFrame());
		break;
	case TOBEDESTROYED:
		break;
	default:
		break;
	}
	return UPDATE_CONTINUE;
}

void Enemy::displayEnemyDestruction()const{
	switch (relativePositionsDestroyingState){
	case 0:
		App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - destroyingOffset + relativePositionsDestroying, &App->graphics->snowBallDestroying1.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying2.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying3.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->snowBallDestroying4.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying1.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying2.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - destroyingOffset - relativePositionsDestroying, &App->graphics->snowBallDestroying3.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying4.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying1.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->snowBallDestroying2.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying3.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying4.GetCurrentFrame());
		break;
	case 1:
		App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - destroyingOffset + relativePositionsDestroying, &App->graphics->snowBallDestroying4.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying1.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying2.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->snowBallDestroying3.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying4.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying1.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - destroyingOffset - relativePositionsDestroying, &App->graphics->snowBallDestroying2.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying3.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying4.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->snowBallDestroying1.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying2.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying3.GetCurrentFrame());
		break;
	case 2:
		App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - destroyingOffset + relativePositionsDestroying, &App->graphics->snowBallDestroying3.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying4.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying1.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->snowBallDestroying2.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying3.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying4.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - destroyingOffset - relativePositionsDestroying, &App->graphics->snowBallDestroying1.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying2.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying3.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->snowBallDestroying4.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying1.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying2.GetCurrentFrame());
		break;
	case 3:
		App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - destroyingOffset + relativePositionsDestroying, &App->graphics->snowBallDestroying2.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying3.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying4.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->snowBallDestroying1.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying2.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying3.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x, position.y - destroyingOffset - relativePositionsDestroying, &App->graphics->snowBallDestroying4.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying1.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying2.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->snowBallDestroying3.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->snowBallDestroying4.GetCurrentFrame());
		App->renderer->Blit(App->graphics->enemyGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->snowBallDestroying1.GetCurrentFrame());
		break;
	}
}

void Enemy::shoot(int direction){
	particle aux;
	switch (direction)
	{
	case 1://LEFT
		aux.position.y = position.y - 13;
		aux.tex = App->graphics->enemyGraphics;
		aux.speed.y = 0;
		aux.position.x = position.x - 10;
		aux.anim = App->graphics->enemyShotLeft;
		aux.speed.x = -3.5f;
		aux.acceleration.x = 0;
		aux.acceleration.y = 0;
		App->particles->CreateParticle(aux, 2);
		shot = true;
		break;
	case 2://RIGHT
		aux.position.y = position.y - 13;
		aux.speed.y = 0;
		aux.tex = App->graphics->enemyGraphics;
		aux.position.x = position.x + 25;
		aux.anim = App->graphics->enemyShotRight;
		aux.speed.x = 3.5f;
		aux.acceleration.x = 0;
		aux.acceleration.y = 0;
		App->particles->CreateParticle(aux, 3);
		shot = true;
		break;
	}
}

void Enemy::dropPowerUp(){
	particle aux;
	aux.position.y = position.y;
	aux.speed.y = 0;
	aux.tex = App->graphics->miscGraphics;
	aux.position.x = position.x + 25;
	aux.speed.x = 0;
	aux.acceleration.x = 0;
	aux.acceleration.y = 0;
	switch (rand() % 3){
	case 0:
		aux.anim = App->graphics->redPowerUp;
		App->particles->CreateParticle(aux, 4);
		break;
	case 1:
		aux.anim = App->graphics->yellowPowerUp;
		App->particles->CreateParticle(aux, 5);
		break;
	case 2:
		aux.anim = App->graphics->bluePowerUp;
		App->particles->CreateParticle(aux, 6);
	}
}