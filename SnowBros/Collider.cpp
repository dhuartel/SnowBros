#include "Collider.h"
#include "Module.h"


Collider::Collider(SDL_Rect box, Module* m,colliderType colType){
	collisionBox = box;
	mod = m;
	flagErase = false;
	type = colType;
	colliding = false;
	colliderStatus = OUT;
}

Collider::~Collider(){
}

void Collider::flagRelease(){
	flagErase = true;
}