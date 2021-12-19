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
	rect = { 141,435,8,8 };

	texture = App->textures->Load("Assets/worms.png");

	SDL_Rect pbodyRect;
	pbodyRect.x = position.x;
	pbodyRect.y = position.y;
	pbodyRect.w = 8;
	pbodyRect.h = 8;

	entityBody = App->physics->CreatePhysBody(pbodyRect, Collider::Type::BULLET, module);
	entityBody->mass = 80;
	entityBody->frictionCoefficient = 1.0;
	entityBody->restitutionCoefficient = 0.1;
	entityBody->physics_enabled = true;

	type = EntityModule::EntityType::ET_GRENADE;

	time = 5.0f;
	timer = 0.0f;

	distanceExplosion = 10.0;
}

void Grenade::Update(float dt)
{
	Entity::Update(dt);

	timer += dt;

	if (timer >= time) {
		Die();
	}
}

void Grenade::Render()
{
	App->renderer->Blit(texture, entityBody->position.x, entityBody->position.y, &rect);
}

void Grenade::Die()
{
	Entity::Die();

	p2List<Entity*> closestList = App->entityModule->GetEntitiesInRadius(this, distanceExplosion);

	p2List_item<Entity*>* entity = closestList.getFirst();

	while (entity) {
		entity->data->Die();
		entity = entity->next;
	}
}