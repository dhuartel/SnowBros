#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "Globals.h"

class Module;

enum colliderType{
	PLAYER=0,
	PLAYERFEET,
	PLAYERSHOT,
	ENEMY,
	ENEMYSHOT,
	SNOWBALL,
	WALL,
	PLATFORM,
	CEILING,
	FLOOR,
	ROLLINGBALL,
	PLATFORMWALL,
	ENEMYTURN,
	ENEMYJUMP,
	REDPOWERUP,
	BLUEPOWERUP,
	YELLOWPOWERUP,

	NUMOFCOLLISIONTYPES
};

enum collidingStatus{
	OUT=1,
	ENTERING,
	IN,
	EXITING
};

class Collider{
public:
	Collider(SDL_Rect,Module*,colliderType);
	~Collider();
	void flagRelease();
public:
	SDL_Rect collisionBox;
	Module* mod=nullptr;
	bool flagErase;
	bool colliding;
	colliderType type;
	collidingStatus colliderStatus;
};
#endif //__COLLIDER_H__