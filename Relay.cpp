/*
 * Relay.cpp
 *
 *  Created on: 29 avr. 2014
 *      Author: nicolaslambert
 */

#include "Relay.h"

Relay::Relay(int const relayId) :
		m_relayId(relayId) {
	m_timeOfNextSwitch = 0;
	pinMode(m_relayId, OUTPUT);
	switch_(false);
}

void Relay::switch_(bool on) {
#ifdef DEBUG
	Serial.print("Switch ");
	Serial.println(on?"on":"off");
#endif
	if (on) {
		m_timeOfLastSwitchOn = millis();
		digitalWrite(m_relayId, LOW);
	} else {
		m_timeOfLastSwitchOn = 0;
		m_timeOfNextSwitch = 0;
		digitalWrite(m_relayId, HIGH);
	}
}

void Relay::switchOnFor(unsigned long const delay) {
#ifdef DEBUG
	Serial.print("Switch on for ");
	Serial.println(delay);
#endif
	switch_(true);
	m_timeOfNextSwitch = m_timeOfLastSwitchOn + delay;
}

void Relay::update() {
	if (m_timeOfNextSwitch > 0 && millis() > m_timeOfNextSwitch) {
		switch_(false);
	}
}

void Relay::cancel() {
	switch_(false);
}
