#include "Globals.h"
#include "Application.h"
#include "ModuleStart.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleLevels.h"
#include "ModuleFadeToBlack.h"
#include "AudioEffects.h"
#include "Graphics.h"
#include "ModuleEnemy.h"
#include "ModulePlayer.h"


ModuleStart::ModuleStart(bool start_enabled) : Module(start_enabled)
{
	startBackground.x = 0;
	startBackground.y = 0;
	startBackground.w = 512;
	startBackground.h = 417;
}

ModuleStart::~ModuleStart()
{}

// Load assets
bool ModuleStart::Start()
{
	LOG("Loading Start scene");

	graphics = App->textures->Load("background/start.png");
	LOG("Start");
	return true;
}

// UnLoad assets
bool ModuleStart::CleanUp()
{
	LOG("Unloading Start scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleStart::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && coins != 0){
		--coins;
		App->fade->FadeToBlack(App->levels, this, 3.0f);
		App->audio->PlayFx(App->audioEffects->startFx);
		return UPDATE_CONTINUE;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN){
		++coins;
		App->audio->PlayFx(App->audioEffects->coinFx);
	}
	App->renderer->Blit(graphics, 0, 0, &startBackground);
	if (coins == 0){
		App->renderer->Blit(App->graphics->miscGraphics, 215, 275, &App->graphics->insertCoin.GetCurrentFrame());
	}
	else{
		App->renderer->Blit(App->graphics->miscGraphics, 215, 275, &App->graphics->insertCoin.GetFrame(1));
	}		
	return UPDATE_CONTINUE;
}