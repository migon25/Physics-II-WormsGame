#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;
struct SDL_Texture;

class GameScene : public Module
{
public:
	GameScene(Application* app, bool start_enabled = true);
	~GameScene();

	bool Start();
	update_status Update();
	bool CleanUp();

	double CalculateSpeed(double dx, double dy);
public:
	PhysBody* ground;
	PhysBody* target;

	SDL_Texture* terrain;
	SDL_Texture* sky;
};
