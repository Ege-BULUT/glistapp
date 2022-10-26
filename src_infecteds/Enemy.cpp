/*
 * Enemy.cpp
 *
 *  Created on: 28 Tem 2022
 *      Author: Ceyda
 */

#include <Enemy.h>

Enemy::Enemy(){

	x = 0.0f;
	y = 0.0f;
	rotation = 0.0f;
	frameno = 0;
	framenum = 8;
	framecounter = 0;
	framecounterlimit = 3;
	animationno = 0;
	islooping = true;

}
//copy constructor
Enemy::Enemy(const Enemy& original) {

	x = original.x;
	y = original.y;
	rotation = original.rotation;
	frameno = original.frameno;
	framenum = original.framenum;
	framecounter = original.framecounter;
	framecounterlimit = original.framecounterlimit;
	animationno = original.animationno;
	islooping = original.islooping;

}

Enemy::~Enemy() {
	// TODO Auto-generated destructor stub
}

void Enemy::setX(float x) {
	this->x = x;
}

float Enemy::getX() {
	return x;
}

void Enemy::setY(float y) {
	this->y = y;
}

float Enemy::getY() {
	return y;
}

void Enemy::setRotation(float rotation) {
	this->rotation = rotation;
}

float Enemy::getRotation() {
	return rotation;
}


void Enemy::setAnimationNo(int animationNo) {
	animationno = animationNo;
}

int Enemy::getAnimationNo() {
	return animationno;
}

void Enemy::setLooping(bool isLooping) {
	islooping = isLooping;
}

bool Enemy::isLooping() {
	return islooping;
}


void Enemy::setFrameNo(int frameNo) {
	frameno = frameNo;
}

int Enemy::getFrameNo() {
	return frameno;
}

void Enemy::setFrameNum(int frameNum) {
	framenum = frameNum;
}

int Enemy::getFrameNum() {
	return framenum;
}

void Enemy::setFrameCounter(int frameCounter) {

}

int Enemy::getFrameCounter() {
	return framecounter;
}

void Enemy::setFrameCounterLimit(int frameCounterLimit) {

}

int Enemy::getFrameCounterLimit() {
	return framecounterlimit;
}

void Enemy::nextFrame() {
	framecounter++;
	if(framecounter >= framecounterlimit ) {
		frameno++;
		if(frameno >= framenum) {
			if(islooping) frameno = 0;
			else frameno = framenum - 1;
		}
		framecounter = 0;
	}
}

