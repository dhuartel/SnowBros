#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Globals.h"
#include "Point.h"

class Collider;

enum enemy_status{
	NONE,
	JUMPING,
	FALLING,
	LANDING,
	SHOOTING,
	SNOW1,
	SNOW2,
	SNOW3,
	SNOW4,
	SNOWROLLING,
	SNOWDESTROYING,
	TAKINGOFF,
	FLYING,
	LANDINGDEAD,
	TOBEDESTROYED
};

class Enemy{
public://Functions
	Enemy(int);
	~Enemy();
	update_status PreUpdate();
	update_status Update();

public://Variables
	fPoint position;
	Collider* myCollider;
	Collider* myFeetCollider;
	enemy_status status;

	bool lookingLeft = true;
	bool turn = true;
	bool shot = false;
	int jumpCommited;
	float movementSpeed = 2.2f;
	bool snowHit;//true if it has been hit by playershot
	bool flyingDown = false;
	int enemynumber;
	int enemyHitCount = 0;//Number of enemies hit as a rolling ball

private://Variables
	Uint32 hitTime;//moment it has been hit
	int hitCounter = 0;//Number of hits since it got into the current status

	//This is the distance from the starting point at the moment
	float relativePositionsDestroying = 0;
	//There are 4 posible positions for the sprites of the destruction
	int relativePositionsDestroyingState = 1;
	//This is the maximum distance from the starting point
	float destroyingOffset = 30;

	Animation enemyTurnLeft;
	Animation enemyTurnRight;
	Animation enemyLandingLeft;
	Animation enemyLandingRight;
	Animation enemyLandingDead;
private://Functions
	void displayEnemyDestruction()const;
	void shoot(int);
	void dropPowerUp();
};
#endif //__ENEMY_H__