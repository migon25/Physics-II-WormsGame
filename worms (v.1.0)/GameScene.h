#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Vector2.h"

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

	//test
	p2List<PhysBody*> grenades;

	// Mouse
	SDL_Texture* corsairTex;
	Animation corsairAnim;
	Animation grenade;
	Animation ice;
	Animation missile;
	SDL_Rect grenRec;
	SDL_Rect iceRec;
	SDL_Rect missRec;
	SDL_Rect corsairRec;
	Vector2 mousePos;

	// numbers
	SDL_Texture* numbers;
	SDL_Texture* font;
	int numEnemies;
	int numGren;
	int numBoxes;
	int numIce;
	int fonts;
	int veloInteg;

private:
};
