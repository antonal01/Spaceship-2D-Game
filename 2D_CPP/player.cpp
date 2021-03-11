#include "player.h"
#include "game.h"
#include <math.h>
#include "util.h"
#include <iostream>

Player::Player(const Game& mygame1) : GameObject(mygame1)
{
}



void Player::update() {

	if (!initializedMusic) {
		//graphics::playMusic(std::string(ASSET_PATH) + "spaceship.wav", 0.7, true);
		initializedMusic = true;
	}



	graphics::getMouseState(ms);
	delta_y = getPosY() - (float)ms.cur_pos_y;
	delta_x = getPosX() - (float)ms.cur_pos_x;
	angle = (atan2(delta_x, delta_y) * (float)180 / (float)PI);



	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		pos_x -= speed * graphics::getDeltaTime()/10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D)) {
		pos_x += speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_W)) {
		pos_y -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_S)) {
		pos_y += speed * graphics::getDeltaTime() / 10.0f;
	}

	if (pos_x<0) {	pos_x =0;}
	if (pos_x > CANVAS_WIDTH) { pos_x = CANVAS_WIDTH; }
	if (pos_y < 0) { pos_y = 0; }
	if (pos_y > CANVAS_HEIGHT) { pos_y = CANVAS_HEIGHT; }
	

}

void Player::draw() {

	graphics::getMouseState(ms);

	float offset = 10 * sinf(graphics::getGlobalTime()/1000.0f)/5;
	float glow = 0.5f+ 0.25f * sinf(graphics::getGlobalTime()/100);

	graphics::Brush br,br1;
	br.outline_opacity = 0;
	br1.outline_opacity = 0;

	
	graphics::setScale(height, height);


	br1.fill_opacity = std::max<float>(0.3, opac-0.4);
	br1.fill_color[0] = 0.292f;
	br1.fill_color[1] = 0.296f;
	br1.fill_color[2] = 0.325f;
	br1.texture = std::string(ASSET_PATH) + "spaces1.png"; //skia
	graphics::setOrientation(angle);
	graphics::drawRect(pos_x-10*height, offset+pos_y+5*height*3, 60,100, br1);
	graphics::resetPose();
	br.fill_opacity = opac;
	br.texture = std::string(ASSET_PATH) + "spaces1.png";
	graphics::setOrientation(angle);
	if (opac < 0.3) {
		if (!oldengineMusic) {
			graphics::playMusic(std::string(ASSET_PATH) + "oldengine.wav", 0.5, true);
			oldengineMusic = true;
		}
		br.fill_color[0] = 0.6 + glow * 0.2;
		br.fill_color[1] = 0.6 + glow * 0.3;
		br.fill_color[2] = 0.1f;
		br.fill_secondary_color[0] = life-0.4f + glow * (0.4f);
		br.fill_secondary_color[1] = life-0.4f + glow * (0.4f);
		br.fill_secondary_color[2] = life -0.4f+ glow * 0.4f;
		br.fill_secondary_opacity = 0.6f;
		br.gradient = true;
	}
	graphics::drawRect(pos_x, pos_y+ offset, 60, 100, br);
	graphics::resetPose();


	br.texture = "";
	br1.texture = "";
	br.fill_opacity = opac -1;
	br.fill_color[0] = 0.6;
	br.fill_color[1] = 0.3 + (float)glow * 0.65;
	br.fill_color[2] = 0.1f;
	br.fill_secondary_color[0] = life + glow * (0.2f);
	br.fill_secondary_color[1] = life + glow * (0.2f);
	br.fill_secondary_color[2] = life + glow * 0.2f;
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true;
	br.outline_opacity = 0;
	graphics::setScale(height, height);
	graphics::drawDisk(pos_x,pos_y+5, 10,br);
	graphics::resetPose();

	
	if (game1.getDebugMode()){
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 0.4f;
		br.fill_color[1] = 0.70f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.43f;
		br.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);

	}
	
}

void Player::init(){
}



void Player::drawCollision()
{
	
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.0f;
	br.texture = std::string(ASSET_PATH) + "Bomb_light.png";
	graphics::drawRect(getPosX() , getPosY() , 300, 100, br);
}

Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 55.0f;
	return disk;
}

