#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__

#include "Module.h"
#include "Point.h"

class Enemy;

class ModuleEnemy : public Module
{
public://Functions
	ModuleEnemy(bool start_enabled = true);
	~ModuleEnemy();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void setEnemies(int);
	Enemy* ReturnOwner(Collider*) const;
	Enemy* ReturnOwner(int)const;
	bool checkHarmingStatus(Collider*) const;
	void deleteEnemies();

public://Variables
	list<Enemy*> enemies;
private://Functions
	bool checkCollidableStatus(Collider*) const;
};

#endif // __MODULEENEMY_H__