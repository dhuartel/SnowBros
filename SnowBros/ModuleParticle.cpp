#include "Globals.h"
#include "Application.h"
#include "ModuleParticle.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Particle.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"
#include "Collider.h"
#include "Graphics.h"


ModuleParticle::ModuleParticle(){
}

ModuleParticle::~ModuleParticle(){
}

//Creates the particle and its correspondent collider
void ModuleParticle::CreateParticle(particle newParticle,int type){
	setOfParticles.push_back(new Particle(newParticle, this, type));
	SDL_Rect aux;
	aux.x = newParticle.position.x;
	aux.y = newParticle.position.y;
	aux.w = newParticle.anim.frames[0].w;
	aux.h = newParticle.anim.frames[0].h;
	switch (type){
	case 1:
		collidersOfParticles.push_back(App->collisions->CreateCollider(aux, this,PLAYERSHOT));
		break;
	case 2:
	case 3:
		collidersOfParticles.push_back(App->collisions->CreateCollider(aux, this, ENEMYSHOT));
		break;
	case 4:
		collidersOfParticles.push_back(App->collisions->CreateCollider(aux, this, REDPOWERUP));
		break;
	case 5:
		collidersOfParticles.push_back(App->collisions->CreateCollider(aux, this, YELLOWPOWERUP));
		break;
	case 6:
		collidersOfParticles.push_back(App->collisions->CreateCollider(aux, this, BLUEPOWERUP));
		break;
	}
}

//Check if has to be destroyed and marks the particle as well if so
update_status ModuleParticle::PreUpdate(){
	list<Particle*>::iterator it = setOfParticles.begin();
	list<Collider*>::iterator it2 = collidersOfParticles.begin();
	Uint32 currentTime = SDL_GetTicks();
	while ( it != setOfParticles.end()){
		if ((*it)->beingDestroyed){
			if ((*it)->part.anim.hasFinished()){
				RELEASE(*it);
				it = setOfParticles.erase(it);
				(*it2)->flagRelease();
				it2 = collidersOfParticles.erase(it2);
			}
			else{
				++it;
				++it2;
			}
		}
		else{
			switch ((*it)->particleType)
			{
			case 1:
				if (currentTime > (*it)->creationTime + 800){
					(*it)->part.anim = App->graphics->playerShotDying;
					(*it)->beingDestroyed = true;
					(*it)->part.speed.x = 0;
					(*it)->part.speed.y = 0;
					++it;
					++it2;
				}
				else{
					++it;
					++it2;
				}
				break;
			case 2:
				if (currentTime > (*it)->creationTime + 1000){
					(*it)->part.anim = App->graphics->enemyShotLeftDying;
					(*it)->beingDestroyed = true;
					(*it)->part.speed.x = -0.01f;
					++it;
					++it2;
				}
				else{
					++it;
					++it2;
				}
				break;
			case 3:
				if (currentTime > (*it)->creationTime + 1000){
					(*it)->part.anim = App->graphics->enemyShotRightDying;
					(*it)->beingDestroyed = true;
					(*it)->part.speed.x = 0.01f;
					++it;
					++it2;
				}
				else{
					++it;
					++it2;
				}
				break;
			case 4:
			case 5: 
			case 6:
				if (currentTime > (*it)->creationTime + 2500){
					RELEASE(*it);
					it = setOfParticles.erase(it);
					(*it2)->flagRelease();
					it2 = collidersOfParticles.erase(it2);
				}
				else{
					++it;
					++it2;
				}
				break;
			default:
				break;
			}
		}
	}
	return UPDATE_CONTINUE;
}

//Draw and move
update_status ModuleParticle::Update(){
	list<Particle*>::iterator it;
	list<Collider*>::iterator it2=collidersOfParticles.begin();
	for (it = setOfParticles.begin(), it2 = collidersOfParticles.begin(); it != setOfParticles.end(); ++it, ++it2){
		App->renderer->Blit((*it)->part.tex, (*it)->part.position.x, (*it)->part.position.y - (*it)->part.anim.GetCurrentFrame().h, &((*it)->part.anim.GetCurrentFrame()));


		if (!(*it)->beingDestroyed){
			(*it)->part.position.x += (*it)->part.speed.x;
			(*it)->part.position.y += (*it)->part.speed.y;
			(*it2)->collisionBox.x = (*it)->part.position.x;
			(*it2)->collisionBox.y = (*it)->part.position.y - (*it)->part.anim.GetCurrentFrame().h;
			(*it2)->collisionBox.w = (*it)->part.anim.GetCurrentFrame().w;
			(*it2)->collisionBox.h = (*it)->part.anim.GetCurrentFrame().h;

			(*it)->part.speed.y += (*it)->part.acceleration.y;
			(*it)->part.speed.y += (*it)->part.acceleration.x;
		}
		else{
			(*it2)->collisionBox.w = 0;
			(*it2)->collisionBox.h = 0;
		}
	}
	return UPDATE_CONTINUE;
}

bool ModuleParticle::CleanUp(){
	deleteParticles();
	return true;
}

void ModuleParticle::OnCollision(Collider* a, Collider* b){
	if (collidersOfParticles.size() != 0 && !a->flagErase && !b->flagErase){
		list<Collider*>::iterator it = collidersOfParticles.begin();
		list<Particle*>::iterator it2 = setOfParticles.begin();
		switch (a->type)
		{
		case PLAYERSHOT:
			if (it != collidersOfParticles.end()){
				while (*it != a && it != collidersOfParticles.end()){
					++it;
				}
				advance(it2, distance(collidersOfParticles.begin(), it));
				if (!(*it2)->beingDestroyed){
					(*it2)->part.anim = App->graphics->playerShotDying;
					(*it2)->part.speed.x = 0;
					(*it2)->part.speed.y = 0;
					(*it2)->beingDestroyed = true;
				}
			}
			break;
		case ENEMYSHOT:
			if (b->type == PLAYERSHOT || b->type == ENEMYSHOT){}
			else{
				while (*it != a && it != collidersOfParticles.end()){
					++it;
				}
				advance(it2, distance(collidersOfParticles.begin(), it));
				if (!(*it2)->beingDestroyed){
					if (a->collisionBox.x < b->collisionBox.x){
						(*it2)->part.anim = App->graphics->enemyShotRightDying;
						(*it2)->part.speed.x = 0.01f;
					}
					else{
						(*it2)->part.anim = App->graphics->enemyShotLeftDying;
						(*it2)->part.speed.x = -0.01f;
					}
					(*it2)->beingDestroyed = true;
				}
			}
			break;
		case REDPOWERUP:
		case BLUEPOWERUP:
		case YELLOWPOWERUP:
			while (*it != a && it != collidersOfParticles.end()){
				++it;
			}
			advance(it2, distance(collidersOfParticles.begin(), it));
			RELEASE(*it2);
			it2 = setOfParticles.erase(it2);
			(*it)->flagRelease();
			it = collidersOfParticles.erase(it);
			break;
		default:
			break;
		}

		switch (b->type)
		{
		case PLAYERSHOT:
			if (it != collidersOfParticles.end()){
				while (*it != b && it != collidersOfParticles.end()){
					++it;
				}
				advance(it2, distance(collidersOfParticles.begin(), it));
				if (!(*it2)->beingDestroyed){
					(*it2)->part.anim = App->graphics->playerShotDying;
					(*it2)->part.speed.x = 0;
					(*it2)->part.speed.y = 0;
					(*it2)->beingDestroyed = true;
				}
			}
			break;
		case ENEMYSHOT:
			while (*it != b && it != collidersOfParticles.end()){
				++it;
			}
			advance(it2, distance(collidersOfParticles.begin(), it));
			if (!(*it2)->beingDestroyed){
				if (b->collisionBox.x < a->collisionBox.x){
					(*it2)->part.anim = App->graphics->enemyShotRightDying;
					(*it2)->part.speed.x = 0.01f;
				}
				else{
					(*it2)->part.anim = App->graphics->enemyShotLeftDying;
					(*it2)->part.speed.x = -0.01f;
				}
				(*it2)->beingDestroyed = true;
			}
			break;
		case REDPOWERUP:
		case BLUEPOWERUP:
		case YELLOWPOWERUP:
			while (*it != b && it != collidersOfParticles.end()){
				++it;
			}
			advance(it2, distance(collidersOfParticles.begin(), it));
			RELEASE(*it2);
			it2 = setOfParticles.erase(it2);
			(*it)->flagRelease();
			it = collidersOfParticles.erase(it);
			break;
		default:
			break;
		}
	}
}

bool ModuleParticle::objectsLeft() const{
	for (list<Particle*>::const_iterator it = setOfParticles.begin(); it != setOfParticles.end();++it){
		switch ((*it)->particleType){
		case 4:
		case 5:
		case 6:
			return true;
			break;
		}
	}
	return false;
}

void ModuleParticle::deleteParticles(){
	LOG("Clearing colliders' list");
	list<Particle*>::iterator it = setOfParticles.begin();
	while (it != setOfParticles.end()){
		RELEASE(*it);
		it = setOfParticles.erase(it);
	}
	collidersOfParticles.clear();
}
