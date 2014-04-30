/*
 * WayParam.cpp
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#include "WayParam.h"

WayParam::WayParam(LiquidCrystal * const lcd) :
// -1 because this param is never saved
		AbstractSliderParam(lcd, -1) {
	m_goLeft = false;
}

bool WayParam::isGoLeft() const {
	return m_goLeft;
}

void WayParam::setGoLeft(bool goLeft) {
	this->m_goLeft = goLeft;
}

void WayParam::print() const {
	m_lcd->setCursor(0, 0);
	if (m_goLeft) {
		printArrow("<<<");
	} else {
		printArrow(">>>");
	}
}

const int WayParam::getType() const {
	return typeParam_Way;
}

void WayParam::printArrow(char const * const arrows) const {
	m_lcd->setCursor(0, 0);
	m_lcd->print(arrows);
	m_lcd->setCursor(13, 0);
	m_lcd->print(arrows);
}

void WayParam::increase() {
	m_goLeft = false;
}

void WayParam::decrease() {
	m_goLeft = true;
}

void WayParam::save() const {
	// No need to save that
	// EEPROM.write(m_eepromAdr, m_goLeft);
}

void WayParam::load() {
	// No need to load that
	// m_goLeft = EEPROM.read(m_eepromAdr);
}
