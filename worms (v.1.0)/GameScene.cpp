#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleRender.h"
#include "FadeToBlack.h"
#include "GameScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

#include <iostream>

GameScene::GameScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

GameScene::~GameScene()
{}

// Load assets
bool GameScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	ball.mass = 10; // kg
	ball.surface = 2; // m^2
	ball.cd = -0.4;
	ball.cl = 1.2;

	// Set initial position and velocity of the ball
	ball.x = rand() % SCREEN_WIDTH;
	ball.y = 0.0;
	ball.vx = 0.0;
	ball.vy = 0.0;

	ground.x = 0.0;
	ground.y = SCREEN_HEIGHT - 5;
	
	atmosphere.windx = 10.0;
	atmosphere.windy = 0.0;
	atmosphere.density = 0.00001;

	return ret;
}

// Load assets
bool GameScene::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}

// Update: draw background
update_status GameScene::Update()
{
	// Instant Loss
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) App->fadeToBlack->Fade_To_Black(this, (Module*)App->gameOver, 0);

	// Step #0: Reset total acceleration and total accumulated force of the ball (clear old values)
	ball.fx = ball.fy = 0.0;
	ball.ax = ball.ay = 0.0;

	// Step #1: Compute forces

		// Compute Gravity force
	double fgx = ball.mass * 0.0;
	double fgy = ball.mass * 10.0; // Let's assume gravity is constant and downwards

	// Add gravity force to the total accumulated force of the ball
	ball.fx += fgx;
	ball.fy += fgy;

	// Compute Aerodynamic Lift & Drag forces
	double speed = CalculateSpeed(ball.vx - atmosphere.windx, ball.vy - atmosphere.windy);
	double fdrag = 0.5 * atmosphere.density * speed * speed * ball.surface * ball.cd;
	double flift = 0.5 * atmosphere.density * speed * speed * ball.surface * ball.cl;
	double fdx = -fdrag; // Let's assume Drag is aligned with x-axis (in your game, generalize this)
	double fdy = flift; // Let's assume Lift is perpendicular with x-axis (in your game, generalize this)

	// Add gravity force to the total accumulated force of the ball
	ball.fx += fdx;
	ball.fy += fdy;

	// Other forces
	// ...

// Step #2: 2nd Newton's Law: SUM_Forces = mass * accel --> accel = SUM_Forces / mass
	ball.ax = ball.fx / ball.mass;
	ball.ay = ball.fy / ball.mass;

	// Step #3: Integrate --> from accel to new velocity & new position. 
	// We will use the 2nd order "Velocity Verlet" method for integration.
	// You can also move this code into a subroutine: integrator_velocity_verlet(ball, dt);
	float dt = App->deltaTime;

	ball.x += ball.vx * dt + 0.5 * ball.ax * dt * dt;
	ball.y += ball.vy * dt + 0.5 * ball.ay * dt * dt;
	ball.vx += ball.ax * dt;
	ball.vy += ball.ay * dt;

	// Step #4: solve collisions
	if (ball.y > ground.y)
	{
		std::cout << "ground" << std::endl;
		// For now, just stop the ball when it reaches the ground.
		ball.vx = ball.vy = 0.0;
		ball.ax = ball.ay = 0.0;
		ball.fx = ball.fy = 0.0;
		ball.physics_enabled = false;
	}

	// Render
	App->renderer->DrawCircle(ball.x, ball.y, 5, 255, 255, 0, 255);

	std::cout << "Ball(x:" << ball.x << ", y:" << ball.y << ")" << std::endl;

	return UPDATE_CONTINUE;
}

void GameScene::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
}

double GameScene::CalculateSpeed(double dx, double dy)
{
	double distance = sqrt(dx * dx + dy * dy);

	return distance / App->deltaTime;
}
