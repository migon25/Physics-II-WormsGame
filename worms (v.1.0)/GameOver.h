#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class GameOver : public Module
{
public:
	// Constructor
	GameOver(Application* app, bool start_enabled = true);

	// Destructor
	~GameOver();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start();

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate();

	bool CleanUp();
public:
	// The scene sprite sheet loaded into an SDL_Texture
};

#endif	// __SCENEINTRO_H__