#include "Box.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"


Box::Box(Application* app) : Entity(app)
{
}


Box::~Box()
{
}

void Box::Init(Module * module)
{
	//rect = { 148,7,10,10 };
	//texture = App->textures->Load("Assets/worms.png");

	SDL_Rect pbodyRect;
	pbodyRect.x = position.x;
	pbodyRect.y = position.y;
	pbodyRect.w = 20;
	pbodyRect.h = 20;

	entityBody = App->physics->CreatePhysBody(pbodyRect, Collider::Type::TARGET, module);
	entityBody->mass = 20;
	entityBody->frictionCoefficient = 0.0;
	entityBody->restitutionCoefficient = 0.0;
	entityBody->physics_enabled = true;

	type = EntityModule::EntityType::ET_BOX;
}

void Box::Update(float dt)
{
}

void Box::Render()
{
}