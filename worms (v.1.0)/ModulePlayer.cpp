#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "GameScene.h"
#include "EntityModule.h"
#include "Grenade.h"

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

	worm = App->textures->Load("Assets/worms.png");

	state = PS_IDLE;

	grenadeOffset = 10.0;
	maxForce = 260000;
	minForce = 250000;
	grenadeForce = minForce;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

void ModulePlayer::Shoot()
{
	int mouseX = App->input->GetMouseX();
	int mouseY = App->input->GetMouseY();
	Vector2 mousePos(mouseX, mouseY);

	Vector2 diff = mousePos - playerBody->position;
	diff.Normalize();

	Vector2 grenadePos = playerBody->position + (diff * grenadeOffset);
	Vector2 grenadeImpulse = diff * grenadeForce;

	Entity* entity = App->entityModule->AddEntity(EntityModule::EntityType::ET_GRENADE, grenadePos);
	entity->Impulse(grenadeImpulse);
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

	if (App->input->GetMouseButton(1) == KEY_REPEAT) {
		grenadeForce += 2500;
		if (grenadeForce == maxForce) grenadeForce = maxForce;
	}
	if (App->input->GetMouseButton(1) == KEY_UP) {
		Shoot();
		grenadeForce = minForce;
	}

	animations[state].Update();

	return UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	SDL_Rect animRect = animations[state].GetCurrentFrame();

	App->renderer->Blit(worm, playerBody->position.x, playerBody->position.y, &animRect, 1.0f, 0.0, flip);

	return UPDATE_CONTINUE;
}



