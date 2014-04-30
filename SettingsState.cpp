/*
 * SettingsState.cpp
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#include "SettingsState.h"

SettingsState::SettingsState(LiquidCrystal * const lcd, char const * const label, AbstractSliderParam * const param) :
		AbstractParamState(lcd, label, param) {
}

void SettingsState::print() const {
	m_lcd->setCursor(0, 0);
	m_lcd->print("<Go Settings Go>");
	printLabelWithPadding();
	m_param->print();
}

const int SettingsState::getType() const {
	return typeState_Settings;
}
