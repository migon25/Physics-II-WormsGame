#pragma once
#include "Entity.h"

class IceCube : public Entity
{
public:
	IceCube(Application* app);
	~IceCube();

	void Init(Module* module) override;
	void Update(float dt) override;
	void Render() override;

	void Die() override;
};