/*
 * ModeParam.h
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#ifndef MODEPARAM_H_
#define MODEPARAM_H_
#include "AbstractSliderParam.h"

class ModeParam: public AbstractSliderParam {
public:
	ModeParam(LiquidCrystal * const lcd, const int eepromAdr);
	virtual void print() const;
	virtual void increase();
	virtual void decrease();
	bool isSimulate() const;
	void setSimulate(bool simulate);
	virtual int const getType() const;
	virtual void save() const;
	virtual void load();

private:
	bool m_simulate;
};

#endif /* MODEPARAM_H_ */
