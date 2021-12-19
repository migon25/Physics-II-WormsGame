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
	rect = { 141,464,8,8 };
	texture = App->textures->Load("Assets/worms.png");

	SDL_Rect pbodyRect;
	pbodyRect.x = position.x;
	pbodyRect.y = position.y;
	pbodyRect.w = 8;
	pbodyRect.h = 8;

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
	App->renderer->Blit(texture, entityBody->position.x, entityBody->position.y, &rect);
}