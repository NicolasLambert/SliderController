/*
 * AbstractParamState.cpp
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#include "AbstractParamState.h"

AbstractParamState::AbstractParamState(LiquidCrystal * const lcd, char const * const label,
		AbstractSliderParam * const param) :
		AbstractSliderState(lcd), m_label(label), m_param(param) {
}

AbstractSliderParam * const AbstractParamState::getParam() const {
	return m_param;
}

void AbstractParamState::printLabelWithPadding() const {
	m_lcd->setCursor(0, 1);
	m_lcd->print(m_label);
	int paddingSize = PADDING_LABEL_SIZE - strlen(m_label);
	for (int i = 0; i < paddingSize; i++)
		m_lcd->print(' ');
}
