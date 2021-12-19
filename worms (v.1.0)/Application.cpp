
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModulePhysics.h"
#include "SceneIntro.h"
#include "GameOver.h"
#include "GameScene.h"
#include "FadeToBlack.h"
#include "ModuleCollisions.h"
#include "EntityModule.h"

#include "Application.h"
#include <time.h>

Application::Application()
{
	renderer = new ModuleRender(this);
	window = new ModuleWindow(this);
	textures = new ModuleTextures(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this);
	fadeToBlack = new FadeToBlack(this);
	player = new ModulePlayer(this,false);
	fonts = new ModuleFonts(this, true);
	sceneIntro = new SceneIntro(this, true);
	gameOver = new GameOver(this, false);
	gameScene = new GameScene(this,false);
	physics = new ModulePhysics(this, false);
	collisions = new ModuleCollisions(this, true);
	entityModule = new EntityModule(this, false);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(physics);
	AddModule(collisions);
	AddModule(textures);
	AddModule(input);
	AddModule(audio);
	AddModule(fonts);

	// Scenes
	AddModule(sceneIntro);
	AddModule(gameScene);
	AddModule(gameOver);

	AddModule(fadeToBlack);
	
	// Player
	AddModule(entityModule);
	AddModule(player);

	AddModule(renderer);
}

Application::~Application()
{
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL)
	{
		delete item->data;
		item = item->prev;
	}
}

bool Application::Init()
{
	bool ret = true;

	srand(time(NULL));

	// Call Init() in all modules
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		ret = item->data->Init();
		item = item->next;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		if(item->data->IsEnabled())
			ret = item->data->Start();
		item = item->next;
	}

	msFrame = 1.0f / FPS;

	lastTime = SDL_GetTicks();

	deltaTime = msFrame;
	
	return ret;
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PreUpdate();
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
  			ret = item->data->Update();
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PostUpdate();
		item = item->next;
	}

	// FPS Control
	currentTime = SDL_GetTicks();

	deltaTime = (currentTime - lastTime) / 1000.0f;

	if (deltaTime < msFrame) {
		SDL_Delay(msFrame - deltaTime);
	}

	lastTime = SDL_GetTicks();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.add(mod);
}