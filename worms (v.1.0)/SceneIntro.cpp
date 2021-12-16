#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "FadeToBlack.h"

SceneIntro::SceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

SceneIntro::~SceneIntro()
{
}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	App->renderer->camera.x = App->renderer->camera.y = 0;
	App->audio->Init();

	bool ret = true;

	return ret;
}

update_status SceneIntro::Update()
{
	// fade to black to game scene
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->fadeToBlack->Fade_To_Black(this, (Module*)App->gameScene, 0);
	}

	// Put images, example: App->renderer->Blit(Title, 0, 0, NULL);
	
	return UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	return true;
}