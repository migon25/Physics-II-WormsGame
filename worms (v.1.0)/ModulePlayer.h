#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Animation.h"
#include "SDL/include/SDL.h"

class ModulePlayer : public Module
{
public:
	enum PlayerState {
		PS_IDLE,
		PS_WALK,
		PS_LAST
	};

	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	update_status PostUpdate() override;
	bool CleanUp();

public:
	PhysBody* playerBody;

	SDL_Texture* worm;

<<<<<<< HEAD
	Animation* currentWormAnim = nullptr;
	Animation* currentSpeedometerAnim = nullptr;

	Animation wormIdle;
	Animation wormWalk;
	Animation speedometer;

	SDL_Rect wormText;

	//for the body
	SDL_Rect wormRect;
	SDL_Rect speed;
=======
	Animation animations[PS_LAST];

	//for the body
	SDL_Rect wormRect;
	SDL_RendererFlip flip;

	PlayerState state;
>>>>>>> 72624a58fa2fed1aa14970a8ef7056cd421626ef

	int prevPos;

};