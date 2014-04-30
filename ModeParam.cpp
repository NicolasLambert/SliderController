/*
 * ModeParam.cpp
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#include "ModeParam.h"

ModeParam::ModeParam(LiquidCrystal * const lcd, const int eepromAdr) :
		AbstractSliderParam(lcd, eepromAdr) {
	load();
}

bool ModeParam::isSimulate() const {
	return m_simulate;
}

void ModeParam::setSimulate(bool simulate) {
	this->m_simulate = simulate;
}

void ModeParam::print() const {
	m_lcd->setCursor(6, 1);
	if (m_simulate) {
		m_lcd->print("Simulating");
	} else {
		m_lcd->print("   Playing");
	}
}

void ModeParam::increase() {
	m_simulate = false;
}

void ModeParam::decrease() {
	m_simulate = true;
}

const int ModeParam::getType() const {
	return typeParam_Mode;
}

void ModeParam::save() const {
	EEPROM.write(m_eepromAdr, m_simulate);
}

void ModeParam::load() {
	m_simulate = EEPROM.read(m_eepromAdr);
}
