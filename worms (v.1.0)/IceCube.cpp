#include "IceCube.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

IceCube::IceCube(Application* app) : Entity(app)
{
}


IceCube::~IceCube()
{
}

void IceCube::Init(Module* module)
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
	entityBody->frictionCoefficient = 0.3;
	entityBody->restitutionCoefficient = 0.5;
	entityBody->physics_enabled = true;

	type = EntityModule::EntityType::ET_ICECUBE;
}

void IceCube::Update(float dt)
{
}

void IceCube::Render()
{
	App->renderer->Blit(texture, entityBody->position.x, entityBody->position.y, &rect);
}

void IceCube::Die()
{
	Entity::Remove();
}