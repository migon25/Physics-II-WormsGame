#pragma once

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Vector2.h"

class Entity;

class EntityModule : public Module
{
public:
	enum class EntityType {
		ET_GRENADE,
		ET_BOX,
		ET_LAST
	};

	EntityModule(Application* app, bool start_enabled);

	// Destructor
	virtual ~EntityModule();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	update_status PreUpdate();

	// Called each loop iteration
	update_status Update();

	// Called before all Updates
	update_status PostUpdate() override;

	// called to deactivate module
	void Deactivate();

	// Called before quitting
	bool CleanUp();

	Entity* AddEntity(EntityType type, Vector2 position);

	// Called when player collides with an object
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB) override;
private:
	p2List<Entity*> entities;
};