#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

struct PhysicsBody
{
	// Position
	// You could also use an array/vector
	double x;
	double y;

	// Velocity
	double vx;
	double vy;

	// Acceleration
	double ax;
	double ay;

	// Force (total) applied to the ball
	double fx;
	double fy;

	// Mass
	double mass;

	// Aerodynamics stuff
	double surface; // Effective wet surface
	double cl; // Lift coefficient
	double cd; // Drag coefficient

	// Has physics enabled?
	bool physics_enabled = true;
};

struct Atmosphere {
	double windx;
	double windy;

	double density;
};

class GameScene : public Module
{
public:
	GameScene(Application* app, bool start_enabled = true);
	~GameScene();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	double CalculateSpeed(double dx, double dy);
public:
	PhysicsBody ball;
	Atmosphere atmosphere;
	dPoint ground;
};
