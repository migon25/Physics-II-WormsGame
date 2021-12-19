#include "Grenade.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

Grenade::Grenade(Application* app) : Entity(app)
{
}


Grenade::~Grenade()
{
}

void Grenade::Init(Module * module)
{
	rect = { 153,346,6,8 };

	texture = App->textures->Load("Assets/worms.png");

	SDL_Rect pbodyRect;
	pbodyRect.x = position.x;
	pbodyRect.y = position.y;
	pbodyRect.w = 10;
	pbodyRect.h = 10;

	entityBody = App->physics->CreatePhysBody(pbodyRect, Collider::Type::BULLET, module);
	entityBody->mass = 30;
	entityBody->frictionCoefficient = 0.5;
	entityBody->restitutionCoefficient = 0.5;
	entityBody->physics_enabled = true;

	type = EntityModule::EntityType::ET_GRENADE;
}

void Grenade::Update(float dt)
{
}

void Grenade::Render()
{
	App->renderer->Blit(texture, entityBody->position.x, entityBody->position.y, &rect);
}