#pragma once
#include "GameObject.h"
#include "graphics.h"
#include "config.h"

class Enemy :public GameObject,public Collidable/*,public Collidable*/ {

	typedef enum { UP, DOWN, LEFT, RIGHT } direction;
	float pos_x = CANVAS_WIDTH + 1.1f * size, pos_y= CANVAS_HEIGHT * rand0to1();
	float speed= 0.3f;
	float size= 50 + 100 * rand0to1();
	float rotation = 360 * rand0to1();
	graphics::Brush brush;	
	bool active = true;
	float angle = 0;
	direction dir = static_cast<direction>(rand() % 4);
public:
	Disk getCollisionHull() const override;
	Enemy(const class Game & mygame1);
	Enemy(const class Game& mygame1, float x, float y, float speed, float size);
	float getPos_X() { return pos_x; }
	float getPos_Y() { return pos_y; }
	void set_Y(float y) { pos_y = y; }
	void set_X(float y) { pos_x = y; }
	void update() override;
	void draw() override;
	void setSpeed(float x) { speed = x; }
	void init() override;
	void check();
	bool isActive() { return active; }
	~Enemy();
};