/*
 * SettingsState.h
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#ifndef SETTINGSSTATE_H_
#define SETTINGSSTATE_H_

#include "AbstractParamState.h"
#include "../param/AbstractSliderParam.h"
#include "EEPROM.h"

class SettingsState: public AbstractParamState {
public:
	SettingsState(LiquidCrystal * const lcd, char const * const label, AbstractSliderParam * const param);
	virtual void print() const;
	virtual int const getType() const;
};

#endif /* SETTINGSSTATE_H_ */
