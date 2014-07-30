/*
 * WaitParam.h
 *
 *  Created on: 29 avr. 2014
 *      Author: nicolaslambert
 */

#ifndef WAITPARAM_H_
#define WAITPARAM_H_

#include "DelayParam.h"

class WaitParam: public DelayParam {
public:
	WaitParam(LiquidCrystal * const lcd, unsigned int const eepromAdr, DelayParam * const startInParam);
	virtual bool printRemaining(unsigned long const beginTime, bool const firstActionStep) const;
private:
	DelayParam * const m_startInParam;
};

#endif /* WAITPARAM_H_ */
