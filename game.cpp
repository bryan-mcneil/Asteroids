/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"
#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "rocks.h"
#include <vector>
#include <list>

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>

#define OFF_SCREEN_BORDER_AMOUNT 5

/******************************************************************************
* GAME CONSTRUCTOR
******************************************************************************/
Game::Game(Point tl, Point br)
	: topLeft(tl), bottomRight(br)
{
	timer = 0;
	levelCount = 1;
	rockCount = 0;
	newRocks = 3;
	makeRocks = true;
	firstStart = true;
	death = false;
	deathTime = 0;
	dotEffect = 0.0;

	ship.setPoint(Point(0, 0));
}

/*******************************************************************************
* GAME DESTRUCTOR
*******************************************************************************/
Game :: ~Game()
{
	std::list<Rock*> ::iterator it = rocks.begin();

	while (it != rocks.end())
	{
		Rock* pRock = *it;
		delete pRock;
		pRock = NULL;
		it = rocks.erase(it);
	}
}

/******************************************************************************
* GAME :: ADVANCE
* advance the game one unit of time
******************************************************************************/
void Game::advance()
{
	if (ship.isAlive())
	{
		ship.advance();
	}
	wrapShip();
	wrapBullet();
    advanceRocks();
	advanceBullets();
	handleCollisions();
	shipCollision();
	cleanUpZombies();
	createRocks(rocks);
	level();
	timer++;

	if (rockCount < 0)
	{
		rockCount = 1;
	}

}

/******************************************************************************
* GAME :: ADVANCE BULLETS
* Go through each bullet and advance it.
******************************************************************************/
void Game::advanceBullets()
{
	// Move each of the bullets forward if it is alive
	for (size_t i = 0; i < bullets.size(); i++)
	{	
		if (bullets[i].isAlive())
		{
			// this bullet is alive, so tell it to move forward
			bullets[i].advance();
			bullets[i].time();
		}

	}
}

/******************************************************************************
* GAME :: ADVANCE ROCKS
* Move Pointers of Rock and wrap
******************************************************************************/
void Game::advanceRocks()
{
	std::list<Rock*> :: iterator it = rocks.begin();

	

	while (it != rocks.end())
	{
		Point p = (*it)->getPoint();
		if (!isOnScreen((*it)->getPoint()))
		{
			if ((int)(*it)->getPoint().getX() <= (int)topLeft.getX())
				(*it)->setPoint(Point(p.getX() * -1 - 1, p.getY()));

			else if ((int)(*it)->getPoint().getY() >= (int)topLeft.getY())
				(*it)->setPoint(Point(p.getX(), p.getY() * -1 + 1));

			else if ((int)(*it)->getPoint().getX() >= (int)bottomRight.getX())
				(*it)->setPoint(Point(p.getX() * -1 + 1, p.getY()));

			else if ((int)(*it)->getPoint().getY() <= (int)bottomRight.getY())
				(*it)->setPoint(Point(p.getX(), p.getY() * -1 - 1));

			else
				(*it)->setPoint(Point(p.getX() * -1, p.getY() * -1));

		}
		(*it)->advance();
		it++;
	}
}

/******************************************************************************
* GAME :: CREATES ROCKS
* Creates a list of rocks
******************************************************************************/
void Game::createRocks(std::list<Rock*> & rocks)
{
	if (timer >= 60 && makeRocks == true)
	{
		for (int i = 0; i < newRocks; i++)
		{
			int rand = random(1, 11);

			if (rand <= 5)
			{
				++rockCount;
				SmallRock *small = new SmallRock;
				small->setPoint(Point((float)random(topLeft.getX(), bottomRight.getX()), (float)random(topLeft.getY(), bottomRight.getY())));
				rocks.push_back(small);
			}
			else if (rand > 5 && rand <= 8)
			{
				++rockCount;
				MedRock *med = new MedRock;
				med->setPoint(Point((float)random(topLeft.getX(), bottomRight.getX()), (float)random(topLeft.getY(), bottomRight.getY())));
				rocks.push_back(med);
			}
			else
			{ 
				++rockCount;
				BigRock *big = new BigRock;
				big->setPoint(Point((float)random(topLeft.getX(), bottomRight.getX()), (float)random(topLeft.getY(), bottomRight.getY())));
				rocks.push_back(big);
			}
		}
		makeRocks = false;
		timer = 65;
	}
}

/**************************************************************************
* GAME :: IS ON SCREEN
* Determines if a given point is on the screen.
**************************************************************************/
bool Game::isOnScreen(const Point & point)
{
	return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
* GAME :: HANDLE COLLISIONS
**************************************************************************/
void Game::handleCollisions()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		for (std::list<Rock*>::iterator it = rocks.begin(); it != rocks.end(); ++it)
		{
			if (bullets[i].isAlive())
			{
				if (fabs(bullets[i].getPoint().getX() - (*it)->getPoint().getX()) < CLOSE_ENOUGH
					&& fabs(bullets[i].getPoint().getY() - (*it)->getPoint().getY()) < CLOSE_ENOUGH)
				{
					(*it)->kill();
					bullets[i].kill();
					rockCount--;

					if ((*it)->getSize() == 1)
					{
						rockCount += 3;
						rocks.push_back(new MedRock((*it)->getPoint().getX(), (*it)->getPoint().getY() + 1, (*it)->getVelocity().getDx(), (*it)->getVelocity().getDy() + 0.5));
						rocks.push_back(new MedRock((*it)->getPoint().getX(), (*it)->getPoint().getY() - 1, (*it)->getVelocity().getDx(), (*it)->getVelocity().getDy() - 0.5));
						rocks.push_back(new SmallRock((*it)->getPoint().getX(), (*it)->getPoint().getY(), (*it)->getVelocity().getDx() + 1, (*it)->getVelocity().getDy()));
					}
					else if ((*it)->getSize() == 2)
					{
						rockCount += 2;
						rocks.push_back(new SmallRock((*it)->getPoint().getX() + 1, (*it)->getPoint().getY() + 1, (*it)->getVelocity().getDx() + 1, (*it)->getVelocity().getDy()));
						rocks.push_back(new SmallRock((*it)->getPoint().getX() - 1, (*it)->getPoint().getY() - 1, (*it)->getVelocity().getDx() - 1, (*it)->getVelocity().getDy()));
					}
				}
			}
		}
	} 

}

/**************************************************************************
* GAME :: Ship collision with asteroids
**************************************************************************/
void Game::shipCollision()
{
	for (std::list<Rock*>::iterator it = rocks.begin(); it != rocks.end(); ++it)
	{
		if (fabs(ship.getPoint().getX() - (*it)->getPoint().getX()) < CLOSE_ENOUGH
			&& fabs(ship.getPoint().getY() - (*it)->getPoint().getY()) < CLOSE_ENOUGH)
		{
			ship.kill();
		}
	}
}

/**************************************************************************
* GAME :: CLEAN UP ZOMBIES
* Remove any dead objects (take bullets out of the list, deallocate bird)
**************************************************************************/
void Game::cleanUpZombies()
{
	std::list<Rock*>::iterator it = rocks.begin();
	while (it != rocks.end())
	{
		Rock* rock = *it;

		if (!(*it)->isAlive())
		{
			delete rock;
			rock = NULL;
			it = rocks.erase(it);
		}
		else
		{
			it++;
		}
	}

	// Look for dead bullets
	std::vector<Bullet>::iterator bulletIt = bullets.begin();
	while (bulletIt != bullets.end())
	{
		Bullet bullet = *bulletIt;

		if (!bullet.isAlive())
		{
			// remove from list and advance
			bulletIt = bullets.erase(bulletIt);
		}
		else
		{
			bulletIt++; // advance
		}
	}
	
}

/***************************************************************************************
* GAME :: WRAPSHIP
* wraps ship with screen
***************************************************************************************/
void Game::wrapShip()
{
	if (!isOnScreen(ship.getPoint()))
	{
		if ((int)ship.getPoint().getX() <= (int)topLeft.getX())
		{
			ship.setPoint(Point((ship.getPoint().getX() * -1 - 5), (ship.getPoint().getY())));
		}
		else if ((int)ship.getPoint().getY() >= (int)topLeft.getY())
		{
			ship.setPoint(Point((ship.getPoint().getX()), (ship.getPoint().getY() * -1 + 5)));
		}
		else if ((int)ship.getPoint().getX() >= (int)bottomRight.getX())
		{
			ship.setPoint(Point((ship.getPoint().getX() * -1 + 5), (ship.getPoint().getY())));
		}
		else if ((int)ship.getPoint().getY() <= (int)bottomRight.getY())
		{
			ship.setPoint(Point((ship.getPoint().getX()), (ship.getPoint().getY() * -1 - 5)));
		}
		else
		{
			ship.setPoint(Point((ship.getPoint().getX() * -1), (ship.getPoint().getY() * -1)));
		}
	}

		return;
}

/***************************************************************************************
* GAME :: WRAPBULLET
* wraps bullets with screen
***************************************************************************************/
void Game::wrapBullet()
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		if (!isOnScreen(bullets[i].getPoint()))
		{
			if ((int)bullets[i].getPoint().getX() <= (int)topLeft.getX())
			{
				bullets[i].setPoint(Point((bullets[i].getPoint().getX() * -1 - 5), (bullets[i].getPoint().getY())));
			}
			else if ((int)bullets[i].getPoint().getY() >= (int)topLeft.getY())
			{
				bullets[i].setPoint(Point((bullets[i].getPoint().getX()), (bullets[i].getPoint().getY() * -1 + 5)));
			}
			else if ((int)bullets[i].getPoint().getX() >= (int)bottomRight.getX())
			{
				bullets[i].setPoint(Point((bullets[i].getPoint().getX() * -1 + 5), (bullets[i].getPoint().getY())));
			}
			else if ((int)bullets[i].getPoint().getY() <= (int)bottomRight.getY())
			{
				bullets[i].setPoint(Point((bullets[i].getPoint().getX()), (bullets[i].getPoint().getY() * -1 - 5)));
			}
			else
			{
				bullets[i].setPoint(Point((bullets[i].getPoint().getX() * -1), (bullets[i].getPoint().getY() * -1)));
			}
		}
	}
}

/******************************************************************************
* GAME :: level
******************************************************************************/
void Game::level()
{
	if (timer >= 65)
	{
		if (rockCount <= 0)
		{
			levelCount++;
			newRocks = levelCount + 5;
			makeRocks = true;
			timer = -30;
			firstStart = false;
		}
	}
}

/******************************************************************************
* GAME :: HANDLE INPUT
* accept input from the user
******************************************************************************/
void Game::handleInput(const Interface & ui)
{
	if (ui.isUp())
	{
		ship.applyThurst();
	}
	else
	{
		ship.motion();
	}
	if (ui.isLeft())
	{
		ship.addSpin(6);
	}

	if (ui.isRight())
	{
		ship.addSpin(-6);
	}

	// Check for "Spacebar
	if (ui.isSpace())
	{
		if (ship.isAlive())
		{
			Bullet newBullet;
			newBullet.setPoint(ship.getPoint());
			newBullet.fire(ship.getPoint(), ship.getAngle(), ship.getVelocity().getDx(), ship.getVelocity().getDy());
			bullets.push_back(newBullet);
		}
	}
}

/************************************************************************************
* GAME :: DRAW
* Draw everything on the screen
************************************************************************************/
void Game::draw(const Interface & ui)
{
	if (ship.isAlive())
	{
		ship.draw();
	}
	else
	{
		if (!death)
		{
			for (int i = 0; i < 10; i++)
			{
				drawDot(Point(ship.getPoint().getX() + 0.1 + dotEffect, ship.getPoint().getY() + 0.1 + dotEffect));
				drawDot(Point(ship.getPoint().getX() - 0.1 - dotEffect, ship.getPoint().getY() - 0.1 - dotEffect));
				drawDot(Point(ship.getPoint().getX() + 0.1 + dotEffect, ship.getPoint().getY() - 0.1 - dotEffect));
				drawDot(Point(ship.getPoint().getX() - 0.1 - dotEffect, ship.getPoint().getY() + 0.1 + dotEffect));
				drawDot(Point(ship.getPoint().getX() + 15 + dotEffect, ship.getPoint().getY()));
				drawDot(Point(ship.getPoint().getX() - 10 - dotEffect, ship.getPoint().getY()));
				drawDot(Point(ship.getPoint().getX() + 1 + dotEffect, ship.getPoint().getY() - 0.1 - dotEffect));
				drawDot(Point(ship.getPoint().getX(), ship.getPoint().getY() + 0.4 + dotEffect));
				drawDot(Point(ship.getPoint().getX(), ship.getPoint().getY() + 3 + dotEffect));
				drawDot(Point(ship.getPoint().getX() - 0.6 - dotEffect, ship.getPoint().getY() - 2.1 - dotEffect));
				drawDot(Point(ship.getPoint().getX(), ship.getPoint().getY() - 9 - dotEffect));
				drawDot(Point(ship.getPoint().getX() - 0.7 - dotEffect, ship.getPoint().getY() + 3 + dotEffect));
				dotEffect += 0.1;
			}
			deathTime++;
			if (deathTime > 45)
			{
				death = true;
			}
		}
	}

	std::list<Rock*> ::iterator it = rocks.begin();

	while (it != rocks.end())
	{
		(*it)->draw();
		it++;
	}

    // draw the bullets, if they are alive
	for (size_t i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].draw();
		}
	}

	if (rockCount <= 0  && firstStart == false)
	{
		drawText(Point(0, 0), "Level Cleared");
	}
	//Put the score on the screen
	Point scoreLocation;
	scoreLocation.setX(topLeft.getX() + 40);
	scoreLocation.setY(topLeft.getY() - 5);

	drawText(Point(topLeft.getX() + 5, topLeft.getY() - 15), "Level:");
	drawNumber(scoreLocation, levelCount);

}

