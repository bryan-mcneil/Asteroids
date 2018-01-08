#ifndef SHIP_H
#define SHIP_H

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.4

#include "flyingObject.h"
#include "uiDraw.h"
#include <cmath>

//Ship Class
class Ship
	: public FlyingObject
{
private:
	int spin;
	int angle;
public:
	Ship();

	void applyThurst();
	void motion();
	void addSpin(int s);
	void setAngle(int a) { angle = a; return; }
	int getAngle() { return angle; }
	bool speedX();
	bool speedY();

	virtual void draw();
	virtual void advance();
	virtual void kill();
};

#endif /* ship_h */
