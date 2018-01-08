/*************************************************************
* File: flyingObject.cpp
* Author: Bryan McNeil
*
* Description: Base Class for flying objects
*************************************************************/

#include "flyingObject.h"


/*********************************************************************
* Default Constructor
* pos = (0, 0)
* vel = (0.0, 0.0)
**********************************************************************/
FlyingObject::FlyingObject()
{
	pos = Point();
	vel = Velocity();
	alive = true;

	return;
}

