#pragma once
#include "GameObject.h"
#include "graphics.h"


class Sprite :public GameObject, public Collidable {
	float pos_x = 1.0f, pos_y = 1.0f;
	float size = 1.0f;
	float time = 0.0f;
	graphics::Brush brush;
	bool active = false;
	bool initialized = false;
	bool initialized1 = false;
	bool erased = false;
public:
	Disk getCollisionHull() const override;
	Sprite(const class Game& mygame1);
	const float  getPosY() { return pos_y; }
	const float  getPosX() { return pos_x; }
	void setPosX(float x) { pos_x = x; }
	void setPosY(float y) { pos_y = y; }
	bool isActive() { return active; }
	bool isErased() { return erased; }
	void update() override;
	void draw() override;
	void init() override;
	~Sprite();
	Sprite(const class Game& mygame1, float x, float y, float time,float size,bool er);
};