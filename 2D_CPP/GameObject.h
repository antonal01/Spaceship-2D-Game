#pragma once
#include "util.h"

class Collidable {
public:
	virtual Disk getCollisionHull() const = 0;
};

class GameObject {
protected:
	const class Game& game1;
public:
	GameObject(const class Game & mygame1);
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
};