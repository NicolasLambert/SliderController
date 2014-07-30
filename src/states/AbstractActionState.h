/*
 * AbstractActionState.h
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#ifndef ABSTRACTACTIONSTATE_H_
#define ABSTRACTACTIONSTATE_H_

#include "AbstractParamState.h"
#include "../param/DelayParam.h"
#include "../param/WayParam.h"

class AbstractActionState: public AbstractParamState {
public:
	AbstractActionState(LiquidCrystal * const lcd, char const * const label, DelayParam * const param,
			WayParam * const wayParam);
	virtual void print() const;
	virtual DelayParam * const getParam() const;
private:
	WayParam * const m_wayParam;
};

#endif /* ABSTRACTACTIONSTATE_H_ */
