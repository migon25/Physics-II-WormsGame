#pragma once
#include "Module.h"
#include "Globals.h"
#include "Vector2.h"
#include "Collider.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y 100.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !
#define RAD_PER_DEG ((float)180/b2_pi)
#define DEG_PER_RAD ((float)b2_pi/180)

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * (m)))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * (p))
#define RAD_TO_DEG(r) ((float) RAD_PER_DEG * (r))
#define DEG_TO_RAD(r) ((float) DEG_PER_RAD * (r))

#define MAX_PHYSICS_BODIES 350

enum class Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

// Small class to return to other modules to track position and rotation of physics bodies
struct PhysBody
{
	// Position
	// You could also use an array/vector
	Vector2 position;

	// Velocity
	Vector2 velocity;

	// Acceleration
	Vector2 acceleration;

	// Force (total) applied to the ball
	Vector2 totalForce;

	Vector2 lastMoveStep;

	// Mass
	double mass;

	// Aerodynamics stuff
	double surface; // Effective wet surface
	double dragCoefficient;
	double liftCoefficient;

	double frictionCoefficient;
	double restitutionCoefficient;

	bool oncontact;
	bool impulse;

	Vector2 impulseForce;

	Collider* collider;
	double gravityScale;

	void GetPosition(int& x, int &y) const;
	void SetPosition(int x, int y);

	void Impulse(double x, double y);

	void Remove();

	bool pendingToDelete;
	bool physics_enabled;
};

struct Atmosphere {
	double windx;
	double windy;

	double density;
};

// Module --------------------------------------
class ModulePhysics : public Module // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreatePhysBody(SDL_Rect rect, Collider::Type type, Module* listener);
	PhysBody* CreatePhysBody(int x, int y, int width, int height, Collider::Type type, Module* listener);

	void OnCollision(Collider* colA, Collider* colB) override;

	void SetAtmosphere(double _windX, double _windY, double _density) { atmosphere.windx = _windX; atmosphere.windy = _windY; atmosphere.density = _density; };
private:
	PhysBody* physicsBodies[MAX_PHYSICS_BODIES] = { nullptr };

	Atmosphere atmosphere;

	void UpdateBody(PhysBody* body);

	Direction GetCollisionDirection(Vector2 difference);
	double CalculateSpeed(double dx, double dy);
};