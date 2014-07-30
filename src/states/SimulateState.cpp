/*
 * SimulateState.cpp
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#include "SimulateState.h"

SimulateState::SimulateState(LiquidCrystal * const lcd, char const * const label, DelayParam * const param,
		WayParam * const wayValue) :
		AbstractActionState(lcd, label, param, wayValue) {
}

void SimulateState::print() const {
	AbstractActionState::print();
	m_lcd->setCursor(3, 0);
	m_lcd->print("Simulating");
}

const int SimulateState::getType() const {
	return typeState_Simulate;
}
