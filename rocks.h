#ifndef ROCKS_H
#define ROCKS_H

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "flyingObject.h"
#include "uiDraw.h"

//   Rock Base Class
class Rock
	: public FlyingObject
{
protected:
	int size;
	int spin;
public:
	Rock();

	int getSize() { return size; }
	void setSize(int s) { size = s; return; }

	virtual void draw() = 0;
	virtual void advance() = 0;
	virtual void kill() = 0;
};

//   BigRock
class BigRock
	: public Rock
{
public:
	BigRock();

	virtual void draw();
	virtual void advance();
	virtual void kill();
};

//   MediumRock
class MedRock
	: public Rock
{
public:
	MedRock();
	MedRock(float px, float py, float vx, float vy);

	virtual void draw();
	virtual void advance();
	virtual void kill();
};

//   SmallRock
class SmallRock
	: public Rock
{
public:
	SmallRock();
	SmallRock(float px, float py, float vx, float vy);

	virtual void draw();
	virtual void advance();
	virtual void kill();
};


#endif /* rocks_h */
