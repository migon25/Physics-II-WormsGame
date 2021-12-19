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

	wormWalkRAnim.PushBack({ 33,6,12,15 });
	wormWalkRAnim.PushBack({ 44,6,12,15 });
	wormWalkRAnim.PushBack({ 58,5,12,15 });
	wormWalkRAnim.PushBack({ 69,6,12,15 });
	wormWalkRAnim.loop = true;
	wormWalkRAnim.speed = 0.1;

	wormWalkLAnim.PushBack({ 448,6,12,15 });
	wormWalkLAnim.PushBack({ 437,6,12,15 });
	wormWalkLAnim.PushBack({ 421,5,12,15 });
	wormWalkLAnim.PushBack({ 410,6,12,15 });
	wormWalkLAnim.loop = true;
	wormWalkLAnim.speed = 0.1;

	currentWormAnim = &wormAnim;

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
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		playerBody->position.x += 2;

		//animation 
		currentWormAnim = &wormWalkRAnim;
		wormWalkRAnim.Update();
		wormText = wormWalkRAnim.GetCurrentFrame();
		App->renderer->Blit(worm, playerBody->position.x, playerBody->position.y, &wormText);
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		playerBody->position.x -= 2;

		//animation 
		currentWormAnim = &wormWalkLAnim;
		wormWalkLAnim.Update();
		wormText = wormWalkLAnim.GetCurrentFrame();
		App->renderer->Blit(worm, playerBody->position.x, playerBody->position.y, &wormText);
	}

	return UPDATE_CONTINUE;
}



