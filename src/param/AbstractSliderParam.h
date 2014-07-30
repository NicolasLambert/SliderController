/*
 * AbstractSliderParam.h
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#ifndef ABSTRACTSLIDERPARAM_H_
#define ABSTRACTSLIDERPARAM_H_
#include "../io/PrintableItem.h"
#include "EEPROM.h"

#define typeParam_Delay 0
#define typeParam_Mode 1
#define typeParam_Way 2

class AbstractSliderParam: public PrintableItem {
public:
	AbstractSliderParam(LiquidCrystal * const lcd, const int eepromAdr);
	virtual void increase() = 0;
	virtual void decrease() = 0;
	virtual int const getType() const = 0;
	virtual void save() const = 0;
	virtual void load() = 0;
protected:
	const int m_eepromAdr;
};

#endif /* ABSTRACTSLIDERPARAM_H_ */
