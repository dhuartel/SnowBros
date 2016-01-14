#ifndef __MODULECOLLISION_H__
#define __MODULECOLLISION_H__

#include "Module.h"
#include <list>
#include "Collider.h"

struct SDL_Texture;

class ModuleCollision : public Module
{
public://functions
	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	//It returns the created collider to be stored in the class that creates it as well
	Collider* CreateCollider(SDL_Rect, Module*, colliderType);

	void deleteColliders();
private://Variables
	list<Collider*> setOfColliders;
	bool DetectCollision(SDL_Rect, SDL_Rect);
	bool possibleCollisions[NUMOFCOLLISIONTYPES][NUMOFCOLLISIONTYPES];
};

#endif // __MODULECOLLISION_H__