#include "GameOver.h"

#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "FadeToBlack.h"
#include "Globals.h"

GameOver::GameOver(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

GameOver::~GameOver()
{
}

// Load assets
bool GameOver::Start()
{
	LOG("Loading GameOver screen");

	bool ret = true;

	App->renderer->camera.x = 0;
	App->renderer->camera.y = 0;

	return ret;
}

update_status GameOver::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->fadeToBlack->Fade_To_Black(this, (Module*)App->sceneIntro, 0);
	}

	return UPDATE_CONTINUE;
}

update_status GameOver::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool GameOver::CleanUp()
{
	LOG("Freeing scene GameOver");
	App->audio->Clear();
	return true;
}