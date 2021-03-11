#include "enemy.h"
#include "graphics.h"
#include "config.h"
#include "util.h" 
#include <random>
#include "game.h"

void Enemy::update()
{	
	if (dir == UP) {
		pos_y += speed * graphics::getDeltaTime();
	}
	if (dir == DOWN) {
		pos_y -= speed * graphics::getDeltaTime();
	}
	if (dir == LEFT) {
		pos_x += speed * graphics::getDeltaTime();
	}
	if (dir == RIGHT) {
		pos_x -= speed * graphics::getDeltaTime();
	}

	check();
	rotation += 0.05f * graphics::getDeltaTime();
	rotation = fmodf(rotation, 360);
	angle++;
}

void Enemy::draw()
{
	brush.outline_opacity = 0.0f;
	graphics::setOrientation(rotation);
	brush.texture = std::string(ASSET_PATH) + "Meteor_03.png";
	brush.fill_opacity = 0.5f;
	graphics::drawRect(pos_x - 10, pos_y + 30, size, size,brush);
	brush.texture = std::string(ASSET_PATH) + "Meteor_01.png";

	brush.fill_opacity =1.0f;
	graphics::drawRect(pos_x, pos_y, size, size,brush);
	graphics::resetPose();

	if (game1.getDebugMode()) {

		graphics::Brush brr;
		brr.outline_opacity = 1.0f;
		brr.texture = "";
		brr.fill_color[0] =1.0f;
		brr.fill_color[1] = 0.370f;
		brr.fill_color[2] = 0.3f;
		brr.fill_opacity = 0.43f;
		brr.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, brr);

	}
}


void Enemy::init()
{
	speed = 0.8f;

	if (dir == RIGHT) {
		pos_x = CANVAS_WIDTH + 1.1f * size;
		pos_y = CANVAS_HEIGHT * rand0to1();
	}
	if (dir == LEFT) {
		pos_x = -CANVAS_WIDTH - 1.1f * size;
		pos_y = CANVAS_HEIGHT * rand0to1();
	}
	if (dir == DOWN) {
		pos_x = CANVAS_WIDTH * rand0to1();
		pos_y = CANVAS_HEIGHT + 1.1f * size;
	}
	if (dir == UP) {
		pos_x = CANVAS_WIDTH * rand0to1();
		pos_y = -CANVAS_HEIGHT - 1.1f * size;
	}
	size= 50 + 100 * rand0to1();
	rotation = 360 * rand0to1();
	brush.outline_opacity = 0.0f;
}

void Enemy::check()
{
	if ((pos_x < -size || pos_y < -size)&& dir==RIGHT)
	{
		active = false;
	}
	if ((pos_x > CANVAS_WIDTH+size || pos_y < -size) && dir== LEFT)
	{
		active = false;
	}
	if ((pos_y < -size) && dir == DOWN)
	{
		active = false;
	}
	if (( pos_y > CANVAS_HEIGHT + size) && dir== UP)
	{
		active = false;
	}
}

Disk Enemy::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.time = 0;
	disk.radius =(size * 7/10);
	return disk;
}

Enemy::Enemy(const Game& mygame1) : GameObject(mygame1)
{
	init();
}

Enemy::Enemy(const Game& mygame1, float x, float y, float speed, float size) : GameObject(mygame1)
{
	pos_x = x;
	pos_y = y;
	this->speed = speed;
	this->size = size;

}


Enemy::~Enemy()
{
}

