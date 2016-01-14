#include "Particle.h"
#include "SDL/include/SDL.h"

Particle::Particle(particle newPart, Module* mod,int type){
	part = newPart;
	creationTime = SDL_GetTicks();
	particleType = type;
}

Particle::~Particle(){
}
