#include "AudioEffects.h"
#include "Application.h"
#include "ModuleAudio.h"

AudioEffects::AudioEffects(){}

void AudioEffects::LoadFxs(){
	coinFx = App->audio->LoadFx("sound/wavs/coin.wav");
	jumpFx = App->audio->LoadFx("sound/wavs/salto.wav");
	fireFx = App->audio->LoadFx("sound/wavs/disparo.wav");
	appearFx = App->audio->LoadFx("sound/wavs/aparicionPersonaje.wav");
	playerDieFx = App->audio->LoadFx("sound/wavs/muerte.wav");
	changeLevelFx = App->audio->LoadFx("sound/wavs/cambionv.wav");
	pushFx = App->audio->LoadFx("sound/wavs/empujarBola.wav");
	ballDieFx = App->audio->LoadFx("sound/wavs/bolafin.wav");
	objectFx = App->audio->LoadFx("sound/wavs/cogeObjeto.wav");
	bounceBallFx = App->audio->LoadFx("sound/wavs/reboteBola.wav");
	startFx = App->audio->LoadFx("sound/wavs/inicio.wav");
	flyEnemyFx = App->audio->LoadFx("sound/wavs/enemigoVuela.wav");
}