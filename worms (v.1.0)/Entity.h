#pragma once

#include "Animation.h"
#include "ModulePhysics.h"
#include "EntityModule.h"

#include "SDL/include/SDL_render.h"

#include "p2List.h"
#include "Collider.h"
#include "Vector2.h"

class Entity
{
protected:
	Application* App;

	EntityModule::EntityType type;

	Vector2 position;
	SDL_Texture* texture;
	
	p2List<Animation> animations;
	SDL_Rect rect;

	int collisionWidth, collisionHeight;

	PhysBody* entityBody;

	bool remove;
public:
	Entity(Application* app);
	~Entity();

	virtual void Init(Module* module){}
	virtual void Update(float dt) { position = entityBody->position; }
	virtual void Render(){}

	void SetPosition(Vector2 pos) { position = pos; }

	Collider::Type GetColliderType() { return entityBody->collider->type; }
	EntityModule::EntityType GetType() { return type; }

	bool HasCollider(Collider* col) { return entityBody->collider == col; }

	virtual void Cleanup();
	virtual void Die() { remove = true; }

	bool Remove() { return remove; }

	Vector2 GetPosition() { return position; }

	void Impulse(Vector2 impulse);

	virtual void OnCollision(Entity* other){}
};