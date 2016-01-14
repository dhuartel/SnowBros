#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include<list>
#include "Globals.h"

class Module;

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModulePlayer;
class ModuleEnemy;
class ModuleParticle;
class ModuleCollision;
class ModuleLevels;
class ModuleGameOver;
class Graphics;
class ModuleStart;
class ModuleWin;
class AudioEffects;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleLevels* levels;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModulePlayer* player;
	ModuleEnemy* enemy;
	ModuleCollision* collisions;
	ModuleFadeToBlack* fade;
	ModuleParticle* particles;
	ModuleGameOver* gameOver;
	ModuleStart* start;
	ModuleWin* win;
	Graphics* graphics;
	AudioEffects* audioEffects;

	bool debugMode = false;

private:

	std::list<Module*> modules;

};

extern Application* App;

#endif // __APPLICATION_H__