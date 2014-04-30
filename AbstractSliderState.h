/*
 * AbstractSliderState.h
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#ifndef ABSTRACTSLIDERSTATE_H_
#define ABSTRACTSLIDERSTATE_H_
#include "PrintableItem.h"

#define typeState_Welcome 0
#define typeState_Settings 1
#define typeState_Simulate 2
#define typeState_Play 3

class AbstractSliderState: public PrintableItem {
public:
	AbstractSliderState(LiquidCrystal * const lcd);
	virtual int const getType() const = 0;
};

#endif /* ABSTRACTSLIDERSTATE_H_ */
