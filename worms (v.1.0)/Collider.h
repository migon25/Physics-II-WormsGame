#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"
#include "p2Point.h"
#define MAX_LISTENERS 5

class Module;

struct Collider
{
	enum Type
	{
		NONE,
		GROUND,
		PLAYER,
		BULLET,
		ENEMY,
		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	iPoint GetPos() { return iPoint{ rect.x,rect.y }; }

	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	bool isSensor = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__
