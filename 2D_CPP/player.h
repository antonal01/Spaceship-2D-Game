#pragma once
#include "GameObject.h"
#include "config.h"
#include "graphics.h"

class Player :public GameObject, public Collidable {
	Delay* delay2 = new Delay();
	float speed = 4.0f;
	float pos_x= CANVAS_WIDTH/2, pos_y=CANVAS_HEIGHT/2;
	float height = 1.0;
	float life = 1.0f;
	float rotation = 1.0f;
	float angle = 0; 
	float opac = 1.0f;
	float delta_y = 0, delta_x = 0;
	graphics::MouseState ms;
	Delay* del1 = new Delay();
	float x = -200;
	float y = -200;
	bool oldengineMusic = false;
	bool initializedMusic = false;
	bool initializedMusic1 = false;
	float time = 0;
public:
	
	 Player(const class Game& mygame1);
	 void update() override;
	 void draw() override;
	 void init() override;
	 void drawCollision();
	 const float getPosY() { return pos_y; }
	 const float getPosX() { return pos_x; }
	 Disk getCollisionHull() const override;
	 float getRemainingLife() const { return life; }
	 void resetLife() { life = 1.0f;	opac = 1.0f; }
	 void drainLife(float amount) {
		 life = std::max<float>(0.0f, life - amount);
		 opac = std::max<float>(0.0f, opac - amount);
	 }
};