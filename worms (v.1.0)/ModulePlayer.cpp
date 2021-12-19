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
	wormRect.y = 350;
	wormRect.w = 8;
	wormRect.h = 13;
	playerBody = App->physics->CreatePhysBody(wormRect, Collider::Type::PLAYER, this);

	playerBody->mass = 10; // kg
	playerBody->surface = 2; // m^2
	playerBody->dragCoefficient = 0.0;
	playerBody->liftCoefficient = 0.0;
	playerBody->frictionCoefficient = 0.0;

	wormIdle.PushBack({ 8,7,8,13 });
	wormIdle.loop = false;

	wormWalk.PushBack({ 8,7,8,13 });
	wormWalk.PushBack({ 19,7,8,13 });
	wormWalk.loop = true;
	wormWalk.speed = 0.05f;

	worm = App->textures->Load("Assets/worms.png");

	currentWormAnim = &wormIdle;

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
	wormText = currentWormAnim->GetCurrentFrame();
	
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) 
	{
		currentWormAnim = &wormWalk;
		App->renderer->Blit(worm, playerBody->position.x, playerBody->position.y, &wormText);
		playerBody->position.x += 1;
		prevPos = playerBody->position.x - 1;
	} 
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) 
	{
		currentWormAnim = &wormWalk;
		App->renderer->Blit(worm, playerBody->position.x, playerBody->position.y, &wormText, false, 1.0, SDL_FLIP_HORIZONTAL);
		playerBody->position.x -= 1;
		prevPos = playerBody->position.x + 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		playerBody->velocity.y -= 50;
	}

	if ((App->input->GetKey(SDL_SCANCODE_A) == false) && (App->input->GetKey(SDL_SCANCODE_D) == false))
	{
		currentWormAnim = &wormIdle;
		if (playerBody->position.x < prevPos) App->renderer->Blit(worm, playerBody->position.x, playerBody->position.y, &wormText, false, 1.0, SDL_FLIP_HORIZONTAL);;
		if (playerBody->position.x > prevPos) App->renderer->Blit(worm, playerBody->position.x, playerBody->position.y, &wormText);
	}

	currentWormAnim->Update();

	return UPDATE_CONTINUE;
}



