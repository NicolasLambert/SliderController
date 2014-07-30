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

void DelayParam::padding(int paddingSize) const {
	while (paddingSize > 0) {
		paddingSize--;
		m_lcd->print(' ');
	}
}

void DelayParam::print(unsigned int const value, unsigned int const unit, const unsigned int slotSize,
		const unsigned int col, const unsigned int row) const {
	m_lcd->setCursor(col, row);
	if (value > 0) {
		char const * const unitLabel = getUnitLabel(unit);
		padding(slotSize - ((int) log10(value)) - 1 - strlen(unitLabel));
		m_lcd->print(value);
		m_lcd->print(unitLabel);
	} else if (col >= 11) {
		char const * const unitLabel = getUnitLabel(unit);
		padding(slotSize - 1 - strlen(unitLabel));
		m_lcd->print('0');
		m_lcd->print(unitLabel);
	} else {
		padding(slotSize);
	}
}

void DelayParam::print(unsigned int const value, unsigned int const unit) const {
	print(value, unit, MAX_PARAM_NB_CHAR, 11, 1);
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
#endif
	return result;
}

const unsigned long DelayParam::getDelayInMs() const {
	return getDelayInMs(this);
}

bool DelayParam::printRemaining(const unsigned long beginTime, DelayParam const * const param) const {
	unsigned long int delayInMs = getDelayInMs(param);
	unsigned long int endTime = beginTime + delayInMs;
	unsigned long int currentTime = millis();
	if (endTime > currentTime) {
		unsigned long remaining = endTime - currentTime;
		unsigned int nbMs, nbS, nbM;

		nbM = remaining / MS_IN_ONE_M;
		nbS = (remaining - nbM * MS_IN_ONE_M) / MS_IN_ONE_S;
		if (nbM == 0) {
			nbMs = remaining - nbM * MS_IN_ONE_M - nbS * MS_IN_ONE_S;
			print(nbS, SECOND, 3, 8, 1);
			print(nbMs, MILLISECOND, 5, 11, 1);
		} else {
			print(nbM, MINUTE, 4, 9, 1);
			print(nbS, SECOND, 3, 13, 1);
		}
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
	case SECOND:
		return 59;
	case MINUTE:
		return 999;
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
	int step = getStepValueForCurrentUnit();
	if (m_value > getMaxValueForCurrentUnit() - step) {
		changeUnit(true);
		m_value = this->getMinValueForCurrentUnit();
	} else {
		m_value += step;
	}
}

void DelayParam::decrease() {
	int step = getStepValueForCurrentUnit();
	if (m_value < this->getMinValueForCurrentUnit() + step) {
		changeUnit(false);
		m_value = getMaxValueForCurrentUnit();
	} else {
		m_value -= step;
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
	if (m_unit < MILLISECOND || m_unit > MINUTE || m_value > getMaxValueForCurrentUnit()
			|| m_value < getMinValueForCurrentUnit() || m_value % getStepValueForCurrentUnit() != 0) {
		// value or unit are invalids. It should be the first launch, no value was save, we can use a default value
		m_value = 1;
		m_unit = SECOND;
	}
}
