/*
 * DelayParam.cpp
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#include "DelayParam.h"

DelayParam::DelayParam(LiquidCrystal * const lcd, unsigned const int eepromAdr) :
		AbstractSliderParam(lcd, eepromAdr) {
	load();
}

char const * const DelayParam::getUnitLabel(unsigned int const unit) const {
	switch (unit) {
	case MILLISECOND:
		return "ms";
	case SECOND:
		return "s";
	case MINUTE:
		return "m";
	}
	return "?";
}

void DelayParam::print(unsigned int const value, unsigned int const unit) const {
	const char* unitLabel = getUnitLabel(unit);
	int valueSize = value == 0 ? 1 : (((int) log10(value)) + 1);
	int paddingSize = MAX_PARAM_NB_CHAR - valueSize - strlen(unitLabel);
	m_lcd->setCursor(11, 1);
	while (paddingSize > 0) {
		paddingSize--;
		m_lcd->print(' ');
	}
	m_lcd->print(value);
	m_lcd->print(unitLabel);
}

void DelayParam::print() const {
	print(m_value, m_unit);
}

unsigned int DelayParam::getValue() const {
	return m_value;
}

const unsigned long DelayParam::getDelayInMs(DelayParam const * const param) const {
	// value and unit to ms
	unsigned long result = param->m_value;
	switch (param->m_unit) {
	case MILLISECOND:
		result *= MS_IN_ONE_MS;
		break;
	case SECOND:
		result *= MS_IN_ONE_S;
		break;
	case MINUTE:
		result *= MS_IN_ONE_M;
		break;
	}
#ifdef DEBUG
	Serial.print("Compute nb of ms in ");
	Serial.print(param->m_value);
	Serial.print(getUnitLabel(param->m_unit));
	Serial.print(" : ");
	Serial.println(result);
#else
	// I really don't know why we need some little instruction here but without it the valu returned is wrong.
	// It's a shame...
	delay(1);
#endif
	return result;
}

const unsigned long DelayParam::getDelayInMs() const {
	getDelayInMs(this);
}

bool DelayParam::printRemaining(const unsigned long beginTime, DelayParam const * const param) const {
	unsigned long int delayInMs = getDelayInMs(param);
	unsigned long int endTime = beginTime + delayInMs;
	unsigned long int currentTime = millis();
	if (endTime > currentTime) {
		unsigned long remaining = endTime - currentTime;
		unsigned int newValue, newUnit;
		// ms to value and unit
		if (remaining < MS_IN_ONE_S) {
			newValue = remaining;
			newUnit = MILLISECOND;
		} else if (remaining < MS_IN_ONE_M) {
			newValue = remaining / MS_IN_ONE_S + 1;
			newUnit = SECOND;
		} else {
			newValue = remaining / MS_IN_ONE_M + 1;
			newUnit = MINUTE;
		}
		// Then finaly print the remaining time
		print(newValue, newUnit);
		return true;
	}
	return false;
}

bool DelayParam::printRemaining(unsigned long const beginTime, bool const firstActionStep) const {
	return printRemaining(beginTime, this);
}

unsigned int DelayParam::getStepValueForCurrentUnit() const {
	switch (m_unit) {
	case MILLISECOND:
		return 10;
	case MINUTE:
	case SECOND:
		return 1;
	}
	return 0;
}

// Pay attention to step values, max values must respect steps !
unsigned int DelayParam::getMaxValueForCurrentUnit() const {
	switch (m_unit) {
	case MILLISECOND:
		return 990;
	case MINUTE:
		return 999;
	case SECOND:
		return 59;
	}
	return 0;
}

// Pay attention to step values, min values must respect steps !
unsigned int DelayParam::getMinValueForCurrentUnit() const {
	switch (m_unit) {
	case MILLISECOND:
		return 0;
	case MINUTE:
	case SECOND:
		return 1;
	}
	return 0;
}

void DelayParam::increase() {
	int newParam = m_value + getStepValueForCurrentUnit();
	if (newParam > getMaxValueForCurrentUnit()) {
		changeUnit(true);
		m_value = this->getMinValueForCurrentUnit();
	} else {
		m_value = newParam;
	}
}

void DelayParam::decrease() {
	int newValue = m_value - getStepValueForCurrentUnit();
	if (newValue < this->getMinValueForCurrentUnit()) {
		changeUnit(false);
		m_value = getMaxValueForCurrentUnit();
	} else {
		m_value = newValue;
	}
}

void DelayParam::changeUnit(bool goUp) {
	if (goUp) {
		if (m_unit == MINUTE) {
			m_unit = MILLISECOND;
		} else {
			m_unit++;
		}
	} else {
		if (m_unit == MILLISECOND) {
			m_unit = MINUTE;
		} else {
			m_unit--;
		}
	}

	// Round to step
	int step = getStepValueForCurrentUnit();
	if (m_value % step != 0) {
		m_value = (m_value / step) * step;
	}

	// Manage value limits
	int min = getMinValueForCurrentUnit();
	int max = getMaxValueForCurrentUnit();
	if (m_value < min) {
		m_value = min;
	} else if (m_value > max) {
		m_value = max;
	}
}

const int DelayParam::getType() const {
	return typeParam_Delay;
}

void DelayParam::save() const {
	unsigned int startAdr = m_eepromAdr;
	unsigned int lastValue = 0;
	for (unsigned int i = 100; i > 0; i = i / 10) {
		int newValue = m_value / i;
		EEPROM.write(startAdr++, newValue - lastValue * 10);
		lastValue = newValue;
	}
	EEPROM.write(startAdr++, m_unit);
}

void DelayParam::load() {
	unsigned int startAdr = m_eepromAdr;
	m_value = 0;
	for (unsigned int i = 100; i > 0; i = i / 10) {
		uint8_t read = EEPROM.read(startAdr++);
		m_value += read * i;
	}
	m_unit = EEPROM.read(startAdr++);
}
