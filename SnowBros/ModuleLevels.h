#ifndef __MODULELEVELS_H__
#define __MODULELEVELS_H__

#include "Module.h"

struct SDL_Texture;

class ModuleLevels : public Module
{
public://Functions
	ModuleLevels(bool start_enabled = true);
	~ModuleLevels();

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public://Variables
	int levelNumber;

private://Variables
	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	SDL_Rect blackPiece;
	bool changingLevel;
	int blackPiecePos;
};

#endif // __MODULELEVELS_H__