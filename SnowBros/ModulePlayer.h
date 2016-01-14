#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Point.h"

struct SDL_Texture;
class Collider;

enum playerStatus{
	PLAYERNONE,
	PLAYERMOVING,
	PLAYERJUMPING,
	PLAYERFALLING,
	PLAYERPUSHING,
	PLAYERPUSHBALL,
	PLAYERBALLED,
	PLAYERCHANGINGLEVEL,
	PLAYERDYING,
	PLAYERDESTROYING
};

class ModulePlayer : public Module
{
public://Functions
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*,Collider*);
	void ResetPlayer(int,bool=true);
	void SetPlayerFirstTime();

public://Variables
	int lives;
	playerStatus status;
	int score = 0;
	bool immune = false;
	bool shooting = false;
	Uint32 immuneTime;
	float movementSpeed = 2;
	int numberBall;//number of the enemy that has taken the player into its ball
	bool bluePowerUp = false;

private://Functions
	void displayPlayerDestruction() const;

private://Variables
	bool firstTime = false;
	fPoint position;
	Collider* myCollider;
	Collider* myFeetCollider;

	float fallingSpeed = 3;
	float fallingAcceleration = 0.2f;
	bool leftBlocked = false;//Can't move left
	bool rightBlocked = false;//Can't move right
	bool redPowerUp = false;
	bool yellowPowerUp = false;

	bool lookingLeft = true;
	bool newLevel = false;
	int jumpCommited;
	int alpha = 255;//alpha value to draw with

	//Variables for the display of the player destruction
	float relativePositionsDestroying = 0;
	int relativePositionsDestroyingState = 1;
	float destroyingOffset = 30;
};

#endif // __MODULEPLAYER_H__