/*
 * WayParam.h
 *
 *  Created on: 28 avr. 2014
 *      Author: nicolaslambert
 */

#ifndef WAYPARAM_H_
#define WAYPARAM_H_

#include "AbstractSliderParam.h"

class WayParam: public AbstractSliderParam {
public:
	WayParam(LiquidCrystal * const lcd);
	bool isGoLeft() const;
	void setGoLeft(bool goLeft);
	virtual void print() const;
	virtual void increase();
	virtual void decrease();
	virtual int const getType() const;
	virtual void save() const;
	virtual void load();

private:
	bool m_goLeft;
	void printArrow(char const * const arrows) const;
};

#endif /* WAYPARAM_H_ */
