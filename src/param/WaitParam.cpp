/*
 * WaitParam.cpp
 *
 *  Created on: 29 avr. 2014
 *      Author: nicolaslambert
 */

#include "WaitParam.h"

WaitParam::WaitParam(LiquidCrystal* const lcd, unsigned int const eepromAdr, DelayParam* const startInParam) :
		DelayParam(lcd, eepromAdr), m_startInParam(startInParam) {
}

bool WaitParam::printRemaining(const unsigned long beginTime, bool const firstActionStep) const {
	if (firstActionStep) {
		return DelayParam::printRemaining(beginTime, m_startInParam);
	} else {
		return DelayParam::printRemaining(beginTime, firstActionStep);
	}
}
