#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"

class Application;
class Collider;

class Module
{
public:

	Module(bool active = true) : active(active)
	{}

	virtual ~Module()
	{}

	bool IsEnabled() const
	{
		return active;
	}

	bool Enable()
	{
		if (!active)
			return active = Start();

		return true;
	}

	bool Disable()
	{
		if (active)
			return active = !CleanUp();

		return true;
	}

	virtual bool Init()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	virtual void OnCollision(Collider*,Collider*){

	}

private:
	bool active = true;
};

#endif // __MODULE_H__