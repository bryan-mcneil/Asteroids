#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "bullet.h"
#include "rocks.h"
#include "ship.h"

#define CLOSE_ENOUGH 15


/*****************************************
* GAME
* The main game class containing all the state
*****************************************/
class Game
{
public:
	/*********************************************
	* Constructor
	* Initializes the game
	*********************************************/
	Game(Point tl, Point br);
	~Game();

	/*********************************************
	* Function: handleInput
	* Description: Takes actions according to whatever
	*  keys the user has pressed.
	*********************************************/
	void handleInput(const Interface & ui);

	/*********************************************
	* Function: advance
	* Description: Move everything forward one
	*  step in time.
	*********************************************/
	void advance();

	/*********************************************
	* Function: draw
	* Description: draws everything for the game.
	*********************************************/
	void draw(const Interface & ui);

private:
	// The coordinates of the screen
	Point topLeft;
	Point bottomRight;

	Ship ship; 
	std::vector<Bullet> bullets;
	std::list<Rock*> rocks;
	int timer;
	int levelCount;
	int rockCount;
	int newRocks;
	bool makeRocks;
	bool firstStart;
	bool death;
	int deathTime;
	float dotEffect;

	/*************************************************
	* Private methods to help with the game logic.
	*************************************************/
	void createRocks(std::list<Rock*> & rocks);
	bool isOnScreen(const Point & point);
	void advanceBullets();
	void advanceRocks();
	void handleCollisions();
	void shipCollision();
	void cleanUpZombies();
	void wrapShip();
	void wrapBullet();
	void level();
};

#endif /* GAME_H */
