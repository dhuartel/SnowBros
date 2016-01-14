#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleRender::ModuleRender()
{
	camera.x =  0;
	camera.y = 0;
	camera.w = SCREEN_WIDTH * SCREEN_SIZE;
	camera.h = SCREEN_HEIGHT* SCREEN_SIZE;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	// debug camera
	if (App->debugMode){
		int speed = 3;

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			App->renderer->camera.y += speed;

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			App->renderer->camera.y -= speed;

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			App->renderer->camera.x += speed;

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			App->renderer->camera.x -= speed;
	}
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed,int alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
	bool ret = true;
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
	rect.y = (int)(camera.y * speed) + y * SCREEN_SIZE;

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

//Draws a rectangle wityh the given color and alpha
void ModuleRender::DrawRect(SDL_Rect rect, int r, int g, int b,int a){
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_Rect aux;
	aux.x = camera.x + rect.x*SCREEN_SIZE;
	aux.y = camera.y + rect.y*SCREEN_SIZE;
	aux.w = rect.w*SCREEN_SIZE;
	aux.h = rect.h*SCREEN_SIZE;
	SDL_RenderFillRect(renderer, &aux);
}

//Sets the camera for the second level
//using movement commited instead of absolute positions would make it scalable for more levels
bool ModuleRender::ChangeLevel(){
	camera.y += 3*SCREEN_SIZE;
	if (camera.y == 56*SCREEN_SIZE)
		return true;
	return false;
}
