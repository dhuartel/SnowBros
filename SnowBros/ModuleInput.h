#ifndef __MODULEINPUT_H__
#define __MODULEINPUT_H__

#include "Module.h"
#include "Point.h"

#include "SDL/include/SDL_scancode.h"

#define NUM_MOUSE_BUTTONS 5

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{

public:

	ModuleInput();

	// Destructor
	virtual ~ModuleInput();

	// Called before render is available
	bool Init();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	update_status PreUpdate();

	// Called before quitting
	bool CleanUp();

	// Check key states (includes mouse and joy buttons)
	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}


	
	// Check for window events last frame
	bool GetWindowEvent(EventWindow code) const;


private:
	bool		windowEvents[WE_COUNT];
	KeyState*	keyboard;
};

#endif // __MODULEINPUT_H__