/*
 * DelayParam.h
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#ifndef DELAYPARAM_H_
#define DELAYPARAM_H_
#define MAX_PARAM_NB_CHAR 5
#define MILLISECOND 0
#define SECOND 1
#define MINUTE 2
#define MS_IN_ONE_MS 1ul
#define MS_IN_ONE_S 1000ul
#define MS_IN_ONE_M 60000ul
#include "AbstractSliderParam.h"
#include "math.h"
#include "Arduino.h"

class DelayParam: public AbstractSliderParam {

public:
	DelayParam(LiquidCrystal * const lcd, const unsigned int eepromAdr);
	void changeUnit(bool goUp);
	virtual void print() const;
	virtual void increase();
	virtual void decrease();
	virtual int const getType() const;
	unsigned int getValue() const;
	virtual void save() const;
	virtual void load();
	virtual bool printRemaining(unsigned long const beginTime, bool const firstActionStep) const;
	unsigned long const getDelayInMs() const;

protected:
	virtual bool printRemaining(unsigned long const beginTime, DelayParam const * const param) const;

private:
	unsigned int m_value;
	unsigned int m_unit;
	char const * const getUnitLabel(unsigned int const unit) const;
	unsigned int getMinValueForCurrentUnit() const;
	unsigned int getMaxValueForCurrentUnit() const;
	unsigned int getStepValueForCurrentUnit() const;
	void print(unsigned int const value, unsigned int const unit) const;
	unsigned long const getDelayInMs(DelayParam const * const param) const;
};

#endif /* DELAYPARAM_H_ */
