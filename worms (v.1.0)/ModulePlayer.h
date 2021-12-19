#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Animation.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	PhysBody* playerBody;

private:
	//SDL_Texture* worm;
	Animation wormAnim;
	SDL_Rect wormText;

	//for the body
	SDL_Rect wormRect;

};