#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"

struct SDL_Renderer;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0f,int alpha=255);
	void DrawRect(SDL_Rect,int,int,int,int);
	bool ChangeLevel();

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
};

#endif // __MODULERENDER_H__