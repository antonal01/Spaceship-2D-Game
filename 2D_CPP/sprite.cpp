#include "sprite.h"
#include "config.h"
Disk Sprite::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.time = 0;
	disk.radius = (size * 7 / 10);
	return disk;
}

Sprite::Sprite(const Game& mygame1) : GameObject(mygame1)
{
	init();
}

void Sprite::update()
{
	
		time += 0.5f * graphics::getDeltaTime();
		if (time > 200 && time < 700) {
			if (!initialized) {
				graphics::playSound(std::string(ASSET_PATH) + "ret4.wav", 0.0324, false);
				initialized = true;
			}
			pos_y += 0.1812f * graphics::getDeltaTime();
		}
		if (time >= 700 && time < 1100) {
			if (!initialized1) {
				graphics::playSound(std::string(ASSET_PATH) + "exp3.wav", 0.0413, false);
				initialized1 = true;
			}
			size += 0.1f * graphics::getDeltaTime();
		}
}

void Sprite::draw()
{
	brush.outline_opacity = 0.0f;
	if (time>200 &&time < 700) {

		graphics::setOrientation(90.0f);
		brush.texture = std::string(ASSET_PATH) + "crystal_02.png";
		graphics::drawRect(pos_x, pos_y, size, size/2, brush);
		graphics::resetPose();
	}
	if (time >= 700 && time <1100) {
		brush.texture = std::string(ASSET_PATH) + "crystal_01.png";
		graphics::drawRect(pos_x, pos_y, size, size / 2, brush);
	}

	if(time >=1100) {
		erased = true;
	}
}

void Sprite::init()
{	
	 pos_x = 0.0f, pos_y = 0.0f;
	 size = 200.0f;
	 time = 0.0f;
	 erased = false;
}

Sprite::~Sprite()
{
}

Sprite::Sprite(const Game& mygame1, float x, float y, float time, float size,bool er) : GameObject(mygame1)
{

	erased = er;
	pos_x = x;
	pos_y = y;
	this->time = time;
	this->size = size;
}
