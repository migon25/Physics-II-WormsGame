#include "ModuleCollisions.h"

#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::TARGET] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BULLET] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::GROUND] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::NONE] = true;

	matrix[Collider::Type::TARGET][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TARGET][Collider::Type::TARGET] = true;
	matrix[Collider::Type::TARGET][Collider::Type::BULLET] = true;
	matrix[Collider::Type::TARGET][Collider::Type::GROUND] = true;
	matrix[Collider::Type::TARGET][Collider::Type::NONE] = true;

	matrix[Collider::Type::BULLET][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BULLET][Collider::Type::TARGET] = true;
	matrix[Collider::Type::BULLET][Collider::Type::BULLET] = true;
	matrix[Collider::Type::BULLET][Collider::Type::GROUND] = true;
	matrix[Collider::Type::BULLET][Collider::Type::NONE] = true;

	matrix[Collider::Type::NONE][Collider::Type::NONE] = true;
	matrix[Collider::Type::NONE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::NONE][Collider::Type::TARGET] = true;
	matrix[Collider::Type::NONE][Collider::Type::GROUND] = true;
	matrix[Collider::Type::NONE][Collider::Type::BULLET] = true;

	matrix[Collider::Type::GROUND][Collider::Type::GROUND] = false;
	matrix[Collider::Type::GROUND][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::GROUND][Collider::Type::TARGET] = true;
	matrix[Collider::Type::GROUND][Collider::Type::BULLET] = true;
	matrix[Collider::Type::GROUND][Collider::Type::NONE] = true;

}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

update_status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			if (colliders[i]->pendingToDelete == true) {
				delete colliders[i];
				colliders[i] = nullptr;
			}
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollisions::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	return UPDATE_CONTINUE;
}

update_status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case Collider::Type::BULLET: // orange
			App->renderer->DrawQuad(colliders[i]->rect, 255, 122, 0, alpha);
			break;
		case Collider::Type::PLAYER: // green
			App->renderer->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::TARGET: // red
			App->renderer->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::NONE: // white
			App->renderer->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::GROUND: // green
			App->renderer->DrawQuad(colliders[i]->rect, 84, 141, 84, 255);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}