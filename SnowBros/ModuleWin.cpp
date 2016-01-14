#include "Application.h"
#include "ModuleWin.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "ModuleParticle.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStart.h"

ModuleWin::ModuleWin(bool start_enabled) : Module(start_enabled)
{
	winBackground.x = 0;
	winBackground.y = 0;
	winBackground.w = 512;
	winBackground.h = 471;
}

ModuleWin::~ModuleWin()
{}

// Load assets
bool ModuleWin::Start()
{
	LOG("Loading Victory scene");

	graphics = App->textures->Load("background/victory.png");
	App->player->Disable();
	App->enemy->deleteEnemies();
	App->enemy->Disable();
	App->particles->deleteParticles();
	App->collisions->deleteColliders();
	App->renderer->camera.y = 0;
	App->audio->PlayMusic("sound/otros/ending.ogg");
	return true;
}

// UnLoad assets
bool ModuleWin::CleanUp()
{
	LOG("Unloading Victory scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleWin::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN){
		App->audio->PlayMusic("");
		App->fade->FadeToBlack(App->start, this, 0);
		return UPDATE_CONTINUE;
	}
	App->renderer->Blit(graphics, 0, 0, &winBackground);
	return UPDATE_CONTINUE;
}