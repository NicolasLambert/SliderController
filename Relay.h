/*
 * Relay.h
 *
 *  Created on: 29 avr. 2014
 *      Author: nicolaslambert
 */

#ifndef RELAY_H_
#define RELAY_H_

#include "Global.h"
#include "Arduino.h"

class Relay {
public:
	Relay(int const relayId);
	void switchOnFor(unsigned long delay);
	void update();
	void cancel();
private:
	int const m_relayId;
	unsigned long m_timeOfLastSwitchOn;
	unsigned long m_timeOfNextSwitch;
	void switch_(bool on);
};

#endif /* RELAY_H_ */
