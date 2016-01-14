#ifndef __MODULEPARTICLE_H__
#define __MODULEPARTICLE_H__

#include "Module.h"

struct SDL_Texture;
class Particle;
class Collider;

class ModuleParticle : public Module
{
public:
	ModuleParticle();
	~ModuleParticle();

	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	void CreateParticle(particle,int);
	void OnCollision(Collider*,Collider*);
	bool objectsLeft() const;
	void deleteParticles();
	
private:
	list<Particle*> setOfParticles;
	list<Collider*> collidersOfParticles;//The colliders are stored in the same order as the particles
};

#endif // __MODULEPARTICLE_H__