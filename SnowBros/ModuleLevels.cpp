#include "Application.h"
#include "ModuleLevels.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleWin.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleEnemy.h"
#include "ModuleCollision.h"
#include "Graphics.h"
#include "ModuleFadeToBlack.h"
#include "AudioEffects.h"
#include "ModuleParticle.h"


ModuleLevels::ModuleLevels(bool start_enabled) : Module(start_enabled)
{
	// ground
	blackPiece.x = 0;
	blackPiece.y = 397;
	blackPiece.w = 512;
	blackPiece.h = 50;

	//Background
	background.x = 0;
	background.y = 0;
	background.w = 512;
	background.h = 868;

}

ModuleLevels::~ModuleLevels()
{}

// Load assets
bool ModuleLevels::Start()
{
	LOG("Loading Levels scene");

	graphics = App->textures->Load("background/niveles.png");
	//Set the camera to first level
	App->renderer->camera.y = -397 * SCREEN_SIZE;
	blackPiecePos = 397;
	changingLevel = false;
	// Enable the player and enemies modules
	App->player->Enable();
	App->enemy->Enable();
	App->player->SetPlayerFirstTime();
	App->enemy->setEnemies(1);
	// Trigger background music
	App->audio->PlayMusic("sound/otros/stage1_3.ogg");
	
	//Walls and level 1 floor and ceiling
	SDL_Rect aux;
	aux.x = -5;
	aux.y = 0;
	aux.w = 5;
	aux.h = 868;
	App->collisions->CreateCollider(aux, this, WALL);
	aux.x = 512;
	aux.y = 0;
	aux.w = 5;
	aux.h = 868;
	App->collisions->CreateCollider(aux, this, WALL);
	aux.x = 0;
	aux.y = 839;
	aux.w = 512;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, FLOOR);
	aux.x = 0;
	aux.y = 437;
	aux.w = 512;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, CEILING);
	//Lvl 1 Tier 0
	aux.x = 110;
	aux.y = 830;
	aux.w = 5;
	aux.h = 5;
	App->collisions->CreateCollider(aux, this, ENEMYJUMP);
	aux.x = 396;
	aux.y = 830;
	aux.w = 5;
	aux.h = 5;
	App->collisions->CreateCollider(aux, this, ENEMYJUMP);
	//Lvl 1 Tier 1
	aux.x = 0;
	aux.y = 774;
	aux.w = 120;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	aux.x = 194;
	aux.y = 774;
	aux.w = 120;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	aux.x = 386;
	aux.y = 774;
	aux.w = 126;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	aux.x = 150;
	aux.y = 760;
	aux.w = 5;
	aux.h = 5;
	App->collisions->CreateCollider(aux, this, ENEMYTURN);
	aux.x = 356;
	aux.y = 760;
	aux.w = 5;
	aux.h = 5;
	App->collisions->CreateCollider(aux, this, ENEMYTURN);
	//Lvl1 Tier 2
	aux.x = 98;
	aux.y = 710;
	aux.w = 310;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	aux.x = 310;
	aux.y = 690;
	aux.w = 5;
	aux.h = 5;
	App->collisions->CreateCollider(aux, this, ENEMYJUMP);
	aux.x = 190;
	aux.y = 690;
	aux.w = 5;
	aux.h = 5;
	App->collisions->CreateCollider(aux, this, ENEMYJUMP);
	aux.x = 80;
	aux.y = 690;
	aux.w = 5;
	aux.h = 5;
	App->collisions->CreateCollider(aux, this, ENEMYTURN);
	aux.x = 428;
	aux.y = 690;
	aux.w = 5;
	aux.h = 5;
	App->collisions->CreateCollider(aux, this, ENEMYTURN);
	//Lvl1 Tier 3
	aux.x = 0;
	aux.y = 646;
	aux.w = 216;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	aux.x = 290;
	aux.y = 646;
	aux.w = 222;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	aux.x = 249;
	aux.y = 625;
	aux.w = 17;
	aux.h = 5;
	App->collisions->CreateCollider(aux, this, ENEMYTURN);
	//Lvl 1 Tier 4
	aux.x = 66; 
	aux.y = 582;
	aux.w = 61;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	aux.x = 128;
	aux.y = 549;
	aux.w = 249;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	aux.x = 128;
	aux.y = 549;
	aux.w = 249;
	aux.h = 30;
	App->collisions->CreateCollider(aux, this, PLATFORMWALL);
	aux.x = 378; 
	aux.y = 582;
	aux.w = 61;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);

	//Lvl2 Ceiling and floor
	aux.x = 0;
	aux.y = 388;
	aux.w = 512;
	aux.h = 20;
	App->collisions->CreateCollider(aux, this, FLOOR);
	aux.x = 0;
	aux.y = -10;
	aux.w = 512;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, CEILING);
	//Lvl2 Tier 1
	aux.x = 122;
	aux.y = 323;
	aux.w = 285;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	aux.x = 205;
	aux.y = 300;
	aux.w = 5;
	aux.h = 5;
	App->collisions->CreateCollider(aux, this, ENEMYJUMP);
	aux.x = 68;
	aux.y = 270;
	aux.w = 54;
	aux.h = 50;
	App->collisions->CreateCollider(aux, this, PLATFORMWALL);
	//Lvl2 Tier 2
	aux.x = 194;
	aux.y = 259;
	aux.w = 194;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	aux.x = 165;
	aux.y = 240;
	aux.w = 5;
	aux.h = 5;
	App->collisions->CreateCollider(aux, this, ENEMYTURN);
	aux.x = 388;
	aux.y = 207;
	aux.w = 54;
	aux.h = 50;
	App->collisions->CreateCollider(aux, this, PLATFORMWALL);
	aux.x = 68;
	aux.y = 259;
	aux.w = 54;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	//Lvl2 Tier 3
	aux.x = 121;
	aux.y = 196;
	aux.w = 191;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	aux.x = 205;
	aux.y = 175;
	aux.w = 5;
	aux.h = 5;
	App->collisions->CreateCollider(aux, this, ENEMYJUMP);
	aux.x = 68;
	aux.y = 143;
	aux.w = 54;
	aux.h = 50;
	App->collisions->CreateCollider(aux, this, PLATFORMWALL);
	aux.x = 388;
	aux.y = 196;
	aux.w = 54;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	//Lvl2 Tier 4
	aux.x = 194;
	aux.y = 132;
	aux.w = 194;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	aux.x = 165;
	aux.y = 115;
	aux.w = 5;
	aux.h = 5;
	App->collisions->CreateCollider(aux, this, ENEMYTURN);
	aux.x = 388;
	aux.y = 79;
	aux.w = 54;
	aux.h = 50;
	App->collisions->CreateCollider(aux, this, PLATFORMWALL);
	aux.x = 68;
	aux.y = 132;
	aux.w = 54;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	//Lvl2 Tier 5
	aux.x = 98;
	aux.y = 68;
	aux.w = 214;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	aux.x = 388;
	aux.y = 68;
	aux.w = 54;
	aux.h = 10;
	App->collisions->CreateCollider(aux, this, PLATFORM);
	


	levelNumber = 1;
	return true;
}

// UnLoad assets
bool ModuleLevels::CleanUp()
{
	LOG("Unloading levels scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleLevels::Update()
{
	blackPiece.y = blackPiecePos;
	
	App->renderer->Blit(graphics, 0, 0, &background); // This is the whole background for both levels

	//Draw Lives
	if (!changingLevel){
		switch (levelNumber){
		case 1:
			App->renderer->Blit(App->graphics->playerGraphics, 10, 449, &App->graphics->livesFace);

			App->renderer->Blit(App->graphics->playerGraphics, 48, 455, &App->graphics->livesNumbers.GetFrame(App->player->lives));
			break;
		case 2:
			App->renderer->Blit(App->graphics->playerGraphics, 10, 2, &App->graphics->livesFace);

			App->renderer->Blit(App->graphics->playerGraphics, 48, 8, &App->graphics->livesNumbers.GetFrame(App->player->lives));
			break;
		}
	}

	//Check if there are enemies left to start changing the level
	if (App->enemy->enemies.size()==0 && !changingLevel && !App->particles->objectsLeft()){
		if (levelNumber == 1){
			changingLevel = true;
			App->player->status=PLAYERCHANGINGLEVEL;
			App->audio->PlayFx(App->audioEffects->changeLevelFx);
		}
		else{
			App->fade->FadeToBlack(App->win, this, 3.0f);
			changingLevel = true;
		}
	}

	//The != lastlevel is needed not to move camera before going to victory screen
	if (changingLevel && levelNumber!=2){
		blackPiecePos -=3;//Moving the blackPiece at same speed as camera seems to be at same position
		//If the new level is displayed, set the player and the enemies
		if (App->renderer->ChangeLevel()){
			App->player->ResetPlayer(2,false);
			App->enemy->setEnemies(2);
			levelNumber = 2;
			changingLevel = false;
		}
	}
		
	
	return UPDATE_CONTINUE;
}

update_status ModuleLevels::PostUpdate(){//This must be drawn after the player, so must be done in postupdate
	App->renderer->DrawRect(blackPiece, 0, 0, 0, 255); //In this rectangle should go the points
	App->renderer->Blit(App->graphics->miscGraphics, 10, blackPiecePos + 15, &App->graphics->player1);
	App->renderer->Blit(App->graphics->miscGraphics, 180, blackPiecePos + 15, &App->graphics->hi);
	App->renderer->Blit(App->graphics->miscGraphics, 350, blackPiecePos + 15, &App->graphics->player2);
	App->renderer->Blit(App->graphics->miscGraphics, 400, blackPiecePos + 5, &(App->graphics->pushButton.GetCurrentFrame()));
	int puntuationPos = 0;
	int auxScore = App->player->score;
	//PlayerScore
	while (auxScore / 10 != 0){
		App->renderer->Blit(App->graphics->miscGraphics, 143-20*puntuationPos, blackPiecePos + 15, &App->graphics->pointsNumbers.GetFrame(auxScore % 10));
		++puntuationPos;
		auxScore /= 10;
	}
	App->renderer->Blit(App->graphics->miscGraphics, 143 - 20 * puntuationPos, blackPiecePos + 15, &App->graphics->pointsNumbers.GetFrame(auxScore));
	//HiScore
	puntuationPos = 0;
	auxScore = 40000;
	while (auxScore / 10 != 0){
		App->renderer->Blit(App->graphics->miscGraphics, 313 - 20 * puntuationPos, blackPiecePos + 15, &App->graphics->pointsNumbers.GetFrame(auxScore % 10));
		++puntuationPos;
		auxScore /= 10;
	}
	App->renderer->Blit(App->graphics->miscGraphics, 313 - 20 * puntuationPos, blackPiecePos + 15, &App->graphics->pointsNumbers.GetFrame(auxScore));
	return UPDATE_CONTINUE;
}