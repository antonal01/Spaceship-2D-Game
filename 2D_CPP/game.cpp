#include "game.h"
#include "graphics.h"
#include "config.h"


void Game::spawnMissiles() {
	graphics::getMouseState(ms);
	if (delay->delay()) {
		delay->setSpeed(5.0f);
		if (ms.button_left_pressed) {
			Shots* tmp = new Shots(*this);
			missiles.push_back(tmp);
			delay->resetDelay();
		}
	}
}


void Game::checkMissiles() {

	if (!missiles.empty())
	{
		for (it = missiles.begin(); it != missiles.end();) {
			
			if (!(*it)->isActive()) {
				delete* it;
				it = missiles.erase(it);
			}
			else { 
				it++;
			}
		}
	}
}


void Game::checkSprites() {

	if (!sprites.empty())
	{
		for (itSprite = sprites.begin(); itSprite != sprites.end();) {

			if ((*itSprite)->isErased()) {
				delete* itSprite;
				itSprite = sprites.erase(itSprite);
			}
			else {
				itSprite++;
			}
		}
	}
}


void Game::spawnMeteorite()
{
	if (!meteorite) {
		meteorite = new Enemy(*this);
	}
	if(score>=15 && meteorite){
		meteorite->setSpeed(1.5f);
	}
	if (score >= 25 && meteorite) {
		meteorite->setSpeed(1.8f);
	}
	if (score >= 35 && meteorite) {
		meteorite->setSpeed(2.0f);
	}
	if (score >= 50 && meteorite) {
		meteorite->setSpeed(2.5f);
	}

}
void Game::checkMeteorite()
{
	if (meteorite && !meteorite->isActive()) {
		delete meteorite;
		meteorite = nullptr;
	}
}

bool Game::checkCollision()
{
	if (!player || !meteorite) {
		return false;
	}	


	Disk d1 = player->getCollisionHull();
	Disk d2 = meteorite->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		player->drainLife(0.1f);
		return true;
	}
	else {
		return false;
	}
}

void Game::checkCollisionSprite()
{
	if (player && meteorite) {

		Disk d1 = player->getCollisionHull();
		Disk d2 = meteorite->getCollisionHull();

		float dx = d1.cx - d2.cx;
		float dy = d1.cy - d2.cy;

		if (sqrt(dx * dx + dy * dy)  < 10+d1.radius + d2.radius) {
			graphics::playSound(std::string(ASSET_PATH) + "damaged.wav", 0.24, false);
			player->drawCollision();
		}
	}
}
void Game::checkMissileCollision()
{
	graphics::Brush br;
	if (meteorite && !missiles.empty()) {
		Disk d1 = meteorite->getCollisionHull();
		for (it = missiles.begin(); it != missiles.end();)
		{			
			Disk d2 = (*it)->getCollisionHull();
			float dx = d1.cx - d2.cx;
			float dy = d1.cy - d2.cy;
			if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
				graphics::playSound(std::string(ASSET_PATH) + "explos.wav", 0.49, false);
				score++;
				prev_x = d1.cx;
				prev_y = d1.cy;
				prev prev1;
				prev1.prevx = prev_x;
				prev1.prevy = prev_y;
				prev1.size = d1.radius;
				i++;
				map.insert(std::pair<int,prev>(i,prev1));
				time = 0;
				delete* it;
				it = missiles.erase(it);
				delete meteorite;
				meteorite = nullptr;
				
			}
			else {
				it++;
			}

		}
	}
}

void Game::drawMetCol()
{
	graphics::Brush br;
	if (time < 500 && meteorite) {
		br.outline_opacity = 0.0f;
		br.fill_opacity = 1.0f;
		br.texture = std::string(ASSET_PATH) + "Crystal_03.png";
		graphics::drawRect(prev_x, prev_y, 80, 70, br);
		time += 1.5f * graphics::getDeltaTime();
	}
	else {
		br.texture = "";
	}
}


float Game::getPlayerPosX() const
{
	if (player) {
		float x = player->getPosX();
		return x;
	}
	else { return 0; }
	
}

float Game::getPlayerPosY() const
{
	if (player) {
		float x = player->getPosY();
		return x;
	}
	else { return 0; }

}

void Game::update()
{
	if (status == STATUS_START) {
		updateStartScreen();
	}
	else if (status == STATUS_CONTROLS) {
		updateControlsScreen();
	}
	else if(status == STATUS_PLAYING){
		updateLevelScreen();
	}
	else {
		updateEndScreen();
	}
}

void Game::draw()
{
	if (status == STATUS_START) {
		drawStartScreen();
	}
	else if (status == STATUS_CONTROLS) {
		drawControlsScreen();
	}
	else if( status== STATUS_PLAYING) {
		drawLevelScreen();
	}
	else {
		drawEndScreen();
	}

}


void Game::init()
{
	//graphics::setFont(std::string(ASSET_PATH) + "MONSHTER.ttf");
	//graphics::playMusic(std::string(ASSET_PATH) +"hit1.wav",0.5,true,4000);

}

void Game::updateStartScreen()
{ 
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	if (getStartMusic()) {
		graphics::playMusic(std::string(ASSET_PATH) + "loading.wav",0.6, true);
		setStartMusic(false);
		
	}


	if (ms.button_left_pressed) {
		graphics::stopMusic();
		setStartMusic(true);

	}
	
	if (graphics::getKeyState(graphics::SCANCODE_Z)) {
		status = STATUS_CONTROLS;
	}
	

	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		delete start;
		start = nullptr;
		status = STATUS_PLAYING;
	}
	
	if (ms.button_left_pressed) {
		delete start;
		start = nullptr;
		status = STATUS_PLAYING;
	}
	int i = 0;
	if (!start) {
		start = new Enemy(*this, 280, 230 ,0.0f, 80);
	}
	

	if (start && !start->isActive()) {
		delete start;
		start = nullptr;
	}
	

	if (start) {
		start->update();
	}

}

void Game::updateLevelScreen()
{
	if (graphics::getGlobalTime() > 500 && !player_initialized) {
		graphics::playSound(std::string(ASSET_PATH) + "start-level.wav", 0.2, false);
		player = new Player(*this);
		player_initialized = true;

	}
	
	if (player) {
		player->update();
	}


	checkMeteorite();
	spawnMeteorite();
	


	if (meteorite) {
		meteorite->update();
	}


	checkMissiles();
	spawnMissiles();
	

	if (!missiles.empty())
	{
		for (it = missiles.begin(); it != missiles.end(); it++)
		{
			(*it)->update();
		}
	}	
	


	if (checkCollision()) {
		
		delete meteorite;
		meteorite = nullptr;
	}
	
	checkMissileCollision();

	checkSprites();
	pushSprites();

	if (!sprites.empty())
	{
		for (itSprite = sprites.begin(); itSprite != sprites.end(); itSprite++)
		{
			(*itSprite)->update();
		}
	}

	if (player && player->getRemainingLife() == 0) {
		oldscore = score;
		status = STATUS_END;
		graphics::stopMusic();
		delete player;
		player = nullptr;
		delete meteorite;
		meteorite = nullptr;
		player_initialized = false;
	}
}
void Game::updateControlsScreen() {

	if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE)) {
		status = STATUS_START;
	}
}

void Game::updateEndScreen() {
	graphics::getMouseState(ms);

	if (getEndMusic()) {
		graphics::playMusic(std::string(ASSET_PATH) + "meet-the-princess.wav", 0.5, true);
		setEndMusic(false);

	}


	if(((window2CanvasX(ms.cur_pos_x)>=380 && window2CanvasX(ms.cur_pos_x) <= 820) && (window2CanvasY(ms.cur_pos_y) >= 235 && window2CanvasY(ms.cur_pos_y) <= 325))&& ms.button_right_pressed){
		graphics::stopMusic();
		setEndMusic(true);
		score = 0;
		status = STATUS_PLAYING;
	}
	if (((window2CanvasX(ms.cur_pos_x) >= 380 && window2CanvasX(ms.cur_pos_x) <= 820) && (window2CanvasY(ms.cur_pos_y) >= 335 && window2CanvasY(ms.cur_pos_y) <= 425)) && ms.button_right_pressed) {
		graphics::stopMusic();
		setEndMusic(true);
		score = 0;
		status = STATUS_START;
	}
	//if (((window2CanvasX(ms.cur_pos_x) >= 380 && window2CanvasX(ms.cur_pos_x) <= 820) && (window2CanvasY(ms.cur_pos_y) >= 435 && window2CanvasY(ms.cur_pos_y) <= 525)) && ms.button_right_pressed) {
	//	graphics::stopMusic();
	//	setEndMusic(true);
	//}
	
}

void Game::drawControlsScreen() {
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + "howtoplay.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	br.texture = "";

	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 200);

	br.fill_color[0] = 0.971f;
	br.fill_color[1] = 0.0565f;
	br.fill_color[2] = 0.0899f;
	br.fill_secondary_color[0] = 0.679f;
	br.fill_secondary_color[1] = 0.432f + glow * 0.2f;
	br.fill_secondary_color[2] = 0.100f;
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.9f;
	br.gradient = true;
	br.gradient_dir_u = 0.0f;
	br.gradient_dir_v = 1.0f;
	graphics::setFont(std::string(ASSET_PATH) + "Dommage.ttf");
	char info[40];
	sprintf_s(info, "Controls");
	graphics::drawText(CANVAS_WIDTH / 2 - 310, CANVAS_HEIGHT / 2 - 200, 100, info, br);

	graphics::Brush br1;
	br1.outline_opacity = 0.0;
	br1.fill_color[0] = 0.749f;
	br1.fill_color[1] = 0.565f;
	br1.fill_color[2] = 0.0899f;
	char info1[40];
	sprintf_s(info1, "Press ");
	graphics::drawText(CANVAS_WIDTH - 400, CANVAS_HEIGHT / 2 - 150, 15, info1, br1);


	graphics::Brush br2;
	br2.outline_opacity = 0.0;
	br2.fill_color[0] = 0.0749f;
	br2.fill_color[1] = 0.2565f;
	br2.fill_color[2] = 0.399f;
	char info7[40];
	sprintf_s(info7, "Backspace");
	graphics::drawText(CANVAS_WIDTH  - 330, CANVAS_HEIGHT / 2 - 150,45, info7, br2);


	char info71[40];
	sprintf_s(info71, "to return to Menu");
	graphics::drawText(CANVAS_WIDTH -300, CANVAS_HEIGHT / 2 - 120, 25, info71, br1);

}

void Game::drawEndScreen()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + "imageedit_2_5725317488.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);


	br.texture = "";
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 200);

	br.fill_color[0] = 0.971f;
	br.fill_color[1] = 0.0565f;
	br.fill_color[2] = 0.0899f;
	br.fill_secondary_color[0] = 0.679f;
	br.fill_secondary_color[1] = 0.432f +glow* 0.2f;
	br.fill_secondary_color[2] = 0.100f;
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.9f;
	br.gradient = true;
	br.gradient_dir_u = 0.0f;
	br.gradient_dir_v = 1.0f; 
	graphics::setFont(std::string(ASSET_PATH) + "Dommage.ttf");
	char info[40];
	sprintf_s(info, "L  O  S  T");
	graphics::drawText(CANVAS_WIDTH / 2 - 220, CANVAS_HEIGHT / 2 - 150, 120, info, br);

	
	size123 +=  5* sinf(graphics::getGlobalTime() / 350.0f) / 5;
	br.gradient = false;
	char info5[40];
	sprintf_s(info5, "%6d", oldscore);
	graphics::setFont(std::string(ASSET_PATH) + "gtb.ttf");
	graphics::drawText(780, CANVAS_HEIGHT / 2 , size123+50, info5, br);

	glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 600);
	br.fill_color[0] = 0.921f;
	br.fill_color[1] = 0.390f + glow* 0.1f;
	br.fill_color[2] = 0.278f + glow * 0.1f;
	br.fill_secondary_color[0] = 0.460;
	br.fill_secondary_color[1] = 0.062f;
	br.fill_secondary_color[2] = 0.160f;
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.8f;
	br.gradient = true;

	
	char info1[40];
	sprintf_s(info1, "Play Again");
	graphics::drawText(CANVAS_WIDTH / 2 - 150, CANVAS_HEIGHT / 2 , 60, info1, br);

	char info2[40];
	sprintf_s(info2, "Main Menu");
	graphics::drawText(CANVAS_WIDTH / 2 - 155, CANVAS_HEIGHT / 2 +100, 60, info2, br);
	
	char info33[40];
	sprintf_s(info33, "Press Esc to ");
	graphics::drawText(430, CANVAS_HEIGHT / 2 + 200, 15, info33, br);

	char info3[40];
	sprintf_s(info3, "Exit");	
	graphics::drawText(CANVAS_WIDTH/2-70, CANVAS_HEIGHT / 2 + 200, 60, info3, br);

	//br.outline_opacity = 1.0f;								
	//graphics::drawRect(600, 280, 440, 90, br);  
													//check click position
	//graphics::drawRect(600, 380, 440, 90, br);	
	//graphics::drawRect(600, 480, 400, 90, br); 

	br.texture = std::string(ASSET_PATH) + "crosshair.png";
	graphics::getMouseState(ms);
	graphics::drawRect(window2CanvasX(ms.cur_pos_x), window2CanvasY(ms.cur_pos_y), 35, 35, br);

}

void Game::drawStartScreen()
{

	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + "269147.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	

	br.texture = "";
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 200);

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f + glow * 0.5f;
	br.fill_color[2] = 0.0f;
	br.fill_secondary_color[0] = 0.3f+ glow* 0.7f;
	br.fill_secondary_color[1] = 0.1f + glow * 0.6f;
	br.fill_secondary_color[2] = 0.7f;
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.5f;
	br.gradient = true;
	graphics::setFont(std::string(ASSET_PATH) + "Dommage.ttf");
	char info[40];
	sprintf_s(info, "S T A R T");
	graphics::drawText(CANVAS_WIDTH / 2 -200, CANVAS_HEIGHT / 2-200, 100, info, br);
	graphics::setFont(std::string(ASSET_PATH) + "Dommage.ttf");

	br.outline_opacity = 0.0f;
	br.fill_color[0] = 3.0f;
	br.fill_color[1] = 0.5f + glow * 0.5f;
	br.fill_color[2] = glow * 0.4f;
	br.fill_secondary_color[0] = 0.6f + glow * 0.4f;
	br.fill_secondary_color[1] = 0.1f + glow * 0.3f;
	br.fill_secondary_color[2] = 0.7f;
	br.texture = "";
	br.texture= std::string(ASSET_PATH) + "crosshair.png";
	
	graphics::getMouseState(ms); 
	graphics::drawRect(window2CanvasX(ms.cur_pos_x),window2CanvasY(ms.cur_pos_y), 35,35, br);


	char info7[40];
	sprintf_s(info7, "press");
	graphics::drawText(CANVAS_WIDTH / 2 - 250, CANVAS_HEIGHT - 100, 30, info7, br);


	char info71[40];
	sprintf_s(info71, "Z");
	graphics::drawText(CANVAS_WIDTH / 2 - 120, CANVAS_HEIGHT - 100, 50, info71, br);


	char info72[40];
	sprintf_s(info72, "to view controls");
	graphics::drawText(CANVAS_WIDTH / 2 - 70, CANVAS_HEIGHT - 100, 30, info72, br);

	if (start) {
		start->draw();
	}
}

void Game::drawLevelScreen()
{

	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "untitled1.png";
	br.outline_opacity = 0.0f;

	

	//draw bacground
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	//draw player
	if (player) {
		player->draw();
			
	}

	if (meteorite) {
		meteorite->draw();
	}

	drawMetCol();
	checkCollisionSprite();
	if (!missiles.empty())
	{
		for (it = missiles.begin(); it != missiles.end(); it++)
		{
			(*it)->draw();

		}
	}
		
	
	if (!sprites.empty())
	{
		for (itSprite = sprites.begin(); itSprite != sprites.end(); itSprite++)
		{
			(*itSprite)->draw();

		}
	}

	char info[40];
	sprintf_s(info, "SCORE :%6d", score);
	graphics::setFont(std::string(ASSET_PATH) + "AGOXES.otf");


	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	graphics::drawText(460, 50,40, info, br);
	br.fill_color[0] = 0.442f;
	br.fill_color[1] = 0.445f;
	br.fill_color[2] = 0.0f;
	graphics::drawText(460, 50, 40, info, br);


	
	//UI/info layer
	if (player && debug_mode) {
		graphics::setFont(std::string(ASSET_PATH) + "MONSHTER.ttf");
		char info[40];
		sprintf_s(info, "(%6.2f,%6.2f)", player->getPosX(), player->getPosY());
		graphics::drawText(30, 30, 15, info, br);

	}

	float player_life = player ? player->getRemainingLife() : 0.0f;
	br.texture = "";
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 0.8450f;
	br.fill_color[1] = 0.6523f;
	br.fill_color[2] = 0.0f;
	br.fill_secondary_color[0] = 1.0f * (1.0f - player_life) + player_life * 0.2f;
	br.fill_secondary_color[1] =  0.2f * (1.0f - player_life) + player_life * 1.0f;
	br.fill_secondary_color[2] = 0.2f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect( 100 - ((1.0f - player_life) * 120 / 2), 35, player_life * 120, 20, br);

	br.outline_opacity = 1.0f;
	br.gradient = false;
	br.fill_opacity = 0.0f;
	graphics::drawRect( 100, 35, 120, 20, br);
	
	graphics::Brush br1;
	br1.outline_opacity = 0.0f;
	br1.texture = std::string(ASSET_PATH) + "crosshair.png";
	br1.fill_color[0] = 0.050f;
	br1.fill_color[1] = 0.632f;
	br1.fill_color[2] = 0.775f;
	br1.fill_opacity = 1.0f;
	

	graphics::getMouseState(ms);
	graphics::drawRect(window2CanvasX(ms.cur_pos_x), window2CanvasY(ms.cur_pos_y), 35, 35, br1);

}

void Game::pushSprites()
{
	graphics::Brush br;
	br.outline_opacity = 1.0f;
	Delay* del1 = new Delay();
	if(!map.empty()){
		for (it1 = map.begin(); it1 != map.end();) {
			prev asd;
			asd = it1->second;
			Sprite* tmp = new Sprite(*this,asd.prevx,asd.prevy,0,asd.size,false);
			sprites.push_back(tmp);
			it1 = map.erase(it1);			
		}

	}
}

float Game::window2CanvasX(float x)
{

	return  x*   CANVAS_WIDTH/ (float)window_width;
}

float Game::window2CanvasY(float y)
{
	return  y *  CANVAS_HEIGHT/(float) window_height;
}




Game::Game()
{
}

Game::~Game()
{
	if (player) {
		delete player;
	}
	
}
