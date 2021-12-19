#pragma once
#include "Entity.h"

class Missile : public Entity
{
private:
	double distanceExplosion;
public:
	Missile(Application* app);
	~Missile();

	void Init(Module* module) override;
	void Update(float dt) override;
	void Render() override;

	void OnCollision(Entity* other) override;

	void Die() override;
};