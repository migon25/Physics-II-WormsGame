#pragma once
#include "Entity.h"

class Grenade : public Entity
{
public:
	Grenade(Application* app);
	~Grenade();

	void Init(Module* module) override;
	void Update(float dt) override;
	void Render() override;
};