#include "shots.h"
#include "config.h"
#include "game.h"
#include "util.h" 

Disk Shots::getCollisionHull() const
{
    Disk d1;
    d1.cx = pos_x;
    d1.cy = pos_y;
    d1.radius = (size * 7 / 10);
    return  d1;
}

Shots::Shots(const Game& mygame1):GameObject(mygame1)
{
    init();
}

void Shots::update()
{

    if (!active) {
        pos_x = game1.getPlayerPosX() + 20;//CANVAS_WIDTH * rand0to1();
        pos_y = game1.getPlayerPosY() + 50;//CANVAS_HEIGHT + 1.1f * size;
        active = true;
        graphics::getMouseState(ms1);
        delta_y = getPosY() - (float)ms1.cur_pos_y;
        delta_x = getPosX() - (float)ms1.cur_pos_x;
        angle = (atan2(delta_x, delta_y) * (float)180 / (float)PI);
    }

   
    pos_x -= speed * ((float)sin(angle *(float) PI /(float) 180)) * graphics::getDeltaTime();
    pos_y -= speed * ((float)cos(angle *(float) PI /(float) 180)) * graphics::getDeltaTime();
    if (pos_y < -200)
    {
        active = false;
        erased = true;
    }
}

void Shots::draw()
{   
    graphics::setOrientation(angle);
    brush.texture = std::string(ASSET_PATH) + "missile.png";
    if (isActive()) {
        brush.fill_opacity = 1.0f;
    }
    else {
        brush.fill_opacity = 0.0f;
    }
    brush.outline_opacity = 0.0f;

    graphics::drawRect(pos_x, pos_y, size, 2 * size, brush);


	graphics::resetPose();
    if (game1.getDebugMode()) {

        graphics::Brush brr;
        brr.outline_opacity = 1.0f;
        brr.texture = "";
        brr.fill_color[0] = 1.0f;
        brr.fill_color[1] = 0.370f;
        brr.fill_color[2] = 0.3f;
        brr.fill_opacity = 0.43f;
        brr.gradient = false;
        Disk hull = getCollisionHull();
        graphics::drawDisk(hull.cx, hull.cy, hull.radius, brr);

    }
}

void Shots::init()
{
    graphics::playSound(std::string(ASSET_PATH) + "mis2.wav", 0.2, false);
    speed = 2.3f;
    pos_x = game1.getPlayerPosX();//CANVAS_WIDTH * rand0to1();
    pos_y = game1.getPlayerPosY();//CANVAS_HEIGHT + 1.1f * size;
    size = 40 ;
    brush.outline_opacity = 0.0f; 
}


Shots::~Shots()
{
}
