/*
 * WelcomeState.h
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#ifndef WELCOMESTATE_H_
#define WELCOMESTATE_H_

#include "AbstractSliderState.h"

class WelcomeState: public AbstractSliderState {
public:
	WelcomeState(LiquidCrystal * const lcd);
	virtual void print() const;
	virtual int const getType() const;
};

#endif /* WELCOMESTATE_H_ */
