#include "Application.h"
#include "ModuleEnemy.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"
#include "Graphics.h"
#include "Enemy.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "AudioEffects.h"
#include <vld.h>


ModuleEnemy::ModuleEnemy(bool start_enabled) : Module(start_enabled)
{
}

ModuleEnemy::~ModuleEnemy()
{
}

// Load assets
bool ModuleEnemy::Start()
{
	return true;
}


// Unload assets
bool ModuleEnemy::CleanUp()
{
	deleteEnemies();
	return true;
}

//LOGIC
update_status ModuleEnemy::PreUpdate(){
	

	for (list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		(*it)->PreUpdate();
	}
	return UPDATE_CONTINUE;
}

// DRAW
update_status ModuleEnemy::Update()
{
	
	for (list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		(*it)->Update();
	}
	return UPDATE_CONTINUE;

}


//Destruction of the marked enemies
update_status ModuleEnemy::PostUpdate(){
	list<Enemy*>::iterator it = enemies.begin();
	while (it != enemies.end()){
		if ((*it)->status == TOBEDESTROYED){
			(*it)->myCollider->flagRelease();
			(*it)->myFeetCollider->flagRelease();
			RELEASE(*it);
			it = enemies.erase(it);
		}
		else{
			++it;
		}
	}
	return UPDATE_CONTINUE;
}



void ModuleEnemy::OnCollision(Collider* a, Collider* b){
	//FEETS
	if (a->type == PLAYERFEET && !(a->flagErase)){
		switch (b->type){
		case SNOWBALL:
			break;
		default:
			if (checkCollidableStatus(a)){
				ReturnOwner(a)->position.y = b->collisionBox.y;
				a->collisionBox.y = b->collisionBox.y;
				a->colliding = true;
			}
			break;
		}
	}
	else if (b->type == PLAYERFEET && !(b->flagErase)){
		switch (a->type){
		case SNOWBALL:
			break;
		default:
			if (checkCollidableStatus(b)){
				ReturnOwner(b)->position.y = a->collisionBox.y;
				b->collisionBox.y = a->collisionBox.y;
				b->colliding = true;
			}
			break;
		}
	}



	//ENEMY
	if (a->type == ENEMY && !(a->flagErase)){
		switch (b->type){
		case PLAYERSHOT:
			if (checkCollidableStatus(a)){
				App->player->score += 10;
				ReturnOwner(a)->snowHit = true;
			}
			break;
		case ROLLINGBALL:
			if (checkCollidableStatus(a)){
				ReturnOwner(a)->status = TAKINGOFF;
				App->audio->PlayFx(App->audioEffects->flyEnemyFx);
				ReturnOwner(a)->jumpCommited = 0;
				switch (ReturnOwner(b)->enemyHitCount){
				case 0:
					App->player->score += 1000;
					++ReturnOwner(b)->enemyHitCount;
					break;
				case 1:
					App->player->score += 2000;
					++ReturnOwner(b)->enemyHitCount;
					break;
				case 2:
					App->player->score += 3000;
					++ReturnOwner(b)->enemyHitCount;
					break;
				}
			}
			break;
		case WALL:
		case PLATFORMWALL:
			if (a->collisionBox.x > b->collisionBox.x && a->collisionBox.x + a->collisionBox.w < b->collisionBox.x + b->collisionBox.w){}
			else if (a->collisionBox.x < b->collisionBox.x && !ReturnOwner(a)->lookingLeft){
				ReturnOwner(a)->lookingLeft = !ReturnOwner(a)->lookingLeft;
				if (ReturnOwner(a)->status == NONE){
					ReturnOwner(a)->status = SHOOTING;
				}
			}
			else if (a->collisionBox.x > b->collisionBox.x && ReturnOwner(a)->lookingLeft){
				ReturnOwner(a)->lookingLeft = !ReturnOwner(a)->lookingLeft;
				if (ReturnOwner(a)->status == NONE){
					ReturnOwner(a)->status = SHOOTING;
				}
			}
			break;
		case ENEMYTURN:
			if (ReturnOwner(a)->turn && checkHarmingStatus(a)){
				ReturnOwner(a)->status = SHOOTING;
				ReturnOwner(a)->lookingLeft = !ReturnOwner(a)->lookingLeft;
				ReturnOwner(a)->position.x -= ReturnOwner(a)->movementSpeed;
				ReturnOwner(a)->turn = false;
			}
			break;
		case ENEMYJUMP:
			if (checkHarmingStatus(a) && ReturnOwner(a)->status != JUMPING){
				ReturnOwner(a)->status = JUMPING;
				ReturnOwner(a)->jumpCommited = 0;
				ReturnOwner(a)->turn = true;
			}
			break;
		case ENEMY:
			if (checkCollidableStatus(a) && checkCollidableStatus(b)){
				if (a->collisionBox.x < b->collisionBox.x && !ReturnOwner(a)->lookingLeft && ReturnOwner(a)->status == NONE){
					ReturnOwner(a)->lookingLeft = !ReturnOwner(a)->lookingLeft;
					ReturnOwner(a)->status = SHOOTING;
				}
				else if (a->collisionBox.x > b->collisionBox.x && ReturnOwner(a)->lookingLeft && ReturnOwner(a)->status == NONE){
					ReturnOwner(a)->lookingLeft = !ReturnOwner(a)->lookingLeft;
					ReturnOwner(a)->status = SHOOTING;
				}
			}
			break;
		case CEILING:
			ReturnOwner(a)->flyingDown = true;
			break;
		case FLOOR:
			if (ReturnOwner(a)->status == FLYING){
				ReturnOwner(a)->status = LANDINGDEAD;
			}
			break;
		}
	}
	if (b->type == ENEMY && !(b->flagErase)){
		switch (a->type){
		case PLAYERSHOT:
			if (checkCollidableStatus(b)){
				App->player->score += 10;
				ReturnOwner(b)->snowHit = true;
			}
			break;
		case ROLLINGBALL:
			if (checkCollidableStatus(b)){
				ReturnOwner(b)->status = TAKINGOFF;
				App->audio->PlayFx(App->audioEffects->flyEnemyFx);
				ReturnOwner(b)->jumpCommited = 0;
				switch (ReturnOwner(a)->enemyHitCount){
				case 0:
					App->player->score += 1000;
					++ReturnOwner(a)->enemyHitCount;
					break;
				case 1:
					App->player->score += 2000;
					++ReturnOwner(a)->enemyHitCount;
					break;
				case 2:
					App->player->score += 3000;
					++ReturnOwner(a)->enemyHitCount;
					break;
				}
			}
			break;
		case WALL:
		case PLATFORMWALL:
			if (a->collisionBox.x > b->collisionBox.x && a->collisionBox.x + a->collisionBox.w < b->collisionBox.x + b->collisionBox.w){}
			else if (b->collisionBox.x < a->collisionBox.x && !ReturnOwner(b)->lookingLeft){
				ReturnOwner(b)->lookingLeft = !ReturnOwner(b)->lookingLeft;
				if (ReturnOwner(b)->status == NONE){
					ReturnOwner(b)->status = SHOOTING;
				}
			}
			else if (b->collisionBox.x > a->collisionBox.x && ReturnOwner(b)->lookingLeft){
				ReturnOwner(b)->lookingLeft = !ReturnOwner(b)->lookingLeft;
				if (ReturnOwner(b)->status == NONE){
					ReturnOwner(b)->status = SHOOTING;
				}
			}
			break;
		case ENEMYTURN:
			if ((ReturnOwner(b))->turn && checkHarmingStatus(b)){
				ReturnOwner(b)->status = SHOOTING;
				ReturnOwner(b)->lookingLeft = !ReturnOwner(b)->lookingLeft;
				ReturnOwner(b)->position.x -= ReturnOwner(b)->movementSpeed;
				ReturnOwner(b)->turn = false;
			}
			break;
		case ENEMYJUMP:
			if (checkHarmingStatus(b) && ReturnOwner(b)->status != JUMPING){
				ReturnOwner(b)->status = JUMPING;
				ReturnOwner(b)->jumpCommited = 0;
				ReturnOwner(b)->turn = true;
			}
			break;
		case ENEMY:
			if (checkCollidableStatus(a) && checkCollidableStatus(b)){
				if (b->collisionBox.x < a->collisionBox.x && !ReturnOwner(b)->lookingLeft && ReturnOwner(b)->status == NONE){
					ReturnOwner(b)->lookingLeft = !ReturnOwner(b)->lookingLeft;
					ReturnOwner(b)->status = SHOOTING;
				}
				else if (b->collisionBox.x > a->collisionBox.x && ReturnOwner(b)->lookingLeft && ReturnOwner(b)->status == NONE){
					ReturnOwner(b)->lookingLeft = !ReturnOwner(b)->lookingLeft;
					ReturnOwner(b)->status = SHOOTING;
				}
			}
			break;
		case CEILING:
			ReturnOwner(b)->flyingDown = true;
			break;
		case FLOOR:
			if (ReturnOwner(b)->status == FLYING){
				ReturnOwner(b)->status = LANDINGDEAD;
			}
			break;
		}
	}



	//SNOWBALL
	if (a->type == SNOWBALL && !(a->flagErase)){
		switch (b->type){
		case WALL:
		case PLATFORMWALL:
			if (a->collisionBox.x > b->collisionBox.x){
				ReturnOwner(a)->position.x += App->player->movementSpeed;
			}
			else{
				ReturnOwner(a)->position.x -= App->player->movementSpeed;
			}
		case PLAYERSHOT:
			ReturnOwner(a)->snowHit = true;
			break;
		case SNOWBALL:
			if (a->collisionBox.x > b->collisionBox.x){
				ReturnOwner(a)->position.x = ReturnOwner(b)->position.x + b->collisionBox.w;
			}
			else{
				ReturnOwner(b)->position.x = ReturnOwner(a)->position.x + a->collisionBox.w;
			}
			break;
		case ROLLINGBALL:
			if (a->collisionBox.x < b->collisionBox.x){
				ReturnOwner(a)->lookingLeft = true;
				ReturnOwner(a)->status = SNOWROLLING;
				a->type = ROLLINGBALL;
				ReturnOwner(b)->lookingLeft = false;
				App->player->score += 1000;
			}
			else{
				ReturnOwner(a)->lookingLeft = false;
				ReturnOwner(a)->status = SNOWROLLING;
				a->type = ROLLINGBALL;
				ReturnOwner(b)->lookingLeft = true;
				App->player->score += 1000;
			}
			break;
		case PLAYER:
			if (a->collisionBox.y-10 >b->collisionBox.y){}
			else {
				if (a->collisionBox.x < b->collisionBox.x){
					if (App->player->shooting || App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT){
						App->audio->PlayFx(App->audioEffects->pushFx);
						ReturnOwner(a)->status = SNOWROLLING;
						ReturnOwner(a)->lookingLeft = true;
						a->type = ROLLINGBALL;
						App->player->score += 500;
						App->player->status = PLAYERPUSHBALL;
					}
					else{
						App->player->status = PLAYERPUSHING;
						ReturnOwner(a)->position.x -= App->player->movementSpeed;
					}
				}
				else if (a->collisionBox.x > b->collisionBox.x){
					if (App->player->shooting || App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT){
						App->audio->PlayFx(App->audioEffects->pushFx);
						ReturnOwner(a)->status = SNOWROLLING;
						ReturnOwner(a)->lookingLeft = false;
						a->type = ROLLINGBALL;
						App->player->score += 500;
						App->player->status = PLAYERPUSHBALL;
					}
					else{
						App->player->status = PLAYERPUSHING;
						ReturnOwner(a)->position.x += App->player->movementSpeed;
					}
				}
			}
			break;
		}
	}
	if (b->type == SNOWBALL && !(b->flagErase)){
		switch (a->type){
		case WALL:
		case PLATFORMWALL:
			if (b->collisionBox.x > a->collisionBox.x){
				ReturnOwner(b)->position.x += App->player->movementSpeed;
			}
			else{
				ReturnOwner(b)->position.x -= App->player->movementSpeed;
			}
		case PLAYERSHOT:
			ReturnOwner(b)->snowHit = true;
			break;
		case ROLLINGBALL:
			if (b->collisionBox.x < b->collisionBox.x){
				ReturnOwner(b)->lookingLeft = true;
				ReturnOwner(b)->status = SNOWROLLING;
				b->type = ROLLINGBALL;
				ReturnOwner(a)->lookingLeft = false;
				App->player->score += 1000;
			}
			else{
				ReturnOwner(b)->lookingLeft = false;
				ReturnOwner(b)->status = SNOWROLLING;
				b->type = ROLLINGBALL;
				ReturnOwner(a)->lookingLeft = true;
				App->player->score += 1000;
			}
			break;
		case PLAYER:
			if (b->collisionBox.y-10 >a->collisionBox.y ){}
			else {
				if (b->collisionBox.x < a->collisionBox.x){
					if (App->player->shooting || App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT){
						App->audio->PlayFx(App->audioEffects->pushFx);
						ReturnOwner(b)->status = SNOWROLLING;
						ReturnOwner(b)->lookingLeft = true;
						b->type = ROLLINGBALL;
						App->player->score += 500;
						App->player->status = PLAYERPUSHBALL;
					}
					else{
						App->player->status = PLAYERPUSHING;
						ReturnOwner(b)->position.x -= App->player->movementSpeed;
					}
				}
				else if (b->collisionBox.x > a->collisionBox.x){
					if (App->player->shooting || App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT){
						App->audio->PlayFx(App->audioEffects->pushFx);
						ReturnOwner(b)->status = SNOWROLLING;
						ReturnOwner(b)->lookingLeft = false;
						b->type = ROLLINGBALL;
						App->player->score += 500;
						App->player->status = PLAYERPUSHBALL;
					}
					else{
						App->player->status = PLAYERPUSHING;
						ReturnOwner(b)->position.x += App->player->movementSpeed;
					}
				}
			}
			break;
		}
	}



	//ROLLINGSNOWBALL
	if (a->type == ROLLINGBALL && !(a->flagErase)){
		switch (b->type){
		case ROLLINGBALL:
			ReturnOwner(a)->lookingLeft = !ReturnOwner(a)->lookingLeft;
			break;
		case WALL:
			if ((ReturnOwner(a)->position.y == 839 || ReturnOwner(a)->position.y == 388) && checkCollidableStatus(a)){
				App->audio->PlayFx(App->audioEffects->ballDieFx,0);
				ReturnOwner(a)->status = SNOWDESTROYING;
				if (App->player->status == PLAYERBALLED && App->player->numberBall == ReturnOwner(a)->enemynumber){
					App->player->status = PLAYERJUMPING;
					App->player->immune = true;
					App->player->immuneTime = SDL_GetTicks();
				}
				break;
			}
		case PLATFORMWALL:
			if (a->collisionBox.x >= b->collisionBox.x){
				++ReturnOwner(a)->position.x;
			}
			else{
				--ReturnOwner(a)->position.x;
			}
			ReturnOwner(a)->lookingLeft = !ReturnOwner(a)->lookingLeft;
			App->audio->PlayFx(App->audioEffects->bounceBallFx,0);
			break;
		}
	}
	if (b->type == ROLLINGBALL && !(b->flagErase)){
		switch (a->type){
		case ROLLINGBALL:
			ReturnOwner(b)->lookingLeft = !ReturnOwner(b)->lookingLeft;
			break;
		case WALL:
			if ((ReturnOwner(b)->position.y == 839 || ReturnOwner(b)->position.y == 388) && checkCollidableStatus(b)){
				App->audio->PlayFx(App->audioEffects->ballDieFx,0);
				ReturnOwner(b)->status = SNOWDESTROYING;
				if (App->player->status == PLAYERBALLED && App->player->numberBall == ReturnOwner(b)->enemynumber){
					App->player->status = PLAYERJUMPING;
					App->player->immune = true;
					App->player->immuneTime = SDL_GetTicks();
				}
			}
		case PLATFORMWALL:
			if (b->collisionBox.x >= a->collisionBox.x){
				++ReturnOwner(b)->position.x;
			}
			else{
				--ReturnOwner(b)->position.x;
			}
			ReturnOwner(b)->lookingLeft = !ReturnOwner(b)->lookingLeft;
			App->audio->PlayFx(App->audioEffects->bounceBallFx,0);
			break;
		}
	}
}


//Auxiliar function to set the enemies in each level
void ModuleEnemy::setEnemies(int level){
	switch (level){
	case 1:
		enemies.push_back(new Enemy(1));
		enemies.push_back(new Enemy(2));
		enemies.push_back(new Enemy(3));
		enemies.push_back(new Enemy(4));
		break;
	case 2:
		enemies.push_back(new Enemy(5));
		enemies.push_back(new Enemy(6));
		break;
	}
}

//Auxiliar function that returns the enemy correspondent to the given collider(feet or body)
Enemy* ModuleEnemy::ReturnOwner(Collider* a)const{
	for (list<Enemy*>::const_iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (a == (*it)->myCollider || a == (*it)->myFeetCollider){
			return *it;
		}
	}
}

//Auxiliar function that returns the enemy given its number
Enemy* ModuleEnemy::ReturnOwner(int number)const{
	for (list<Enemy*>::const_iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		if ((*it)->enemynumber==number){
			return *it;
		}
	}
	return NULL;
}

//Checks if the enemy has to collide against other things apart from walls floor and ceiling
bool ModuleEnemy::checkCollidableStatus(Collider* a)const{
	switch (ReturnOwner(a)->status){
	case FLYING:
	case LANDINGDEAD:
	case TAKINGOFF:
	case TOBEDESTROYED:
		return false;
	default:
		return true;
	}
}

//Checks if the enemy may move or hurt the player, in not collidable status, it can't hurt
bool ModuleEnemy::checkHarmingStatus(Collider* a)const{
	switch (ReturnOwner(a)->status){
	case SNOW1:
	case SNOW2:
	case SNOW3:
	case SNOW4:
		return false;
		break;
	default:
		return checkCollidableStatus(a);
		break;
	}
}

void ModuleEnemy::deleteEnemies(){
	list<Enemy*>::iterator it = enemies.begin();
	while (it != enemies.end()){
		RELEASE(*it);
		it = enemies.erase(it);
	}
}
