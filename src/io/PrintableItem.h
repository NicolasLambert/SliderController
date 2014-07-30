/*
 * PrintableItem.h
 *
 *  Created on: 29 avr. 2014
 *      Author: nicolaslambert
 */

#ifndef PRINTABLEITEM_H_
#define PRINTABLEITEM_H_
#include "../Global.h"
#include "LiquidCrystal.h"

class PrintableItem {
public:
	PrintableItem(LiquidCrystal * const lcd);
	virtual void print() const = 0;
protected:
	LiquidCrystal * const m_lcd;
};

#endif /* PRINTABLEITEM_H_ */
