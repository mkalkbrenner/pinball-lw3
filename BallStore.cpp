/*
 * BallStore.cpp
 *
 *  Created on: 28.08.2015
 *      Author: sr
 */

#include "BallStore.h"
#include <Arduino.h>

BallStore::BallStore(int maxBalls) {
	this->maxBalls = maxBalls;
	this->balls = 0;
	this->switchVal = (int*)malloc(sizeof(int) * maxBalls);
	this->switchIndex = (int*)malloc(sizeof(int) * maxBalls);
	for(int i = 0; i < maxBalls; i++) {
		switchIndex[i] = 0;
		switchVal[i] = 0;
	}
	this->lastIndex = 0;
}

BallStore::~BallStore() {
}

void BallStore::onSwitchUpdate(bool active, int num) {
	int old = balls;
	int i;
	for(i = 0; i < maxBalls; i++) {
	    if(switchIndex[i] == num) {
		    break;
		}
	}
	if(i >= maxBalls && lastIndex < maxBalls ) {
	    // "num" is col*100+row. num is not yet in switchIndex => add it.
		i = lastIndex++;
		switchIndex[i] = num;
	}
	switchVal[i] = (active ? 1 : 0);
	balls = 0;
	for(i = 0; i < maxBalls; i++) {
		balls += switchVal[i];
	}
	if(old != balls) {
	    Serial.print("Balls: ");Serial.println(balls);
	}
}

