#ifndef __PARTICLE_H__
#define __PARTICLE_H__

class Module;
#include "Globals.h"

class Particle{
public://Functions

	Particle(particle,Module*,int);
	~Particle();

public://Variables
	particle part;
	Uint32 creationTime;
	int particleType;
	bool beingDestroyed = false;
};

#endif __PARTICLE_H__