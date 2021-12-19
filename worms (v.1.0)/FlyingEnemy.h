#pragma once
#include "Entity.h"

class FlyingEnemy : public Entity
{
public:
	FlyingEnemy(Application* app);
	~FlyingEnemy();

	void Init(Module* module) override;
	void Update(float dt) override;
	void Render() override;
};

