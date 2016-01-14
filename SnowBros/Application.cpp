#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleStart.h"
#include "ModuleLevels.h"
#include "ModuleGameOver.h"
#include "ModuleWin.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticle.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "Graphics.h"
#include "AudioEffects.h"
#include <vld.h>

using namespace std;

Application::Application()
{
	// Order matters: they will init/start/pre/update/post in this order
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());

	modules.push_back(textures = new ModuleTextures());
	modules.push_back(audio = new ModuleAudio());

	modules.push_back(start = new ModuleStart(false));
	modules.push_back(levels = new ModuleLevels(false));
	modules.push_back(gameOver = new ModuleGameOver(false));
	modules.push_back(win = new ModuleWin(false));
	modules.push_back(player = new ModulePlayer(false));
	modules.push_back(enemy = new ModuleEnemy(false));
	modules.push_back(fade = new ModuleFadeToBlack());
	modules.push_back(particles = new ModuleParticle());
	modules.push_back(collisions = new ModuleCollision());
	modules.push_back(renderer = new ModuleRender());

	graphics = new Graphics();
	audioEffects = new AudioEffects();
}

Application::~Application()
{
	for (list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
	RELEASE(graphics);
	RELEASE(audioEffects);
}

bool Application::Init()
{
	bool ret = true;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); // we init everything, even if not enabled

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}
	audioEffects->LoadFxs();
	graphics->LoadGraphics();
	// Set the start scene 
	fade->FadeToBlack(start, nullptr, 3.0f);

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	if (input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN){
		debugMode = !debugMode;
	}

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PreUpdate();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Update();
		enemy->enemies;
	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->CleanUp();
	graphics->UnloadGraphics();
	return ret;
}

