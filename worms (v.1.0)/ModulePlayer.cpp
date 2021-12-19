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
	playerBody->restitutionCoefficient = 0.0;

	animations[PS_IDLE].PushBack({ 8,7,8,13 });
	animations[PS_IDLE].loop = false;

	animations[PS_WALK].PushBack({ 8,7,8,13 });
	animations[PS_WALK].PushBack({ 19,7,8,13 });
	animations[PS_WALK].loop = true;
	animations[PS_WALK].speed = 0.05f;

	speedometer.PushBack({ 7,483,28,16 });
	speedometer.PushBack({ 41,483,28,16 });
	speedometer.PushBack({ 75,483,28,16 });
	speedometer.PushBack({ 108,483,28,16 });
	speedometer.PushBack({ 142,483,28,16 });
	speedometer.PushBack({ 175,483,28,16 });
	speedometer.loop = true;
	speedometer.speed = 0.15f;


	worm = App->textures->Load("Assets/worms.png");

<<<<<<< HEAD
	currentWormAnim = &wormIdle;
	currentSpeedometerAnim = &speedometer;
=======
	state = PS_IDLE;
>>>>>>> 72624a58fa2fed1aa14970a8ef7056cd421626ef

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
	state = PS_IDLE;

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) 
	{
		state = PS_WALK;
		flip = SDL_FLIP_NONE;
		playerBody->position.x += 1;
		prevPos = playerBody->position.x - 1;
	} 
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) 
	{
		state = PS_WALK;
		flip = SDL_FLIP_HORIZONTAL;
		playerBody->position.x -= 1;
		prevPos = playerBody->position.x + 1;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		playerBody->Impulse(0, -50000);
	}

	animations[state].Update();

	return UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	SDL_Rect animRect = animations[state].GetCurrentFrame();

<<<<<<< HEAD
	speed = currentSpeedometerAnim->GetCurrentFrame();

	App->renderer->Blit(worm, 10, 10, &speed);

	currentSpeedometerAnim->Update();
	currentWormAnim->Update();
=======
	App->renderer->Blit(worm, playerBody->position.x, playerBody->position.y, &animRect, 1.0f, 0.0, flip);
>>>>>>> 72624a58fa2fed1aa14970a8ef7056cd421626ef

	return UPDATE_CONTINUE;
}



