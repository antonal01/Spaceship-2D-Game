#pragma once
#include "GameObject.h"
#include "graphics.h"


class Shots :public GameObject, public Collidable/*,public Collidable*/ {
	float pos_x = 1.0f, pos_y = 1.0f;
	float speed = 1.0f;
	float size = 1.0f;
	graphics::Brush brush;
	float angle = 0;
	bool active = false;
	bool erased = false;
	graphics::MouseState ms1;
	float delta_y = 0;
	float delta_x = 0; 
	bool missileSound = false;
public:
	Disk getCollisionHull() const override;
	Shots(const class Game& mygame1);
	const float  getPosY() { return pos_y; }
	const float  getPosX() { return pos_x; }
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	bool isErased() { return erased; }
	void setActive(bool d) { active = d; }
	~Shots();
};