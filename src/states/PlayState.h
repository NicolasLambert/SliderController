/*
 * PlayState.h
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include "AbstractActionState.h"

class PlayState: public AbstractActionState {
public:
	PlayState(LiquidCrystal * const lcd, char const * const label, DelayParam * const param, WayParam * const wayParam);
	virtual void print() const;
	virtual int const getType() const;
};

#endif /* PLAYSTATE_H_ */
