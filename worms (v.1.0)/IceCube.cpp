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
	rect = { 141, 435, 8, 8 };

	texture = App->textures->Load("Assets/worms.png");

	SDL_Rect pbodyRect;
	pbodyRect.x = position.x;
	pbodyRect.y = position.y;
	pbodyRect.w = 10;
	pbodyRect.h = 10;

	entityBody = App->physics->CreatePhysBody(pbodyRect, Collider::Type::BULLET, module);
	entityBody->mass = 30;
	entityBody->frictionCoefficient = 1.0;
	entityBody->restitutionCoefficient = 0.1;
	entityBody->physics_enabled = true;

	type = EntityModule::EntityType::ET_ICECUBE;

	timer = 0.0f;
	time = 1.5f;
}

void IceCube::Update(float dt)
{
	Entity::Update(dt);

	timer >= dt;

	if (timer >= time) {
		Die();
	}
}

void IceCube::Render()
{
	App->renderer->Blit(texture, entityBody->position.x, entityBody->position.y, &rect);
}