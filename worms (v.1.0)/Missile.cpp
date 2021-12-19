#include "Missile.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

Missile::Missile(Application * app) : Entity(app)
{
}

Missile::~Missile()
{
}

void Missile::Init(Module * module)
{
	rect = { 206, 238, 6, 8 };

	texture = App->textures->Load("Assets/worms.png");

	SDL_Rect pbodyRect;
	pbodyRect.x = position.x;
	pbodyRect.y = position.y;
	pbodyRect.w = 6;
	pbodyRect.h = 8;

	entityBody = App->physics->CreatePhysBody(pbodyRect, Collider::Type::BULLET, module);
	entityBody->mass = 200;
	entityBody->dragCoefficient = 0.0;
	entityBody->liftCoefficient = 0.0;
	entityBody->frictionCoefficient = 0.0;
	entityBody->restitutionCoefficient = 0.0;
	entityBody->gravityScale = 0.0;
	entityBody->physics_enabled = true;

	type = EntityModule::EntityType::ET_MISSILE;

	distanceExplosion = 250.0;
}

void Missile::Update(float dt)
{
	Entity::Update(dt);
}

void Missile::Render()
{
	App->renderer->Blit(texture, entityBody->position.x, entityBody->position.y, &rect);
}

void Missile::OnCollision(Entity * other)
{
	Die();
}

void Missile::Die()
{
	Entity::Die();

	p2List<Entity*>* closestList = App->entityModule->GetEntitiesInRadius(this, distanceExplosion);

	p2List_item<Entity*>* entity = closestList->getFirst();

	while (entity) {
		entity->data->Die();
		entity = entity->next;
	}

	closestList->clear();
	delete closestList;
}
