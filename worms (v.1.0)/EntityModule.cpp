#include "Application.h"
#include "EntityModule.h"
#include "Entity.h"
#include "Collider.h"
#include "Grenade.h"
#include "Box.h"

#include <iostream>

EntityModule::EntityModule(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	for (int i = 0; i < (int)EntityType::ET_LAST; i++) {
		entityCount[i] = 0;
	}
}

// Destructor
EntityModule::~EntityModule()
{}


// Called before the first frame
bool EntityModule::Start()
{
	return true;
}

// Called each loop iteration
update_status EntityModule::PreUpdate()
{
	return UPDATE_CONTINUE;
}

// Called each loop iteration
update_status EntityModule::Update()
{
	p2List_item<Entity*>* entity = entities.getFirst();

	while (entity) {

		entity->data->Update(App->deltaTime);

		if (entity->data->Remove()) {
			p2List_item<Entity*>* prev = entity->prev;

			entityCount[(int)entity->data->GetType()]--;

			entity->data->Cleanup();
			entities.del(entity);

			entity = prev;
		}

		if (entity) {
			entity = entity->next;
		}
	}

	return UPDATE_CONTINUE;
}

// Called each loop iteration
update_status EntityModule::PostUpdate()
{
	p2List_item<Entity*>* entity;

	for (entity = entities.getFirst(); entity != NULL; entity = entity->next) {
		entity->data->Render();
	}

	return UPDATE_CONTINUE;
}

void EntityModule::Deactivate()
{
	CleanUp();
}

// Called before quitting
bool EntityModule::CleanUp()
{
	LOG("Freeing enemies");

	p2List_item<Entity*>* entity;

	for (entity = entities.getFirst(); entity != NULL; entity = entity->next) {
		entity->data->Cleanup();
		delete entity->data;
	}

	entities.clear();

	return true;
}

Entity* EntityModule::AddEntity(EntityType type, Vector2 position)
{
	Entity* entity = nullptr;

	switch (type) {
	case EntityType::ET_GRENADE:
		entity = new Grenade(App);
		break;
	case EntityType::ET_BOX:
		entity = new Box(App);
		break;
	}

	entityCount[(int)type]++;

	entity->SetPosition(position);
	entity->Init(this);
	entities.add(entity);

	return entity;
}

void EntityModule::OnCollision(PhysBody * bodyA, PhysBody * bodyB)
{
	
}

int EntityModule::GetEntityCount(EntityType type)
{
	return entityCount[(int)type];
}
