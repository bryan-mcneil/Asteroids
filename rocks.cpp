#include "rocks.h"

/*********************************************************************
* Default Constructor
**********************************************************************/
Rock::Rock()
{
	size = 0;
	spin = 1;
	vel.setDx((float)random(-5.0, 6.0));
	vel.setDy((float)random(-5.0, 6.0));
}

/*********************************************************************
* Default Constructor
**********************************************************************/
BigRock::BigRock()
{
	size = 1;
	alive = true;
	vel.setDx((float)random(-3.0, 3.0));
	vel.setDy((float)random(-3.0, 3.0));
}

/*********************************************************************
* Draws Big Rock
**********************************************************************/
void BigRock::draw()
{
	drawLargeAsteroid(pos, BIG_ROCK_SPIN + spin);
	spin -= BIG_ROCK_SPIN;
}

/*********************************************************************
* Moves Big Rock
**********************************************************************/
void BigRock::advance()
{
	pos.addX(vel.getDx());
	pos.addY(vel.getDy());
}

/*********************************************************************
* Sets Big rock to alive = false 
**********************************************************************/
void BigRock::kill()
{
	setAlive(false);
}

/*********************************************************************
* Default Constructor
**********************************************************************/
MedRock::MedRock()
{
	size = 2;
	alive = true;
	vel.setDx((float)random(-4.0, 4.0));
	vel.setDy((float)random(-4.0, 4.0));
}

/*********************************************************************
* Constructor
**********************************************************************/
MedRock::MedRock(float px, float py, float vx, float vy)
{
	size = 2;
	alive = true;

	pos.setX(px);
	pos.setY(py);
	vel.setDx(vx);
	vel.setDy(vy);
}

/*********************************************************************
* Draws medium rock
**********************************************************************/
void MedRock::draw()
{
	drawMediumAsteroid(pos, MEDIUM_ROCK_SPIN + spin);
	spin -= MEDIUM_ROCK_SPIN;
}

/*********************************************************************
* Moves Medium Rock
**********************************************************************/
void MedRock::advance()
{
	pos.addX(vel.getDx());
	pos.addY(vel.getDy());
}

/*********************************************************************
* Kills Medium Rock
**********************************************************************/
void MedRock::kill()
{
	setAlive(false);
}

/*********************************************************************
* Default Constructor
**********************************************************************/
SmallRock::SmallRock()
{
	size = 3;
	alive = true;
	vel.setDx((float)random(-4.0, 4.0));
	vel.setDy((float)random(-4.0, 4.0));
}

/*********************************************************************
* Constructor
**********************************************************************/
SmallRock::SmallRock(float px, float py, float vx, float vy)
{
	size = 3;
	alive = true;

	pos.setX(px);
	pos.setY(py);
	vel.setDx(vx);
	vel.setDy(vy);
}

/*********************************************************************
* Draws small rock
**********************************************************************/
void SmallRock::draw()
{
	drawSmallAsteroid(pos, SMALL_ROCK_SPIN + spin);
	spin -= SMALL_ROCK_SPIN;
}

/*********************************************************************
* Moves small rock
**********************************************************************/
void SmallRock::advance()
{
	pos.addX(vel.getDx());
	pos.addY(vel.getDy());
}

/*********************************************************************
* Kills small rock
**********************************************************************/
void SmallRock::kill()
{
	setAlive(false);
}