#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	wormRect.x = SCREEN_WIDTH / 5;
	wormRect.y = 100;
	wormRect.w = 8;
	wormRect.h = 13;
	playerBody = App->physics->CreatePhysBody(wormRect, Collider::Type::PLAYER, this);

	playerBody->mass = 10; // kg
	playerBody->surface = 2; // m^2
	playerBody->dragCoefficient = -0.4;
	playerBody->liftCoefficient = 1.2;
	playerBody->frictionCoefficient = 1.0;

	wormAnim.PushBack({ 8,7,8,13 });
	worm = App->textures->Load("Assets/worms.png");

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	wormText = wormAnim.GetCurrentFrame();
	App->renderer->Blit(worm, playerBody->position.x, playerBody->position.y, &wormText,false,1.0,SDL_FLIP_HORIZONTAL);
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) playerBody->position.x += 2;
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) playerBody->position.x -= 2;

	return UPDATE_CONTINUE;
}



