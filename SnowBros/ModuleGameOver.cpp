#include "Application.h"
#include "ModuleGameOver.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleEnemy.h"
#include "ModuleParticle.h"
#include "ModuleStart.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollision.h"
//#include "Graphics.h"
#include "SDL/include/SDL.h"


ModuleGameOver::ModuleGameOver(bool start_enabled) : Module(start_enabled)
{

	//Game over Letters
	G.x = 0;
	G.y = 0;
	G.w = 48;
	G.h = 48;
	A.x = 48;
	A.y = 0;
	A.w = 48;
	A.h = 48;
	M.x = 96;
	M.y = 0;
	M.w = 48;
	M.h = 48;
	E.x = 144;
	E.y = 0;
	E.w = 48;
	E.h = 48;
	O.x = 0;
	O.y = 48;
	O.w = 48;
	O.h = 48;
	V.x = 48;
	V.y = 48;
	V.w = 48;
	V.h = 48;
	R.x = 144;
	R.y = 48;
	R.w = 48;
	R.h = 48;
}

ModuleGameOver::~ModuleGameOver()
{}

// Load assets
bool ModuleGameOver::Start()
{
	LOG("Loading Game Over scene");

	graphics = App->textures->Load("sprites/GameOver/gameOver.png");
	App->player->Disable();
	App->enemy->deleteEnemies();
	App->enemy->Disable();
	App->particles->deleteParticles();
	App->collisions->deleteColliders();
	App->renderer->camera.y = 0;
	App->audio->PlayMusic("sound/otros/gameover.ogg");
	musicTime = SDL_GetTicks();
	return true;
}

// UnLoad assets
bool ModuleGameOver::CleanUp()
{
	LOG("Unloading Game Over scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw Game Over
update_status ModuleGameOver::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN){
		App->fade->FadeToBlack(App->start, this, 0);
		return UPDATE_CONTINUE;
	}
	if (SDL_GetTicks()> musicTime + 1825){
		App->audio->PlayMusic("");
	}
	App->renderer->Blit(graphics, 50, 160, &G);
	App->renderer->Blit(graphics, 100, 160, &A);
	App->renderer->Blit(graphics, 150, 160, &M);
	App->renderer->Blit(graphics, 200, 160, &E);
	App->renderer->Blit(graphics, 262, 160, &O);
	App->renderer->Blit(graphics, 312, 160, &V);
	App->renderer->Blit(graphics, 362, 160, &E);
	App->renderer->Blit(graphics, 412, 160, &R);
	return UPDATE_CONTINUE;
}