/*
 * AbstractActionState.cpp
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#include "AbstractActionState.h"

AbstractActionState::AbstractActionState(LiquidCrystal * const lcd, char const * const label, DelayParam * const param,
		WayParam * const wayParam) :
		AbstractParamState(lcd, label, param), m_wayParam(wayParam) {

}

void AbstractActionState::print() const {
	m_wayParam->print();
	printLabelWithPadding();
	if (getParam()->getValue() == 0) {
		m_param->print();
	}
}

DelayParam* const AbstractActionState::getParam() const {
	return (DelayParam * const ) m_param;
}
