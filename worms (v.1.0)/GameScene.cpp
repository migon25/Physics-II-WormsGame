#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleRender.h"
#include "FadeToBlack.h"
#include "GameScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleFonts.h"

#include <iostream>

GameScene::GameScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	corsairAnim.PushBack({ 148,7,10,10 });
	corsairAnim.loop = false;
}

GameScene::~GameScene()
{}

// Load assets
bool GameScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Fonts
	char lookupTable[] = { "abcdefghijklmnopqrstuvwxyz" };
	fonts = App->fonts->Load("Assets/fonts.png", lookupTable, 1);
	numbers = App->textures->Load("Assets/numbers.png");
	numBoxes = 0;
	numEnemies = 0;
	numGren = 0;

	// Atmosphere
	//App->physics->SetAtmosphere(-10.0, 0, 0.00001);
	sky = App->textures->Load("Assets/sky.png");

	// Target
	target = App->physics->CreatePhysBody(SCREEN_WIDTH / 2, 100, 50, 50, Collider::Type::ENEMY, this);
	corsairTex = App->textures->Load("Assets/worms.png");

	target->mass = 100; // kg
	target->surface = 2; // m^2
	target->dragCoefficient = -0.4;
	target->liftCoefficient = 1.2;
	target->frictionCoefficient = 1.0;
	target->restitutionCoefficient = 1.0;

	// Ground
	ground = App->physics->CreatePhysBody(0, SCREEN_HEIGHT - 100, SCREEN_WIDTH, 150, Collider::Type::GROUND, this);
	terrain = App->textures->Load("Assets/ground.png");

	// Module enabler
	ground->physics_enabled = false;
	App->player->Enable();

	return ret;
}

// Load assets
bool GameScene::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}

// Update: draw background
update_status GameScene::Update()
{
	// Render
	App->renderer->Blit(sky, 0, 0, NULL);
	App->renderer->Blit(terrain, 0, SCREEN_HEIGHT - 100, NULL);

	// Mouse cursor
	corsairRec = corsairAnim.GetCurrentFrame();
	mousePos.x = App->input->GetMouseX()-5;
	mousePos.y = App->input->GetMouseY()-5;
	App->renderer->Blit(corsairTex, mousePos.x, mousePos.y, &corsairRec);

	// Instant Loss
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) App->fadeToBlack->Fade_To_Black(this, (Module*)App->gameOver, 0);

	// Numbers display
	if (App->collisions->debug == true)
	{
		App->fonts->BlitText(20, 20, fonts, "enemies");
		App->renderer->DrawNumber(numEnemies, 120, 20, 3, numbers, 7, 10);
		App->fonts->BlitText(20, 40, fonts, "boxes");
		App->renderer->DrawNumber(numBoxes, 120, 40, 3, numbers, 7, 10);
		App->fonts->BlitText(20, 60, fonts, "grenades");
		App->renderer->DrawNumber(numGren, 120, 60, 3, numbers, 7, 10);
	}

	return UPDATE_CONTINUE;
}

double GameScene::CalculateSpeed(double dx, double dy)
{
	double distance = sqrt(dx * dx + dy * dy);

	return distance / App->deltaTime;
}
