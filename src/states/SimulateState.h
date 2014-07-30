/*
 * SimulateState.h
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#ifndef SIMULATESTATE_H_
#define SIMULATESTATE_H_

#include "AbstractActionState.h"

class SimulateState: public AbstractActionState {
public:
	SimulateState(LiquidCrystal * const lcd, char const * const label, DelayParam * const param,
			WayParam * const wayParam);
	virtual void print() const;
	virtual int const getType() const;
};

#endif /* SIMULATESTATE_H_ */
