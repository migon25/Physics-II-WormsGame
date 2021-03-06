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
#include "EntityModule.h"
#include "ModuleCollisions.h"
#include "ModuleFonts.h"
#include "GameOver.h"

#include <iostream>

GameScene::GameScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	corsairAnim.PushBack({ 148,7,10,10 });
	corsairAnim.loop = false;

	grenade.PushBack({ 141, 435, 8, 8 });
	ice.PushBack({ 153,346,6,8 });
	missile.PushBack({ 191,375,4,8 });
	
}

GameScene::~GameScene()
{}

// Load assets
bool GameScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->audio->PlayMusic("Assets/wormsThemeSong.wav");
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
	
	App->entityModule->AddEntity(EntityModule::EntityType::ET_ENEMY, { SCREEN_WIDTH / 2, 50 });

	corsairTex = App->textures->Load("Assets/worms.png");

	// Ground
	ground = App->physics->CreatePhysBody(0, SCREEN_HEIGHT - 100, SCREEN_WIDTH, 150, Collider::Type::GROUND, this);
	terrain = App->textures->Load("Assets/ground.png");

	// Module enabler
	ground->physics_enabled = false;
	App->player->Enable();
	App->entityModule->Enable();
	App->physics->Enable();

	// Spawn boxes
	for (int i = 0; i < 2; i++) {
		App->entityModule->AddEntity(EntityModule::EntityType::ET_BOX, { 700, 380.0 - i*20.0 });
	}

	App->entityModule->AddEntity(EntityModule::EntityType::ET_BOX, { 730, 380 });
	App->entityModule->AddEntity(EntityModule::EntityType::ET_BOX, { 730, 360 });

	for (int i = 0; i < 2; i++) {
		App->entityModule->AddEntity(EntityModule::EntityType::ET_BOX, { 400, 380.0 - i * 20.0 });
	}

	for (int i = 0; i < 2; i++) {
		App->entityModule->AddEntity(EntityModule::EntityType::ET_BOX, { 500, 380.0 - i * 20.0 });
	}

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
	if (App->entityModule->GetTotalEntityCount() == 0) {
		App->gameOver->win = true;
		App->player->Disable();
		App->physics->Disable();
		App->entityModule->Disable();
		App->fadeToBlack->Fade_To_Black(this, App->gameOver, 60);
	}
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

	numEnemies = App->entityModule->entityCount[(int)EntityModule::EntityType::ET_ENEMY];
	numGren = App->entityModule->entityCount[(int) EntityModule::EntityType::ET_GRENADE];
	numBoxes = App->entityModule->entityCount[(int)EntityModule::EntityType::ET_BOX];
	numIce = App->entityModule->entityCount[(int)EntityModule::EntityType::ET_ICECUBE];
	veloInteg = (int) App->physics->GetVelocityIntegrator();

	// switch between velocities
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) 
	{
		veloInteg += 1;
		App->physics->SetVelocityIntegrator((ModulePhysics::VelocityIntegrator)veloInteg);
		if (veloInteg > 2)App->physics->SetVelocityIntegrator(ModulePhysics::VelocityIntegrator::VERLET);
	}
		
	// Numbers display
	if (App->collisions->debug == true)
	{
		// entity
		App->fonts->BlitText(20, 20, fonts, "enemies");
		App->renderer->DrawNumber(numEnemies, 120, 20, 3, numbers, 7, 10);
		App->fonts->BlitText(20, 40, fonts, "boxes");
		App->renderer->DrawNumber(numBoxes, 120, 40, 3, numbers, 7, 10);
		App->fonts->BlitText(20, 60, fonts, "grenades");
		App->renderer->DrawNumber(numGren, 120, 60, 3, numbers, 7, 10);
		App->fonts->BlitText(20, 80, fonts, "ice");
		App->renderer->DrawNumber(numIce, 120, 80, 3, numbers, 7, 10);

		// velocity
		App->fonts->BlitText(500, 20, fonts, "velocity");
		switch (veloInteg)
		{
		case 0:
			App->fonts->BlitText(610, 20, fonts, "verlet");
			break;

		case 1: 
			App->fonts->BlitText(610, 20, fonts, "sympleticeuler");
			break;

		case 2: 
			App->fonts->BlitText(610, 20, fonts, "impliciteuler");
			break;
		}
	}

	if (App->collisions->debug == false)
	{
		switch (App->player->weapon)
		{
		case 0:
			grenRec = grenade.GetCurrentFrame();
			App->renderer->Blit(corsairTex, 20, 20, &grenRec);
			break;

		case 1:
			iceRec = ice.GetCurrentFrame();
			App->renderer->Blit(corsairTex, 20, 20, &iceRec);
			break;
		case 2:
			missRec = missile.GetCurrentFrame();
			App->renderer->Blit(corsairTex, 20, 20, &missRec);
			break;
		}

	}

	return UPDATE_CONTINUE;
}

double GameScene::CalculateSpeed(double dx, double dy)
{
	double distance = sqrt(dx * dx + dy * dy);

	return distance / App->deltaTime;
}
