/*************************************************************
* File: velocity.h
* Author: Bryan McNeil
*
* Description: Creates Velocity object
*************************************************************/

#ifndef VELOCITY_H
#define VELOCITY_H

/*************************************************************
* Class: Velocity
**************************************************************/
class Velocity
{
private:
	float dx;
	float dy;

public:
	Velocity();
	Velocity(float x, float y);

	float getDx() { return dx; }
	float getDy() { return dy; }

	void setDx(float x) { dx = x; return; }
	void setDy(float y) { dy = y; return; }

	void addDx(float x);
	void addDy(float y);

	void subDx(float x);
	void subDy(float y);

};

#endif