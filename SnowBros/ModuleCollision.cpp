#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleRender.h"

ModuleCollision::ModuleCollision(){
	//Set the collisions matrix
	possibleCollisions[PLAYER][PLAYER] = false;
	possibleCollisions[PLAYER][PLAYERFEET] = false;
	possibleCollisions[PLAYER][PLAYERSHOT] = false;
	possibleCollisions[PLAYER][ENEMY] = true;
	possibleCollisions[PLAYER][ENEMYSHOT] = true;
	possibleCollisions[PLAYER][SNOWBALL] = true;
	possibleCollisions[PLAYER][WALL] = true;
	possibleCollisions[PLAYER][PLATFORM] = false;
	possibleCollisions[PLAYER][ROLLINGBALL] = true;
	possibleCollisions[PLAYER][CEILING] = false;
	possibleCollisions[PLAYER][FLOOR] = false;
	possibleCollisions[PLAYER][PLATFORMWALL] = true;
	possibleCollisions[PLAYER][ENEMYTURN] = false;
	possibleCollisions[PLAYER][ENEMYJUMP] = false;
	possibleCollisions[PLAYER][REDPOWERUP] = true;
	possibleCollisions[PLAYER][BLUEPOWERUP] = true;
	possibleCollisions[PLAYER][YELLOWPOWERUP] = true;

	possibleCollisions[PLAYERFEET][PLAYER] = false;
	possibleCollisions[PLAYERFEET][PLAYERFEET] = false;
	possibleCollisions[PLAYERFEET][PLAYERSHOT] = false;
	possibleCollisions[PLAYERFEET][ENEMY] = false;
	possibleCollisions[PLAYERFEET][ENEMYSHOT] = false;
	possibleCollisions[PLAYERFEET][SNOWBALL] = true;
	possibleCollisions[PLAYERFEET][WALL] = false;
	possibleCollisions[PLAYERFEET][PLATFORM] = true;
	possibleCollisions[PLAYERFEET][ROLLINGBALL] = false;
	possibleCollisions[PLAYERFEET][CEILING] = false;
	possibleCollisions[PLAYERFEET][FLOOR] = true;
	possibleCollisions[PLAYERFEET][PLATFORMWALL] = false;
	possibleCollisions[PLAYERFEET][ENEMYTURN] = false;
	possibleCollisions[PLAYERFEET][ENEMYJUMP] = false;
	possibleCollisions[PLAYERFEET][REDPOWERUP] = false;
	possibleCollisions[PLAYERFEET][BLUEPOWERUP] = false;
	possibleCollisions[PLAYERFEET][YELLOWPOWERUP] = false;

	possibleCollisions[PLAYERSHOT][PLAYER] = false;
	possibleCollisions[PLAYERSHOT][PLAYERFEET] = false;
	possibleCollisions[PLAYERSHOT][PLAYERSHOT] = false;
	possibleCollisions[PLAYERSHOT][ENEMY] = true;
	possibleCollisions[PLAYERSHOT][ENEMYSHOT] = false;
	possibleCollisions[PLAYERSHOT][SNOWBALL] = true;
	possibleCollisions[PLAYERSHOT][WALL] = true;
	possibleCollisions[PLAYERSHOT][PLATFORM] = true;
	possibleCollisions[PLAYERSHOT][ROLLINGBALL] = false;
	possibleCollisions[PLAYERSHOT][CEILING] = false;
	possibleCollisions[PLAYERSHOT][FLOOR] = true;
	possibleCollisions[PLAYERSHOT][PLATFORMWALL] = true;
	possibleCollisions[PLAYERSHOT][ENEMYTURN] = false;
	possibleCollisions[PLAYERSHOT][ENEMYJUMP] = false;
	possibleCollisions[PLAYERSHOT][REDPOWERUP] = false;
	possibleCollisions[PLAYERSHOT][BLUEPOWERUP] = false;
	possibleCollisions[PLAYERSHOT][YELLOWPOWERUP] = false;

	possibleCollisions[ENEMY][PLAYER] = true;
	possibleCollisions[ENEMY][PLAYERFEET] = false;
	possibleCollisions[ENEMY][PLAYERSHOT] = true;
	possibleCollisions[ENEMY][ENEMY] = true;
	possibleCollisions[ENEMY][ENEMYSHOT] = false;
	possibleCollisions[ENEMY][SNOWBALL] = true;
	possibleCollisions[ENEMY][WALL] = true;
	possibleCollisions[ENEMY][PLATFORM] = false;
	possibleCollisions[ENEMY][ROLLINGBALL] = true;
	possibleCollisions[ENEMY][CEILING] = true;
	possibleCollisions[ENEMY][FLOOR] = true;
	possibleCollisions[ENEMY][PLATFORMWALL] = true;
	possibleCollisions[ENEMY][ENEMYTURN] = true;
	possibleCollisions[ENEMY][ENEMYJUMP] = true;
	possibleCollisions[ENEMY][REDPOWERUP] = false;
	possibleCollisions[ENEMY][BLUEPOWERUP] = false;
	possibleCollisions[ENEMY][YELLOWPOWERUP] = false;
	
	possibleCollisions[ENEMYSHOT][PLAYER] = true;
	possibleCollisions[ENEMYSHOT][PLAYERFEET] = false;
	possibleCollisions[ENEMYSHOT][PLAYERSHOT] = false;
	possibleCollisions[ENEMYSHOT][ENEMY] = false;
	possibleCollisions[ENEMYSHOT][ENEMYSHOT] = false;
	possibleCollisions[ENEMYSHOT][SNOWBALL] = true;
	possibleCollisions[ENEMYSHOT][WALL] = true;
	possibleCollisions[ENEMYSHOT][PLATFORM] = false;
	possibleCollisions[ENEMYSHOT][ROLLINGBALL] = false;
	possibleCollisions[ENEMYSHOT][CEILING] = false;
	possibleCollisions[ENEMYSHOT][FLOOR] = false;
	possibleCollisions[ENEMYSHOT][PLATFORMWALL] = true;
	possibleCollisions[ENEMYSHOT][ENEMYTURN] = false;
	possibleCollisions[ENEMYSHOT][ENEMYJUMP] = false;
	possibleCollisions[ENEMYSHOT][REDPOWERUP] = false;
	possibleCollisions[ENEMYSHOT][BLUEPOWERUP] = false;
	possibleCollisions[ENEMYSHOT][YELLOWPOWERUP] = false;

	possibleCollisions[SNOWBALL][PLAYER] = true;
	possibleCollisions[SNOWBALL][PLAYERFEET] = true;
	possibleCollisions[SNOWBALL][PLAYERSHOT] = true;
	possibleCollisions[SNOWBALL][ENEMY] = true;
	possibleCollisions[SNOWBALL][ENEMYSHOT] = true;
	possibleCollisions[SNOWBALL][SNOWBALL] = true;
	possibleCollisions[SNOWBALL][WALL] = true;
	possibleCollisions[SNOWBALL][PLATFORM] = true;
	possibleCollisions[SNOWBALL][ROLLINGBALL] = true;
	possibleCollisions[SNOWBALL][CEILING] = false;
	possibleCollisions[SNOWBALL][FLOOR] = false;
	possibleCollisions[SNOWBALL][PLATFORMWALL] = true;
	possibleCollisions[SNOWBALL][ENEMYTURN] = false;
	possibleCollisions[SNOWBALL][ENEMYJUMP] = false;
	possibleCollisions[SNOWBALL][REDPOWERUP] = false;
	possibleCollisions[SNOWBALL][BLUEPOWERUP] = false;
	possibleCollisions[SNOWBALL][YELLOWPOWERUP] = false;

	possibleCollisions[WALL][PLAYER] = true;
	possibleCollisions[WALL][PLAYERFEET] = false;
	possibleCollisions[WALL][PLAYERSHOT] = true;
	possibleCollisions[WALL][ENEMY] = true;
	possibleCollisions[WALL][ENEMYSHOT] = true;
	possibleCollisions[WALL][SNOWBALL] = true;
	possibleCollisions[WALL][WALL] = false;
	possibleCollisions[WALL][PLATFORM] = false;
	possibleCollisions[WALL][ROLLINGBALL] = true;
	possibleCollisions[WALL][CEILING] = false;
	possibleCollisions[WALL][FLOOR] = false;
	possibleCollisions[WALL][PLATFORMWALL] = false;
	possibleCollisions[WALL][ENEMYTURN] = false;
	possibleCollisions[WALL][ENEMYJUMP] = false;
	possibleCollisions[WALL][REDPOWERUP] = false;
	possibleCollisions[WALL][BLUEPOWERUP] = false;
	possibleCollisions[WALL][YELLOWPOWERUP] = false;

	possibleCollisions[PLATFORM][PLAYER] = false;
	possibleCollisions[PLATFORM][PLAYERFEET] = true;
	possibleCollisions[PLATFORM][PLAYERSHOT] = true;
	possibleCollisions[PLATFORM][ENEMY] = false;
	possibleCollisions[PLATFORM][ENEMYSHOT] = false;
	possibleCollisions[PLATFORM][SNOWBALL] = true;
	possibleCollisions[PLATFORM][WALL] = false;
	possibleCollisions[PLATFORM][PLATFORM] = false;
	possibleCollisions[PLATFORM][ROLLINGBALL] = false;
	possibleCollisions[PLATFORM][CEILING] = false;
	possibleCollisions[PLATFORM][FLOOR] = false;
	possibleCollisions[PLATFORM][PLATFORMWALL] = false;
	possibleCollisions[PLATFORM][ENEMYTURN] = false;
	possibleCollisions[PLATFORM][ENEMYJUMP] = false;
	possibleCollisions[PLATFORM][REDPOWERUP] = false;
	possibleCollisions[PLATFORM][BLUEPOWERUP] = false;
	possibleCollisions[PLATFORM][YELLOWPOWERUP] = false;

	possibleCollisions[ROLLINGBALL][PLAYER] = true;
	possibleCollisions[ROLLINGBALL][PLAYERFEET] = false;
	possibleCollisions[ROLLINGBALL][PLAYERSHOT] = false;
	possibleCollisions[ROLLINGBALL][ENEMY] = true;
	possibleCollisions[ROLLINGBALL][ENEMYSHOT] = false;
	possibleCollisions[ROLLINGBALL][SNOWBALL] = true;
	possibleCollisions[ROLLINGBALL][WALL] = true;
	possibleCollisions[ROLLINGBALL][PLATFORM] = false;
	possibleCollisions[ROLLINGBALL][ROLLINGBALL] = true;
	possibleCollisions[ROLLINGBALL][CEILING] = false;
	possibleCollisions[ROLLINGBALL][FLOOR] = false;
	possibleCollisions[ROLLINGBALL][PLATFORMWALL] = true;
	possibleCollisions[ROLLINGBALL][ENEMYTURN] = false;
	possibleCollisions[ROLLINGBALL][ENEMYJUMP] = false;
	possibleCollisions[ROLLINGBALL][REDPOWERUP] = false;
	possibleCollisions[ROLLINGBALL][BLUEPOWERUP] = false;
	possibleCollisions[ROLLINGBALL][YELLOWPOWERUP] = false;

	possibleCollisions[CEILING][PLAYER] = false;
	possibleCollisions[CEILING][PLAYERFEET] = false;
	possibleCollisions[CEILING][PLAYERSHOT] = false;
	possibleCollisions[CEILING][ENEMY] = true;
	possibleCollisions[CEILING][ENEMYSHOT] = false;
	possibleCollisions[CEILING][SNOWBALL] = false;
	possibleCollisions[CEILING][WALL] = false;
	possibleCollisions[CEILING][PLATFORM] = false;
	possibleCollisions[CEILING][ROLLINGBALL] = false;
	possibleCollisions[CEILING][CEILING] = false;
	possibleCollisions[CEILING][FLOOR] = false;
	possibleCollisions[CEILING][PLATFORMWALL] = false;
	possibleCollisions[CEILING][ENEMYTURN] = false;
	possibleCollisions[CEILING][ENEMYJUMP] = false;
	possibleCollisions[CEILING][REDPOWERUP] = false;
	possibleCollisions[CEILING][BLUEPOWERUP] = false;
	possibleCollisions[CEILING][YELLOWPOWERUP] = false;

	possibleCollisions[FLOOR][PLAYER] = false;
	possibleCollisions[FLOOR][PLAYERFEET] = true;
	possibleCollisions[FLOOR][PLAYERSHOT] = true;
	possibleCollisions[FLOOR][ENEMY] = true;
	possibleCollisions[FLOOR][ENEMYSHOT] = false;
	possibleCollisions[FLOOR][SNOWBALL] = false;
	possibleCollisions[FLOOR][WALL] = false;
	possibleCollisions[FLOOR][PLATFORM] = false;
	possibleCollisions[FLOOR][ROLLINGBALL] = false;
	possibleCollisions[FLOOR][CEILING] = false;
	possibleCollisions[FLOOR][FLOOR] = false;
	possibleCollisions[FLOOR][PLATFORMWALL] = false;
	possibleCollisions[FLOOR][ENEMYTURN] = false;
	possibleCollisions[FLOOR][ENEMYJUMP] = false;
	possibleCollisions[FLOOR][REDPOWERUP] = false;
	possibleCollisions[FLOOR][BLUEPOWERUP] = false;
	possibleCollisions[FLOOR][YELLOWPOWERUP] = false;

	possibleCollisions[PLATFORMWALL][PLAYER] = true;
	possibleCollisions[PLATFORMWALL][PLAYERFEET] = false;
	possibleCollisions[PLATFORMWALL][PLAYERSHOT] = true;
	possibleCollisions[PLATFORMWALL][ENEMY] = true;
	possibleCollisions[PLATFORMWALL][ENEMYSHOT] = true;
	possibleCollisions[PLATFORMWALL][SNOWBALL] = true;
	possibleCollisions[PLATFORMWALL][WALL] = false;
	possibleCollisions[PLATFORMWALL][PLATFORM] = false;
	possibleCollisions[PLATFORMWALL][ROLLINGBALL] = true;
	possibleCollisions[PLATFORMWALL][CEILING] = false;
	possibleCollisions[PLATFORMWALL][FLOOR] = false;
	possibleCollisions[PLATFORMWALL][PLATFORMWALL] = false;
	possibleCollisions[PLATFORMWALL][ENEMYTURN] = false;
	possibleCollisions[PLATFORMWALL][ENEMYJUMP] = false;
	possibleCollisions[PLATFORMWALL][REDPOWERUP] = false;
	possibleCollisions[PLATFORMWALL][BLUEPOWERUP] = false;
	possibleCollisions[PLATFORMWALL][YELLOWPOWERUP] = false;

	possibleCollisions[ENEMYTURN][PLAYER] = false;
	possibleCollisions[ENEMYTURN][PLAYERFEET] = false;
	possibleCollisions[ENEMYTURN][PLAYERSHOT] = false;
	possibleCollisions[ENEMYTURN][ENEMY] = true;
	possibleCollisions[ENEMYTURN][ENEMYSHOT] = false;
	possibleCollisions[ENEMYTURN][SNOWBALL] = false;
	possibleCollisions[ENEMYTURN][WALL] = false;
	possibleCollisions[ENEMYTURN][PLATFORM] = false;
	possibleCollisions[ENEMYTURN][ROLLINGBALL] = false;
	possibleCollisions[ENEMYTURN][CEILING] = false;
	possibleCollisions[ENEMYTURN][FLOOR] = false;
	possibleCollisions[ENEMYTURN][PLATFORMWALL] = false;
	possibleCollisions[ENEMYTURN][ENEMYTURN] = false;
	possibleCollisions[ENEMYTURN][ENEMYJUMP] = false;
	possibleCollisions[ENEMYTURN][REDPOWERUP] = false;
	possibleCollisions[ENEMYTURN][BLUEPOWERUP] = false;
	possibleCollisions[ENEMYTURN][YELLOWPOWERUP] = false;

	possibleCollisions[ENEMYJUMP][PLAYER] = false;
	possibleCollisions[ENEMYJUMP][PLAYERFEET] = false;
	possibleCollisions[ENEMYJUMP][PLAYERSHOT] = false;
	possibleCollisions[ENEMYJUMP][ENEMY] = true;
	possibleCollisions[ENEMYJUMP][ENEMYSHOT] = false;
	possibleCollisions[ENEMYJUMP][SNOWBALL] = false;
	possibleCollisions[ENEMYJUMP][WALL] = false;
	possibleCollisions[ENEMYJUMP][PLATFORM] = false;
	possibleCollisions[ENEMYJUMP][ROLLINGBALL] = false;
	possibleCollisions[ENEMYJUMP][CEILING] = false;
	possibleCollisions[ENEMYJUMP][FLOOR] = false;
	possibleCollisions[ENEMYJUMP][PLATFORMWALL] = false;
	possibleCollisions[ENEMYJUMP][ENEMYTURN] = false;
	possibleCollisions[ENEMYJUMP][ENEMYJUMP] = false;
	possibleCollisions[ENEMYJUMP][REDPOWERUP] = false;
	possibleCollisions[ENEMYJUMP][BLUEPOWERUP] = false;
	possibleCollisions[ENEMYJUMP][YELLOWPOWERUP] = false;

	possibleCollisions[REDPOWERUP][PLAYER] = true;
	possibleCollisions[REDPOWERUP][PLAYERFEET] = false;
	possibleCollisions[REDPOWERUP][PLAYERSHOT] = false;
	possibleCollisions[REDPOWERUP][ENEMY] = false;
	possibleCollisions[REDPOWERUP][ENEMYSHOT] = false;
	possibleCollisions[REDPOWERUP][SNOWBALL] = false;
	possibleCollisions[REDPOWERUP][WALL] = false;
	possibleCollisions[REDPOWERUP][PLATFORM] = false;
	possibleCollisions[REDPOWERUP][ROLLINGBALL] = false;
	possibleCollisions[REDPOWERUP][CEILING] = false;
	possibleCollisions[REDPOWERUP][FLOOR] = false;
	possibleCollisions[REDPOWERUP][PLATFORMWALL] = false;
	possibleCollisions[REDPOWERUP][ENEMYTURN] = false;
	possibleCollisions[REDPOWERUP][ENEMYJUMP] = false;
	possibleCollisions[REDPOWERUP][REDPOWERUP] = false;
	possibleCollisions[REDPOWERUP][BLUEPOWERUP] = false;
	possibleCollisions[REDPOWERUP][YELLOWPOWERUP] = false;

	possibleCollisions[BLUEPOWERUP][PLAYER] = true;
	possibleCollisions[BLUEPOWERUP][PLAYERFEET] = false;
	possibleCollisions[BLUEPOWERUP][PLAYERSHOT] = false;
	possibleCollisions[BLUEPOWERUP][ENEMY] = false;
	possibleCollisions[BLUEPOWERUP][ENEMYSHOT] = false;
	possibleCollisions[BLUEPOWERUP][SNOWBALL] = false;
	possibleCollisions[BLUEPOWERUP][WALL] = false;
	possibleCollisions[BLUEPOWERUP][PLATFORM] = false;
	possibleCollisions[BLUEPOWERUP][ROLLINGBALL] = false;
	possibleCollisions[BLUEPOWERUP][CEILING] = false;
	possibleCollisions[BLUEPOWERUP][FLOOR] = false;
	possibleCollisions[BLUEPOWERUP][PLATFORMWALL] = false;
	possibleCollisions[BLUEPOWERUP][ENEMYTURN] = false;
	possibleCollisions[BLUEPOWERUP][ENEMYJUMP] = false;
	possibleCollisions[BLUEPOWERUP][REDPOWERUP] = false;
	possibleCollisions[BLUEPOWERUP][BLUEPOWERUP] = false;
	possibleCollisions[BLUEPOWERUP][YELLOWPOWERUP] = false;

	possibleCollisions[YELLOWPOWERUP][PLAYER] = true;
	possibleCollisions[YELLOWPOWERUP][PLAYERFEET] = false;
	possibleCollisions[YELLOWPOWERUP][PLAYERSHOT] = false;
	possibleCollisions[YELLOWPOWERUP][ENEMY] = false;
	possibleCollisions[YELLOWPOWERUP][ENEMYSHOT] = false;
	possibleCollisions[YELLOWPOWERUP][SNOWBALL] = false;
	possibleCollisions[YELLOWPOWERUP][WALL] = false;
	possibleCollisions[YELLOWPOWERUP][PLATFORM] = false;
	possibleCollisions[YELLOWPOWERUP][ROLLINGBALL] = false;
	possibleCollisions[YELLOWPOWERUP][CEILING] = false;
	possibleCollisions[YELLOWPOWERUP][FLOOR] = false;
	possibleCollisions[YELLOWPOWERUP][PLATFORMWALL] = false;
	possibleCollisions[YELLOWPOWERUP][ENEMYTURN] = false;
	possibleCollisions[YELLOWPOWERUP][REDPOWERUP] = false;
	possibleCollisions[YELLOWPOWERUP][BLUEPOWERUP] = false;
	possibleCollisions[YELLOWPOWERUP][YELLOWPOWERUP] = false;
}

ModuleCollision::~ModuleCollision(){
}

Collider* ModuleCollision::CreateCollider(SDL_Rect box,Module* m,colliderType type){
	Collider* a = new Collider(box, m,type);
	setOfColliders.push_back(a);
	return a;
}

update_status ModuleCollision::PreUpdate(){
	//Release the marked colliders and set the rest to not colliding
	list<Collider*>::iterator it = setOfColliders.begin();
	while (it!=setOfColliders.end()){
		if ((*it)->flagErase){
			RELEASE(*it);
			it = setOfColliders.erase(it);
		}
		else{
			(*it)->colliding = false;
			++it;
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModuleCollision::Update(){
	list<Collider*>::iterator it;
	list<Collider*>::iterator it2;
	for (it = setOfColliders.begin(); it != setOfColliders.end(); it++){
		it2 = it;
		advance(it2, 1);
		for (it2; it2 != setOfColliders.end(); it2++){
			if (DetectCollision((*it)->collisionBox, (*it2)->collisionBox)){
				if (possibleCollisions[(*it)->type][(*it2)->type]){
					switch ((*it)->colliderStatus){
						case OUT:
						case EXITING:
							(*it)->colliderStatus= ENTERING;
							(*it)->mod->OnCollision(*it, *it2);
							break;
						case ENTERING:
						case IN:
							(*it)->colliderStatus= IN;
							(*it)->mod->OnCollision(*it, *it2);
							break;
					}
					switch ((*it2)->colliderStatus){
						case OUT:
						case EXITING:
							(*it2)->colliderStatus = ENTERING;
							(*it2)->mod->OnCollision(*it, *it2);
							break;
						case ENTERING:
						case IN:
							(*it2)->colliderStatus = IN;
							(*it2)->mod->OnCollision(*it, *it2);
							break;
					}
				}
			}
		}
	}
	for (it = setOfColliders.begin(); it != setOfColliders.end(); it++){
		if (!(*it)->colliding){
			switch ((*it)->colliderStatus){
			case OUT:
			case EXITING:
				(*it)->colliderStatus = OUT;
				break;
			case ENTERING:
			case IN:
				(*it)->colliderStatus = EXITING;
				break;
			}
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModuleCollision::PostUpdate(){
	if (App->debugMode){
		list<Collider*>::iterator it;
		for (it = setOfColliders.begin(); it != setOfColliders.end(); ++it){
			switch ((*it)->type)
			{
			case PLAYER:
				App->renderer->DrawRect((*it)->collisionBox, 102, 204, 0, TRANSPARENTALPHA);
				break;
			case PLAYERFEET:
				App->renderer->DrawRect((*it)->collisionBox, 255, 255, 255, TRANSPARENTALPHA);
				break; 
			case PLAYERSHOT:
				App->renderer->DrawRect((*it)->collisionBox, 51, 102, 0, TRANSPARENTALPHA);
				break;
			case ENEMY:
				App->renderer->DrawRect((*it)->collisionBox, 255, 0, 0,TRANSPARENTALPHA);
				break;
			case ENEMYSHOT:
				App->renderer->DrawRect((*it)->collisionBox, 153, 0, 0,TRANSPARENTALPHA);
				break;
			case SNOWBALL:
				App->renderer->DrawRect((*it)->collisionBox, 255, 255, 0,TRANSPARENTALPHA);
				break;
			case WALL:
				App->renderer->DrawRect((*it)->collisionBox, 0, 0, 153,TRANSPARENTALPHA);
				break;
			case PLATFORM:
				App->renderer->DrawRect((*it)->collisionBox, 51, 153, 255,TRANSPARENTALPHA);
				break;
			case ROLLINGBALL:
				App->renderer->DrawRect((*it)->collisionBox, 0, 0, 0,TRANSPARENTALPHA);
			case CEILING:
				App->renderer->DrawRect((*it)->collisionBox, 255, 255, 255,TRANSPARENTALPHA);
			default:
				App->renderer->DrawRect((*it)->collisionBox, 255, 0, 0,TRANSPARENTALPHA);
				break;
			}
		}
	}
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Clearing colliders' list");

	for (list<Collider*>::reverse_iterator it = setOfColliders.rbegin(); it != setOfColliders.rend(); ++it)
		RELEASE(*it);

	setOfColliders.clear();
	return true;
}

bool ModuleCollision::DetectCollision(SDL_Rect a, SDL_Rect b){
	return SDL_HasIntersection(&a, &b);
}

void ModuleCollision::deleteColliders(){

	list<Collider*>::iterator it = setOfColliders.begin();
	while (it != setOfColliders.end()){
		RELEASE(*it);
		it = setOfColliders.erase(it);
	}
}