#pragma once
#include "Entity.h"

class IceCube : public Entity
{
private:
	float timer;
	float time;
public:
	IceCube(Application* app);
	~IceCube();

	void Init(Module* module) override;
	void Update(float dt) override;
	void Render() override;

	void OnCollision(Entity* other) override;
};