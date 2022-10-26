/*
 * Enemy.h
 *
 *  Created on: 28 Tem 2022
 *      Author: Ceyda
 */

#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_
#include "gObject.h"

class Enemy: gObject {
public:
	Enemy();
	Enemy(const Enemy& original);
	virtual ~Enemy();


	float getX();
	void setX(float x);

	void setY(float y);
	float getY();

	void setRotation(float rotation);
	float getRotation();

	void setAnimationNo(int animationNo);
	int getAnimationNo();

	void setFrameNo(int frameNo);
	int getFrameNo();

	void setFrameNum(int frameNum);
	int getFrameNum();

	void setLooping(bool isLooping);
	bool isLooping();

	void setFrameCounter(int frameCounter);
	int getFrameCounter();

	void setFrameCounterLimit(int frameCounterLimit);
	int getFrameCounterLimit();


	void nextFrame();


private:
	float x, y, rotation;
	int animationno;
	int frameno;
	int framenum;
	int framecounter;
	int framecounterlimit;
	bool islooping;
};

#endif /* SRC_ENEMY_H_ */
