#ifndef __AUDIOEFFECTS_H__
#define __AUDIOEFFECTS_H__

#include "Globals.h"
class Animation;

class AudioEffects{
public:
	AudioEffects();
	void LoadFxs();
public:
	unsigned int coinFx = 0;
	unsigned int jumpFx = 0;
	unsigned int fireFx = 0;
	unsigned int appearFx = 0;
	unsigned int playerDieFx = 0;
	unsigned int changeLevelFx = 0;
	unsigned int pushFx = 0;
	unsigned int ballDieFx = 0;
	unsigned int objectFx = 0;
	unsigned int bounceBallFx = 0;
	unsigned int startFx = 0;
	unsigned int flyEnemyFx = 0;
};
#endif //__AUDIOEFFECTS_H__