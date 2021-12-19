#pragma once
#include "Entity.h"

class Grenade : public Entity
{
private:
	float timer;
	float time;

	double distanceExplosion;
public:
	Grenade(Application* app);
	~Grenade();

	void Init(Module* module) override;
	void Update(float dt) override;
	void Render() override;

	void Die() override;
};