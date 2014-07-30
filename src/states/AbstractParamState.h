/*
 * AbstractParamState.h
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#ifndef ABSTRACTPARAMSTATE_H_
#define ABSTRACTPARAMSTATE_H_

#include "AbstractSliderState.h"
#include "../param/AbstractSliderParam.h"

#define PADDING_LABEL_SIZE 11

class AbstractParamState: public AbstractSliderState {
public:
	AbstractParamState(LiquidCrystal * const lcd, char const * const label, AbstractSliderParam * const param);
	virtual AbstractSliderParam * const getParam() const;
	char const * const m_label;
protected:
	AbstractSliderParam * const m_param;
	void printLabelWithPadding() const;
};

#endif /* ABSTRACTPARAMSTATE_H_ */
