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

#include <iostream>

GameScene::GameScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

GameScene::~GameScene()
{}

// Load assets
bool GameScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	//App->physics->SetAtmosphere(-10.0, 0, 0.00001);

	ball = App->physics->CreatePhysBody(SCREEN_WIDTH / 2, 0, 10, 10, Collider::Type::BULLET, this);

	ball->mass = 10; // kg
	ball->surface = 2; // m^2
	ball->dragCoefficient = -0.4;
	ball->liftCoefficient = 1.2;
	ball->frictionCoefficient = 0.5;

	ground = App->physics->CreatePhysBody(0, SCREEN_HEIGHT - 50, SCREEN_WIDTH, 50, Collider::Type::NONE, this);

	ground->physics_enabled = false;

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
	// Instant Loss
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) App->fadeToBlack->Fade_To_Black(this, (Module*)App->gameOver, 0);

	// Render
	App->renderer->DrawQuad(ball->collider->rect, 255, 255, 0, 255);

	App->renderer->DrawQuad(ground->collider->rect, 255, 255, 255, 255);

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		SDL_Rect rect;
		rect.x = App->input->GetMouseX() - 25;
		rect.y = App->input->GetMouseY() - 25;
		rect.w = 50;
		rect.h = 50;
		PhysBody* pb = App->physics->CreatePhysBody(rect, Collider::Type::NONE, this);
		pb->mass = 30;
		pb->frictionCoefficient = 0.5;
		pb->physics_enabled = true;
	}

	return UPDATE_CONTINUE;
}

double GameScene::CalculateSpeed(double dx, double dy)
{
	double distance = sqrt(dx * dx + dy * dy);

	return distance / App->deltaTime;
}
