#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "Enemy.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleParticle.h"
#include "ModuleCollision.h"
#include "ModuleLevels.h"
#include "Graphics.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameOver.h"
#include "ModuleAudio.h"
#include "AudioEffects.h"
#include "SDL/include/SDL.h"

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{
}

bool ModulePlayer::Start()
{
	SDL_Rect aux;
	aux.x = 0;
	aux.y = 0;
	aux.w = 0;
	aux.h = 0;
	myCollider = App->collisions->CreateCollider(aux, this, PLAYER);
	myFeetCollider = App->collisions->CreateCollider(aux, this, PLAYERFEET);
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	return true;
}

update_status ModulePlayer::PreUpdate(){
	if (redPowerUp){
		movementSpeed = 4;
	}
	else{
		movementSpeed = 2;
	}
	if (firstTime){//As it takes a bit from the time start runs to the moment levels ae displayer, this is needed
		ResetPlayer(1);
		firstTime = false;
	}
	if (!myCollider->colliding){
		leftBlocked = false;
		rightBlocked = false;
	}
	if (immune){
		if (alpha == TRANSPARENTALPHA){
			alpha = 255;
		}
		else{
			alpha = TRANSPARENTALPHA;
		}
		if (SDL_GetTicks() > immuneTime + 2500){
			immune = false;
			alpha = 255;
		}
	}
	Enemy* ball;
	switch (status)
	{
	case PLAYERNONE:
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT){
			lookingLeft = true;
			if (!leftBlocked){
				position.x -= movementSpeed;
			}
			status = PLAYERMOVING;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){
			lookingLeft = false;
			if (!rightBlocked){
				position.x += movementSpeed;
			}
			status = PLAYERMOVING;
		}
		if (!myFeetCollider->colliding){
			status = PLAYERFALLING;
		}
		else if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN){
			status = PLAYERJUMPING;
			App->audio->PlayFx(App->audioEffects->jumpFx, 0);
			jumpCommited = 0;
			if (lookingLeft)
				App->graphics->playerJumpLeft.reset();
			else
				App->graphics->playerJumpRight.reset();
		}
		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN){
			particle aux;
			aux.position.y = position.y - 13;
			aux.tex = App->graphics->playerGraphics;
			aux.speed.y = -1;
			aux.acceleration.x = 0;
			aux.acceleration.y = 0.1f;
			if (lookingLeft){
				aux.position.x = position.x - 5;
				if (bluePowerUp){
					aux.anim = App->graphics->playerBigShotLeft;
				}
				else{
					aux.anim = App->graphics->playerShotLeft;
				}
				if (yellowPowerUp){
					aux.speed.x = -4.6f;
				}
				else{
					aux.speed.x = -2.3f;
				}
			}
			else{
				aux.position.x = position.x + 25;
				if (bluePowerUp){
					aux.anim = App->graphics->playerBigShotRight;
				}
				else{
					aux.anim = App->graphics->playerShotRight;
				}
				if (yellowPowerUp){
					aux.speed.x = 4.6f;
				}
				else{
					aux.speed.x = 2.3f;
				}
			}
			App->particles->CreateParticle(aux, 1);
			shooting = true;
			App->audio->PlayFx(App->audioEffects->fireFx, 0);
			App->graphics->playerShootingLeft.reset();
		}
		break;
	case PLAYERMOVING:
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT){
			lookingLeft = true;
			if (!leftBlocked){
				position.x -= movementSpeed;
			}
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){
			lookingLeft = false;
			if (!rightBlocked){
				position.x += movementSpeed;
			}
		}
		else{
			status = PLAYERNONE;
		}
		if (!myFeetCollider->colliding){
			status = PLAYERFALLING;
		}
		else if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN){
			status = PLAYERJUMPING;
			App->audio->PlayFx(App->audioEffects->jumpFx, 0);
			jumpCommited = 0;
			if (lookingLeft)
				App->graphics->playerJumpLeft.reset();
			else
				App->graphics->playerJumpRight.reset();
		}
		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN){
			particle aux;
			aux.position.y = position.y - 13;
			aux.tex = App->graphics->playerGraphics;
			aux.speed.y = -1;
			aux.acceleration.x = 0;
			aux.acceleration.y = 0.1f;
			if (lookingLeft){
				aux.position.x = position.x - 5;
				if (bluePowerUp){
					aux.anim = App->graphics->playerBigShotLeft;
				}
				else{
					aux.anim = App->graphics->playerShotLeft;
				}
				if (yellowPowerUp){
					aux.speed.x = -4.6f;
				}
				else{
					aux.speed.x = -2.3f;
				}
			}
			else{
				aux.position.x = position.x + 25;
				if (bluePowerUp){
					aux.anim = App->graphics->playerBigShotRight;
				}
				else{
					aux.anim = App->graphics->playerShotRight;
				}
				if (yellowPowerUp){
					aux.speed.x = 4.6f;
				}
				else{
					aux.speed.x = 2.3f;
				}
			}
			App->particles->CreateParticle(aux, 1);
			shooting = true;
			App->audio->PlayFx(App->audioEffects->fireFx, 0);
			App->graphics->playerShootingLeft.reset();
		}
		break;
	case PLAYERJUMPING:
		jumpCommited += 3;
		if (jumpCommited <= 69)
			position.y -= 3;
		else if (myFeetCollider->colliding){
			status = PLAYERNONE;
		}
		else{
			status = PLAYERFALLING;
		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT){
			lookingLeft = true;
			if (!leftBlocked){
				position.x -= movementSpeed;
			}
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){
			lookingLeft = false;
			if (!rightBlocked){
				position.x += movementSpeed;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN){
			particle aux;
			aux.position.y = position.y - 13;
			aux.tex = App->graphics->playerGraphics;
			aux.speed.y = -1;
			aux.acceleration.x = 0;
			aux.acceleration.y = 0.1f;
			if (lookingLeft){
				aux.position.x = position.x - 5;
				if (bluePowerUp){
					aux.anim = App->graphics->playerBigShotLeft;
				}
				else{
					aux.anim = App->graphics->playerShotLeft;
				}
				if (yellowPowerUp){
					aux.speed.x = -4.6f;
				}
				else{
					aux.speed.x = -2.3f;
				}
			}
			else{
				aux.position.x = position.x + 25;
				if (bluePowerUp){
					aux.anim = App->graphics->playerBigShotRight;
				}
				else{
					aux.anim = App->graphics->playerShotRight;
				}
				if (yellowPowerUp){
					aux.speed.x = 4.6f;
				}
				else{
					aux.speed.x = 2.3f;
				}
			}
			App->particles->CreateParticle(aux, 1);
			shooting = true;
			App->audio->PlayFx(App->audioEffects->fireFx, 0);
			App->graphics->playerShootingLeft.reset();
		}
		break;
	case PLAYERFALLING:
		if (!myFeetCollider->colliding){
			position.y += fallingSpeed;
			fallingSpeed += fallingAcceleration;
		}
		else{
			status = PLAYERNONE;
			fallingSpeed = 3;
		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT){
			lookingLeft = true;
			if (!leftBlocked){
				position.x -= movementSpeed;
			}
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){
			lookingLeft = false;
			if (!rightBlocked){
				position.x += movementSpeed;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN){
			particle aux;
			aux.position.y = position.y - 13;
			aux.tex = App->graphics->playerGraphics;
			aux.speed.y = -1;
			aux.acceleration.x = 0;
			aux.acceleration.y = 0.1f;
			if (lookingLeft){
				aux.position.x = position.x - 5;
				if (bluePowerUp){
					aux.anim = App->graphics->playerBigShotLeft;
				}
				else{
					aux.anim = App->graphics->playerShotLeft;
				}
				if (yellowPowerUp){
					aux.speed.x = -4.6f;
				}
				else{
					aux.speed.x = -2.3f;
				}
			}
			else{
				aux.position.x = position.x + 25;
				if (bluePowerUp){
					aux.anim = App->graphics->playerBigShotRight;
				}
				else{
					aux.anim = App->graphics->playerShotRight;
				}
				if (yellowPowerUp){
					aux.speed.x = 4.6f;
				}
				else{
					aux.speed.x = 2.3f;
				}
			}
			App->particles->CreateParticle(aux, 1);
			shooting = true;
			App->audio->PlayFx(App->audioEffects->fireFx, 0);
			App->graphics->playerShootingLeft.reset();
		}
		break;
	case PLAYERPUSHING:
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT){
			lookingLeft = true;
			if (!leftBlocked){
				position.x-=movementSpeed;
			}
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){
			lookingLeft = false;
			if (!rightBlocked){
				position.x+=movementSpeed;
			}
		}
		else{
			status = PLAYERNONE;
		}
		if (!myFeetCollider->colliding){
			status = PLAYERFALLING;
		}
		else if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN){
			status = PLAYERJUMPING;
			App->audio->PlayFx(App->audioEffects->jumpFx, 0);
			jumpCommited = 0;
			if (lookingLeft)
				App->graphics->playerJumpLeft.reset();
			else
				App->graphics->playerJumpRight.reset();
		}
		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN){
			particle aux;
			aux.position.y = position.y - 13;
			aux.tex = App->graphics->playerGraphics;
			aux.speed.y = -1;
			aux.acceleration.x = 0;
			aux.acceleration.y = 0.1f;
			if (lookingLeft){
				aux.position.x = position.x - 5;
				if (bluePowerUp){
					aux.anim = App->graphics->playerBigShotLeft;
				}
				else{
					aux.anim = App->graphics->playerShotLeft;
				}
				if (yellowPowerUp){
					aux.speed.x = -4.6f;
				}
				else{
					aux.speed.x = -2.3f;
				}
			}
			else{
				aux.position.x = position.x + 25;
				if (bluePowerUp){
					aux.anim = App->graphics->playerBigShotRight;
				}
				else{
					aux.anim = App->graphics->playerShotRight;
				}
				if (yellowPowerUp){
					aux.speed.x = 4.6f;
				}
				else{
					aux.speed.x = 2.3f;
				}
			}
			App->particles->CreateParticle(aux, 1);
			shooting = true;
			App->audio->PlayFx(App->audioEffects->fireFx, 0);
			App->graphics->playerShootingLeft.reset();
		}
		break;
	case PLAYERBALLED:
		ball = App->enemy->ReturnOwner(numberBall);
		if (ball != NULL) {
			position.x = ball->position.x;
			position.y = App->enemy->ReturnOwner(numberBall)->position.y;
		}
		else{
			status = PLAYERJUMPING;
			App->audio->PlayFx(App->audioEffects->jumpFx, 0);
			jumpCommited = 0;
			immune = true;
			immuneTime = SDL_GetTicks();
			if (lookingLeft)
				App->graphics->playerJumpLeft.reset();
			else
				App->graphics->playerJumpRight.reset();
		}
		if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN){
			status = PLAYERJUMPING;
			App->audio->PlayFx(App->audioEffects->jumpFx, 0);
			jumpCommited = 0;
			immune = true;
			immuneTime = SDL_GetTicks();
			if (lookingLeft)
				App->graphics->playerJumpLeft.reset();
			else
				App->graphics->playerJumpRight.reset();
		}
		break;
	case PLAYERCHANGINGLEVEL:
		position.y -= 15;
		break;
	case PLAYERDYING:
		if (App->graphics->playerDying.hasFinished()){
			status = PLAYERDESTROYING; 
		}
		break;
	case PLAYERDESTROYING:
		if (relativePositionsDestroying >= 30){
			if (lives == 0){
				relativePositionsDestroying = 0;
				App->graphics->playerDying.reset();
				App->levels->Disable();
				App->fade->FadeToBlack(App->gameOver, nullptr, 3.0f);
			}
			else{
				lives--;
				ResetPlayer(App->levels->levelNumber);
				relativePositionsDestroying = 0;
				App->graphics->playerDying.reset();
			}
		}
		else{
			relativePositionsDestroying += 1;
			relativePositionsDestroyingState = (relativePositionsDestroyingState + 1) % 4;
		}
	default:
		break;
	}
	return UPDATE_CONTINUE;
}

// Update
update_status ModulePlayer::Update()
{
	if (App->graphics->playerShootingLeft.hasFinished()){
		App->graphics->playerShootingLeft.reset();
		App->graphics->playerShootingLeft.loops = 1;
		shooting = false;
	}
	if (App->graphics->playerShootingRight.hasFinished()){
		App->graphics->playerShootingRight.reset();
		App->graphics->playerShootingRight.loops = 1;
		shooting = false;
	}
	if (shooting){
		myCollider->collisionBox.w = App->graphics->playerIdleLeft.w;
		myCollider->collisionBox.h = App->graphics->playerIdleLeft.h;
		if (lookingLeft)
			App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - App->graphics->playerShootingLeft.GetCurrentFrame().h, &App->graphics->playerShootingLeft.GetCurrentFrame(),1,alpha); 
		else
			App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - App->graphics->playerShootingRight.GetCurrentFrame().h, &App->graphics->playerShootingRight.GetCurrentFrame(), 1, alpha); 
	}
	else{
		switch (status)
		{
		case PLAYERNONE:
			if (redPowerUp){
				if (lookingLeft){
					App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - (App->graphics->playerFastLeft.GetCurrentFrame()).h, &(App->graphics->playerFastLeft.GetCurrentFrame()), 1, alpha);
				}
				else{
					App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - (App->graphics->playerFastRight.GetCurrentFrame()).h, &(App->graphics->playerFastRight.GetCurrentFrame()), 1, alpha);
				}
			}
			else{
				if (lookingLeft){
					App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - App->graphics->playerIdleLeft.h, &App->graphics->playerIdleLeft, 1, alpha);
				}
				else{
					App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - App->graphics->playerIdleRight.h, &App->graphics->playerIdleRight, 1, alpha);
				}
			}
			myCollider->collisionBox.w = App->graphics->playerIdleLeft.w;
			myCollider->collisionBox.h = App->graphics->playerIdleLeft.h;
			break;
		case PLAYERMOVING:
			if (redPowerUp){
				if (lookingLeft){
					App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - (App->graphics->playerFastLeft.GetCurrentFrame()).h, &(App->graphics->playerFastLeft.GetCurrentFrame()), 1, alpha);
				}
				else{
					App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - (App->graphics->playerFastRight.GetCurrentFrame()).h, &(App->graphics->playerFastRight.GetCurrentFrame()), 1, alpha);
				}
			}
			else{
				if (lookingLeft){
					App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - (App->graphics->playerMoveLeft.GetCurrentFrame()).h, &(App->graphics->playerMoveLeft.GetCurrentFrame()), 1, alpha);
				}
				else{
					App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - (App->graphics->playerMoveRight.GetCurrentFrame()).h, &(App->graphics->playerMoveRight.GetCurrentFrame()), 1, alpha);
				}
			}
			myCollider->collisionBox.w = App->graphics->playerIdleLeft.w;
			myCollider->collisionBox.h = App->graphics->playerIdleLeft.h;
			break;
		case PLAYERJUMPING:
			if (lookingLeft){
				App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - App->graphics->playerJumpLeft.GetCurrentFrame().h, &App->graphics->playerJumpLeft.GetCurrentFrame(), 1, alpha); 
			}
			else{
				App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - App->graphics->playerJumpRight.GetCurrentFrame().h, &App->graphics->playerJumpRight.GetCurrentFrame(), 1, alpha); 
			}
			myCollider->collisionBox.w = App->graphics->playerIdleLeft.w;
			myCollider->collisionBox.h = App->graphics->playerIdleLeft.h;
			break;
		case PLAYERFALLING:
			if (lookingLeft)
				App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - App->graphics->playerFallingLeft.h, &App->graphics->playerFallingLeft, 1, alpha);
			else
				App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - App->graphics->playerFallingRight.h, &App->graphics->playerFallingRight, 1, alpha);
			myCollider->collisionBox.w = App->graphics->playerIdleLeft.w;
			myCollider->collisionBox.h = App->graphics->playerIdleLeft.h;
			break;
		case PLAYERPUSHING:
			if (redPowerUp){
				if (lookingLeft){
					App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - (App->graphics->playerFastPushingLeft.GetCurrentFrame()).h, &(App->graphics->playerFastPushingLeft.GetCurrentFrame()), 1, alpha);
				}
				else{
					App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - (App->graphics->playerFastPushingRight.GetCurrentFrame()).h, &(App->graphics->playerFastPushingRight.GetCurrentFrame()), 1, alpha);
				}
			}
			else{
				if (lookingLeft){
					App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - (App->graphics->playerPushingLeft.GetCurrentFrame()).h, &(App->graphics->playerPushingLeft.GetCurrentFrame()), 1, alpha);
				}
				else{
					App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - (App->graphics->playerPushingRight.GetCurrentFrame()).h, &(App->graphics->playerPushingRight.GetCurrentFrame()), 1, alpha);
				}
			}
			myCollider->collisionBox.w = App->graphics->playerIdleLeft.w;
			myCollider->collisionBox.h = App->graphics->playerIdleLeft.h;
			break;
		case PLAYERPUSHBALL:
			if (lookingLeft){
				App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - App->graphics->playerLastPushLeft.h, &(App->graphics->playerLastPushLeft), 1, alpha);
			}
			else{
				App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - App->graphics->playerLastPushRight.h, &(App->graphics->playerLastPushRight), 1, alpha);
			}
			status = PLAYERNONE;
			break;
		case PLAYERBALLED:
			myCollider->collisionBox.w = 0;
			myCollider->collisionBox.h = 0;
			App->renderer->Blit(App->graphics->playerGraphics, position.x-10, position.y - 35 - App->graphics->playerInBall.GetCurrentFrame().h, &App->graphics->playerInBall.GetCurrentFrame());
			break;
		case PLAYERCHANGINGLEVEL:
			App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - App->graphics->playerChangingLevel.GetCurrentFrame().h, &App->graphics->playerChangingLevel.GetCurrentFrame(), 1, alpha); 
			myCollider->collisionBox.w = App->graphics->playerIdleLeft.w;
			myCollider->collisionBox.h = App->graphics->playerIdleLeft.h;
			break;
		case PLAYERDYING:
			myCollider->collisionBox.w = 0;
			myCollider->collisionBox.h = 0;
			App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - App->graphics->playerDying.GetCurrentFrame().h, &App->graphics->playerDying.GetCurrentFrame(), 1, alpha); 
			break;
		case PLAYERDESTROYING:
			myCollider->collisionBox.w = 0;
			myCollider->collisionBox.h = 0;
			displayPlayerDestruction();
			break;
		default:
			break;
		}
		myCollider->collisionBox.x = position.x;
		myCollider->collisionBox.y = (position.y - App->graphics->playerIdleLeft.h);
		myFeetCollider->collisionBox.x = position.x;
		myFeetCollider->collisionBox.y = position.y; 
	}
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* a,Collider* b){
	if (a->type == PLAYERFEET){
		if (status == PLAYERFALLING){
			position.y = b->collisionBox.y;
			a->collisionBox.y = b->collisionBox.y;
		}
		if (a->collisionBox.y <= b->collisionBox.y )
			a->colliding = true;
	}
	else if (b->type == PLAYERFEET){
		if (status == PLAYERFALLING){
			position.y = a->collisionBox.y;
			b->collisionBox.y = a->collisionBox.y;
		}
		if (b->collisionBox.y <= a->collisionBox.y )
			b->colliding = true;
	}

	if (a->type == PLAYER){
		switch (b->type)
		{
		case ROLLINGBALL:
			if (!immune){
				numberBall = App->enemy->ReturnOwner(b)->enemynumber;
				status = PLAYERBALLED;
			}
			break;
		case ENEMY:
			if (!App->enemy->checkHarmingStatus(b)){
				break;
			}
		case ENEMYSHOT:
			if (!immune){
				status = PLAYERDYING;
				App->audio->PlayFx(App->audioEffects->playerDieFx);
			}
			break;
		case PLATFORMWALL:
			a->colliding = true;
			if (a->collisionBox.x < b->collisionBox.x){
				rightBlocked = true;
			}
			else if (a->collisionBox.x + a->collisionBox.w > b->collisionBox.x + b->collisionBox.w){
				leftBlocked = true;
			}
			else{
				leftBlocked = true;
				rightBlocked = true;
			}
			break;
		case WALL:
			a->colliding = true;
			if (a->collisionBox.x < b->collisionBox.x){
				rightBlocked = true;
			}
			else {
				leftBlocked = true;
			}
			break;
		case REDPOWERUP:
			redPowerUp = true;
			App->audio->PlayFx(App->audioEffects->objectFx);
			score += 1000;
			break;
		case YELLOWPOWERUP:
			yellowPowerUp = true;
			App->audio->PlayFx(App->audioEffects->objectFx);
			score += 1000;
			break;
		case BLUEPOWERUP:
			bluePowerUp = true;
			App->audio->PlayFx(App->audioEffects->objectFx);
			score += 1000;
			break;
		default:
			a->colliding = true;
			if (a->collisionBox.x <= b->collisionBox.x){
				if (!rightBlocked){
					position.x -= movementSpeed;
					rightBlocked = true;
				}
			}
			else{
				if (!leftBlocked){
					position.x += movementSpeed;
					leftBlocked = true;
				}
			}
			break;
		}
	}
	else if (b->type == PLAYER){
		switch (a->type)
		{
		case ROLLINGBALL:
			numberBall = App->enemy->ReturnOwner(a)->enemynumber;
			status = PLAYERBALLED;
			break;
		case ENEMY:
			if (!App->enemy->checkHarmingStatus(a)){
				break;
			}
		case ENEMYSHOT:
			if (!immune){
				status = PLAYERDYING;
				App->audio->PlayFx(App->audioEffects->playerDieFx);
			}
			break;
		case PLATFORMWALL:
			b->colliding = true;
			if (b->collisionBox.x < a->collisionBox.x){
				rightBlocked = true;
			}
			else if (b->collisionBox.x + b->collisionBox.w > a->collisionBox.x + a->collisionBox.w){
				leftBlocked = true;
			}
			else{
				leftBlocked = true;
				rightBlocked = true;
			}
			break;
		case WALL:
			a->colliding = true;
			if (a->collisionBox.x < b->collisionBox.x){
				rightBlocked = true;
			}
			else {
				leftBlocked = true;
			}
			break;
		case REDPOWERUP:
			redPowerUp = true;
			App->audio->PlayFx(App->audioEffects->objectFx);
			break;
		case YELLOWPOWERUP:
			yellowPowerUp = true;
			App->audio->PlayFx(App->audioEffects->objectFx);
			break;
		case BLUEPOWERUP:
			bluePowerUp = true;
			App->audio->PlayFx(App->audioEffects->objectFx);
			break;
		default:
			b->colliding = true;
			if (b->collisionBox.x <= a->collisionBox.x){
				if (!rightBlocked){
					position.x -= movementSpeed;
					rightBlocked = true;
				}
			}
			else{
				if (!leftBlocked){
					position.x += movementSpeed;
					leftBlocked = true;
				}
			}
			break;
		}
	}

}

//Sets the player in the correct position when he dies or the level starts
void ModulePlayer::ResetPlayer(int level,bool died){
	App->audio->PlayFx(App->audioEffects->appearFx);
	status = PLAYERNONE;
	lookingLeft = true;
	immune = true;
	immuneTime = SDL_GetTicks();
	if (died){
		redPowerUp = false;
		bluePowerUp = false;
		yellowPowerUp = false;
	}
	switch (level){
	case 1:
		position.x = 194;
		position.y = 838;
		break;
	case 2:
		position.x = 194;
		position.y = 387;
		break;
	}
}

void ModulePlayer::displayPlayerDestruction() const{
	switch (relativePositionsDestroyingState){
	case 0:
		App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - destroyingOffset + relativePositionsDestroying, &App->graphics->playerDestroying1);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying2);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying3);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->playerDestroying4);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying1);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying2);
		App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - destroyingOffset - relativePositionsDestroying, &App->graphics->playerDestroying3);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying4);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying1);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->playerDestroying2);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying3);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying4);
		break;
	case 1:
		App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - destroyingOffset + relativePositionsDestroying, &App->graphics->playerDestroying4);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying1);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying2);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->playerDestroying3);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying4);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying1);
		App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - destroyingOffset - relativePositionsDestroying, &App->graphics->playerDestroying2);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying3);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying4);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->playerDestroying1);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying2);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying3);
		break;
	case 2:
		App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - destroyingOffset + relativePositionsDestroying, &App->graphics->playerDestroying3);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying4);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying1);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->playerDestroying2);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying3);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying4);
		App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - destroyingOffset - relativePositionsDestroying, &App->graphics->playerDestroying1);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying2);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying3);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->playerDestroying4);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying1);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying2);
		break;
	case 3:
		App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - destroyingOffset + relativePositionsDestroying, &App->graphics->playerDestroying2);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying3);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying4);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->playerDestroying1);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying2);
		App->renderer->Blit(App->graphics->playerGraphics, position.x + relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying3);
		App->renderer->Blit(App->graphics->playerGraphics, position.x, position.y - destroyingOffset - relativePositionsDestroying, &App->graphics->playerDestroying4);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset - relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying1);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset - relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying2);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying, position.y - destroyingOffset, &App->graphics->playerDestroying3);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying*2.0f / 3.0f, position.y - destroyingOffset + relativePositionsDestroying / 3.0f, &App->graphics->playerDestroying4);
		App->renderer->Blit(App->graphics->playerGraphics, position.x - relativePositionsDestroying / 3.0f, position.y - destroyingOffset + relativePositionsDestroying*2.0f / 3.0f, &App->graphics->playerDestroying1);
		break;
	}
}

void ModulePlayer::SetPlayerFirstTime(){
	LOG("Setting player");

	firstTime = true;
	lives = 2;
	score = 0;

	SDL_Rect aux;
	myCollider->collisionBox.x = position.x;
	myCollider->collisionBox.y = (position.y - App->graphics->playerIdleLeft.h);
	myCollider->collisionBox.w = App->graphics->playerIdleLeft.w;
	myCollider->collisionBox.h = App->graphics->playerIdleLeft.h;

	myFeetCollider->collisionBox.x = position.x;
	myFeetCollider->collisionBox.y = position.y;
	myFeetCollider->collisionBox.w = App->graphics->playerIdleLeft.w;
	myFeetCollider->collisionBox.h = 2;

}
