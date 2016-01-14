#ifndef __MODULEWIN_H__
#define __MODULEWIN_H__

#include "Module.h"

struct SDL_Texture;

class ModuleWin : public Module
{
public:
	ModuleWin(bool start_enabled = false);
	~ModuleWin();

	bool Start();
	update_status Update();
	bool CleanUp();

private:

	SDL_Texture* graphics = nullptr;
	SDL_Rect winBackground;
};

#endif // __MODULEWIN_H__