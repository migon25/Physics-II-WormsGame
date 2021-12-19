#include "Entity.h"

Entity::Entity(Application* app) : App(app)
{
	entityBody = NULL;
	remove = false;
}

Entity::~Entity()
{
}

void Entity::Cleanup()
{
	if (entityBody) {
		entityBody->pendingToDelete = true;
		entityBody->collider->pendingToDelete = true;
	}
}

void Entity::Impulse(Vector2 impulse)
{
	entityBody->Impulse(impulse.x, impulse.y);
}
