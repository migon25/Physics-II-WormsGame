#pragma once
#include "Entity.h"

class Box : public Entity
{
public:
	Box(Application* app);
	~Box();

	void Init(Module* module) override;
	void Update(float dt) override;
	void Render() override;
};