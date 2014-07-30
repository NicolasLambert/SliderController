/*
 * PlayState.cpp
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#include "PlayState.h"

PlayState::PlayState(LiquidCrystal * const lcd, char const * const label, DelayParam * const param,
		WayParam * const wayValue) :
		AbstractActionState(lcd, label, param, wayValue) {

}

void PlayState::print() const {
	AbstractActionState::print();
	m_lcd->setCursor(3, 0);
	m_lcd->print(" Playing! ");
}

const int PlayState::getType() const {
	return typeState_Play;
}
