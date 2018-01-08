#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H

#include "point.h"
#include "velocity.h"


//FlyingObject abstract class
class FlyingObject
{
protected:
	Point pos;
	Velocity vel;
	bool alive;
public:
	FlyingObject();

	Point getPoint() { return pos; }
	Velocity getVelocity() { return vel; }
	bool isAlive() { return alive;  }

	void setPoint(Point p) { pos = p; return; }
	void setVelocity(Velocity v) { vel = v; return; }
	void setAlive(bool a) { alive = a; return; }

	virtual void draw() = 0;
	virtual void advance() = 0;
	virtual void kill() = 0;

};

#endif /* flyingObject_h */
