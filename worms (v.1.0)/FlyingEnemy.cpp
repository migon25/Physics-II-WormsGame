#include "FlyingEnemy.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"


FlyingEnemy::FlyingEnemy(Application* app) : Entity(app)
{
}


FlyingEnemy::~FlyingEnemy()
{
}

void FlyingEnemy::Init(Module * module)
{
	rect = { 149,310,10,17 };

	texture = App->textures->Load("Assets/worms.png");

	SDL_Rect pbodyRect;
	pbodyRect.x = position.x;
	pbodyRect.y = position.y;
	pbodyRect.w = 10;
	pbodyRect.h = 17;

	entityBody = App->physics->CreatePhysBody(pbodyRect, Collider::Type::TARGET, module);
	entityBody->mass = 100; // kg
	entityBody->surface = 2; // m^2
	entityBody->dragCoefficient = -0.4;
	entityBody->liftCoefficient = 1.2;
	entityBody->frictionCoefficient = 1.0;
	entityBody->restitutionCoefficient = 1.0;
	entityBody->physics_enabled = true;

	type = EntityModule::EntityType::ET_ENEMY;
}

void FlyingEnemy::Update(float dt)
{
	Entity::Update(dt);
}

void FlyingEnemy::Render()
{
	App->renderer->Blit(texture, entityBody->position.x, entityBody->position.y, &rect);
}
