/*
 * WelcomeState.cpp
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#include "WelcomeState.h"

WelcomeState::WelcomeState(LiquidCrystal * const lcd) :
		AbstractSliderState(lcd) {
}

void WelcomeState::print() const {
	m_lcd->setCursor(0, 0);
	m_lcd->print("Slider    v1.0.1");
	m_lcd->setCursor(0, 1);
	m_lcd->print("Controller");
}

const int WelcomeState::getType() const {
	return typeState_Welcome;
}
