#pragma once
#include "player.h"
#include "sprite.h"
#include "enemy.h"
#include "shots.h"
#include <iterator>
#include <vector>
#include <map>
#include "util.h"

class Game{
	float prev_x=-200, prev_y=-200;
	int i = 0, score = 0, oldscore = 0;
	bool player_initialized = false, debug_mode = false, hi = true, ready = true, refreshed = false, startmusic = true, endmusic = true;
	float time = 0.0f, time1 = 0.0f, size123 = 0;
	typedef enum {STATUS_START, STATUS_PLAYING, STATUS_END,STATUS_CONTROLS} status_t;
	Player * player = nullptr;	
	Delay *delay= new Delay();
	Delay* delayy = new Delay();
	Shots* missile = nullptr;
	Enemy* meteorite = nullptr;
	Enemy* start = nullptr;
	std::vector<Sprite*> sprites;
	std::vector<Sprite*>::iterator itSprite;
	std::vector<Shots*> missiles;
	std::vector<Shots*>::iterator it;
	std::map<int, prev> map;
	std::map<int, prev>::iterator it1;
	void spawnMeteorite();
	void checkMeteorite();
	void spawnMissiles();
	void checkMissiles();
	void checkSprites();
	bool checkCollision();
	void checkCollisionSprite();
	void checkMissileCollision();
	void drawMetCol();
	status_t status = STATUS_START;
	graphics::MouseState ms;
	unsigned int window_width = WINDOW_WIDTH, window_height = WINDOW_HEIGHT;
public:
	bool getStartMusic() { return startmusic; }
	void setStartMusic(bool x) { startmusic = x; }
	bool getEndMusic() { return endmusic; }
	void setEndMusic(bool x) { endmusic = x; }
	float getPlayerPosX() const;
	float getPlayerPosY() const;
	void setDebugMode(bool d) { debug_mode = d;}
	bool getDebugMode() const { return debug_mode; }
	bool getPlayerInitialized() const{ return player_initialized; }
	void update();
	void draw() ;
	void init() ;
	void updateControlsScreen();
	void drawControlsScreen();
	void updateStartScreen();
	void updateLevelScreen();
	void updateEndScreen();
	void drawStartScreen();
	void drawLevelScreen();
	void drawEndScreen();
	void pushSprites();
	unsigned int getWindowWidth() { return window_width; }
	unsigned int getWindowHeight() { return window_height; }
	float window2CanvasX(float x);
	float window2CanvasY(float y);
	void setWindowDimensions(unsigned int w, unsigned int h) { window_width = w; window_height = h; }
	Game();
	~Game();
};