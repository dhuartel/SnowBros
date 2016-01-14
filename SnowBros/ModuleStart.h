#ifndef __MODULESTART_H__
#define __MODULESTART_H__

#include "Module.h"

struct SDL_Texture;

class ModuleStart : public Module
{
public://Functions
	ModuleStart(bool start_enabled = false);
	~ModuleStart();

	bool Start();
	update_status Update();
	bool CleanUp();

private://Variables

	SDL_Texture* graphics = nullptr;
	SDL_Rect startBackground;
	int coins = 0;
};

#endif // __MODULESTART_H__