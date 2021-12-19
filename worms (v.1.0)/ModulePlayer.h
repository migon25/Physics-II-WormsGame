#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;

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

	SDL_Texture* worm;

	Animation* currentWormAnim = nullptr;
	Animation* currentSpeedometerAnim = nullptr;

	Animation wormIdle;
	Animation wormWalk;
	Animation speedometer;

	SDL_Rect wormText;

	//for the body
	SDL_Rect wormRect;
	SDL_Rect speed;

	int prevPos;

};