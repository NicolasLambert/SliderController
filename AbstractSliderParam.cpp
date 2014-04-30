/*
 * AbstractSliderParam.cpp
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#include "AbstractSliderParam.h"

AbstractSliderParam::AbstractSliderParam(LiquidCrystal* const lcd, const int eepromAdr) :
		PrintableItem(lcd), m_eepromAdr(eepromAdr) {
}
