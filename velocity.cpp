#include "velocity.h"

/*********************************************************************
* Default Constructor
**********************************************************************/
Velocity::Velocity()
{
	dx = 0.0;
	dy = 0.0;

	return;
}

/*********************************************************************
* Constructor with parameters (float dx, float dy)
**********************************************************************/
Velocity::Velocity(float x, float y)
{
	dx = x;
	dy = y;

	return;
}

/*********************************************************************
* Adds to total velocity on X axis.
**********************************************************************/
void Velocity::addDx(float x)
{
	dx += x;

	return;
}

/*********************************************************************
* Adds to total velocity on Y axis.
**********************************************************************/
void Velocity::addDy(float y)
{
	dy += y;

	return;
}

/*********************************************************************
* Subtracts the total velocity on X axis.
**********************************************************************/
void Velocity::subDx(float x)
{
	dx -= x;

	return;
}

/*********************************************************************
* Subtracts the total velocity on Y axis.
**********************************************************************/
void Velocity::subDy(float y)
{
	dy -= y;

	return;
}