#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "SDL/include/SDL_rect.h"
#include "Point.h"
#include "Animation.h"
//#include <vld.h>
struct SDL_Texture;

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

typedef struct {
	fPoint position;
	Animation anim;
	SDL_Texture* tex;
	fPoint speed;
	fPoint acceleration;
} particle;

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Deletes a buffer
#define RELEASE( x ) \
    {\
       if( x != nullptr )\
	          {\
         delete x;\
	     x = nullptr;\
	          }\
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
		{\
       if( x != nullptr )\
	          {\
           delete[] x;\
	       x = nullptr;\
	   		 }\
		 }

// Configuration -----------
#define TRANSPARENTALPHA 100
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 471
#define SCREEN_SIZE 1
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Snow Bros Tribute"

#endif //__GLOBALS_H__
