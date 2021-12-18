#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "ModuleCollisions.h"
#include "p2Point.h"
#include "math.h"
#include <cmath>
#include "Collider.h"

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	for (uint i = 0; i < MAX_PHYSICS_BODIES; ++i)
		physicsBodies[i] = nullptr;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// Remove all physic bodies scheduled for deletion
	for (uint i = 0; i < MAX_PHYSICS_BODIES; ++i)
	{
		if (physicsBodies[i] != nullptr)
		{
			if (physicsBodies[i]->pendingToDelete == true) {
				delete physicsBodies[i];
				physicsBodies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

update_status ModulePhysics::Update()
{
	for (uint i = 0; i < MAX_PHYSICS_BODIES; ++i)
	{
		if (physicsBodies[i] != nullptr)
		{
			if (physicsBodies[i]->physics_enabled) {
				UpdateBody(physicsBodies[i]);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	for (uint i = 0; i < MAX_PHYSICS_BODIES; ++i)
	{
		if (physicsBodies[i] != nullptr)
		{
			delete physicsBodies[i];
			physicsBodies[i] = nullptr;
		}
	}


	return true;
}

PhysBody * ModulePhysics::CreatePhysBody(SDL_Rect rect, Collider::Type type, Module* listener)
{
	PhysBody* pbody = new PhysBody();
	pbody->collider = App->collisions->AddCollider(rect, type, listener);
	pbody->collider->AddListener(this);

	pbody->position.x = rect.x;
	pbody->position.y = rect.y;

	pbody->velocity = { 0, 0 };

	pbody->surface = 0.0;

	pbody->gravityScale = 1;
	pbody->dragCoefficient = 0.0;
	pbody->frictionForce = 0.0;
	pbody->liftCoefficient = 0.0;

	pbody->physics_enabled = true;

	pbody->pendingToDelete = false;
	
	for (int i = 0; i < MAX_PHYSICS_BODIES; i++) {
		if (physicsBodies[i] == nullptr) {
			physicsBodies[i] = pbody;
			break;
		}
	}

	return pbody;
}

PhysBody * ModulePhysics::CreatePhysBody(int x, int y, int width, int height, Collider::Type type, Module * listener)
{
	return CreatePhysBody({ x,y,width,height },type,listener);
}

void ModulePhysics::OnCollision(Collider * colA, Collider * colB)
{

}

void ModulePhysics::UpdateBody(PhysBody * body)
{
	// Step #0: Reset total acceleration and total accumulated force of the ball (clear old values)
	body->totalForce = { 0.0, 0.0 };
	body->acceleration = { 0.0, 0.0 };

	// Step #1: Compute forces

		// Compute Gravity force
	double fgx = body->mass * GRAVITY_X;
	double fgy = body->mass * -GRAVITY_Y; // Let's assume gravity is constant and downwards

	// Add gravity force to the total accumulated force of the ball
	body->totalForce.x += fgx;
	body->totalForce.y += fgy;

	// Compute Aerodynamic Lift & Drag forces
	double speed = CalculateSpeed(body->velocity.x - atmosphere.windx, body->velocity.y - atmosphere.windy);
	double dragDirection = atmosphere.windx ? atmosphere.windx / abs(atmosphere.windx) : 1;
	double liftDirection = atmosphere.windy ? atmosphere.windy / abs(atmosphere.windy) : 1;
	double fdrag = 0.5 * atmosphere.density * speed * speed * body->surface * body->dragCoefficient * dragDirection;
	double flift = 0.5 * atmosphere.density * speed * speed * body->surface * body->liftCoefficient * liftDirection;
	double fdx = -fdrag; // Let's assume Drag is aligned with x-axis (in your game, generalize this)
	double fdy = flift; // Let's assume Lift is perpendicular with x-axis (in your game, generalize this)

	// Add gravity force to the total accumulated force of the ball
	body->totalForce.x += fdx;
	body->totalForce.y += fdy;

	// Other forces
	// ...

// Step #2: 2nd Newton's Law: SUM_Forces = mass * accel --> accel = SUM_Forces / mass
	body->acceleration.x = body->totalForce.x / body->mass;
	body->acceleration.y = body->totalForce.y / body->mass;

	// Step #3: Integrate --> from accel to new velocity & new position. 
	// We will use the 2nd order "Velocity Verlet" method for integration.
	// You can also move this code into a subroutine: integrator_velocity_verlet(ball, dt);
	float dt = App->deltaTime;

	body->position.x += body->velocity.x * dt + 0.5 * body->acceleration.x * dt * dt;
	body->position.y += body->velocity.y * dt + 0.5 * body->acceleration.y * dt * dt;
	body->velocity.x += body->acceleration.x * dt;
	body->velocity.y += body->acceleration.y * dt;

	// Step #4: solve collisions
	if (body->position.y > SCREEN_HEIGHT - 50)
	{
		// For now, just stop the ball when it reaches the ground.
		body->physics_enabled = false;
	}
}

double ModulePhysics::CalculateSpeed(double dx, double dy)
{
	double distance = sqrt(dx * dx + dy * dy);

	return distance / App->deltaTime;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	x = collider->rect.x;
	y = collider->rect.y;
}

void PhysBody::Remove()
{
	pendingToDelete = true;
	collider->pendingToDelete = true;
}
