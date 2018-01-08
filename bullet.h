#ifndef BULLET_H
#define BULLET_H

#define BULLET_SPEED 5
#define BULLET_LIFE 40
#define _USE_MATH_DEFINES

#include "flyingObject.h"
#include <cmath>
#include "uiDraw.h"

// Bullets for ship
class Bullet :
	public FlyingObject
{
private:
	int timer;
public:
	Bullet();

	void fire(Point p, float angle, float x, float y);
	void kill();
	void draw();
	void advance();
	void time();
};

#endif /* bullet_h */
