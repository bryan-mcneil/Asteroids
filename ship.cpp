#include "ship.h"

/*********************************************************************
* Default Constructor
**********************************************************************/
Ship::Ship()
{
	alive = true;
	spin = 0;
	angle = 90;
}

/*********************************************************************
* Adds velocity to ship
**********************************************************************/
void Ship::applyThurst()
{
	if (!speedX())
	{
		vel.addDx(THRUST_AMOUNT * (-cos(3.14f / 180.0f * angle)));
	}

	if (!speedY())
	{
		vel.addDy(THRUST_AMOUNT * (sin(3.14f / 180.0f * angle)));
	}

    return;
}

/*********************************************************************
* Slows ship down due to space friction - LOL
**********************************************************************/
void Ship::motion()
{
	if ((int)vel.getDx() > 0)
	{
		vel.subDx(0.2);
	}
	else if ((int)vel.getDx() < 0)
	{
		vel.addDx(0.2);
	}
	else
	{
		vel.setDx(0.0);
	}

	if ((int)vel.getDy() > 0)
	{
		vel.subDy(0.2);
	}
	else if ((int)vel.getDy() < 0)
	{
		vel.addDy(0.2);
	}
	else
	{
		vel.setDy(0.0);
	}
}

/*********************************************************************
* Rotates the ship
**********************************************************************/
void Ship::addSpin(int s)
{
	spin += s;
	
	if (angle <= 0)
	{
		angle = 359;
	}
	else if (angle >= 359)
	{
		angle = 0;
	}

	angle -= s;
	return;
}

/*********************************************************************
* Creates MAX speed X
**********************************************************************/
bool Ship::speedX()
{
	if ((int)vel.getDx() >= 10)
	{
		return true;
	}
	else if ((int)vel.getDx() <= -10)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*********************************************************************
* Creates MAX speed Y
**********************************************************************/
bool Ship::speedY()
{
	if ((int)vel.getDy() >= 10)
	{
		return true;
	}
	else if ((int)vel.getDy() <= -10)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*********************************************************************
* Draws the ship
**********************************************************************/
void Ship::draw()
{
	drawShip(pos, ROTATE_AMOUNT + spin, false);
}

/*********************************************************************
* Moves the ship
**********************************************************************/
void Ship::advance()
{
	pos.addX(vel.getDx());
	pos.addY(vel.getDy());
}

/*********************************************************************
* Kills the ship
**********************************************************************/
void Ship::kill()
{
	setAlive(false);
}
