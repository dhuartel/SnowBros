#ifndef __MODULEGAMEOVER_H__
#define __MODULEGAMEOVER_H__

#include "Module.h"

struct SDL_Texture;

class ModuleGameOver : public Module
{
public:
	ModuleGameOver(bool start_enabled = false);
	~ModuleGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();

private:

	SDL_Texture* graphics = nullptr;
	SDL_Rect G;
	SDL_Rect A;
	SDL_Rect M;
	SDL_Rect E;
	SDL_Rect O;
	SDL_Rect V;
	SDL_Rect R;
	Uint32 musicTime;
};

#endif // __MODULEGAMEOVER_H__