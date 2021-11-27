/*
 * RGBpwm.h
 *
 * RGB LED driver for a common cathode LED
 *
 *  Created on: 24 Oct 2021
 *      Author: jondurrant
 */

#ifndef RGBPWM_H_
#define RGBPWM_H_

#include "pico/stdlib.h"

enum RGBMode { RGBModeOff, RGBModeOn, RGBModeSlow, RGBModeFast, RGBModeFade, RGBModeRainbow, RGBModeOnce };

class RGBpwm {
public:

	/***
	 * Default constructor, setup must be run on object
	 */
	RGBpwm();

	/***
	 * Set up RGB pwm for the defined GPIO Pins
	 * @param redPin - GPIO number
	 * @param greenPin - GPIO number
	 * @param bluePin - GPIO number
	 */
	RGBpwm(unsigned char redPin, unsigned char greenPin, unsigned char bluePin);

	/***
	 * Destructor
	 */
	virtual ~RGBpwm();

	/***
	 * Setup GPIO pins connected to the RGB Led
	 * @param redPin
	 * @param greenPin
	 * @param bluePin
	 */
	void setup(unsigned char redPin, unsigned char greenPin, unsigned char bluePin);

	/***
	 * Set RGB colour of the LED. Max brightness is 0xffff
	 * @param rgb - array is copied
	 */
	void setRGB(uint16_t rgb[3]);

	/***
	 * Set RGB colour of LED, based on 16 bit integers
	 * @param r
	 * @param g
	 * @param b
	 */
	void setRGB(uint16_t r, uint16_t g, uint16_t b);

	/***
	 * Set RGB based on 8 bit brightness, internally squares input
	 * @param r
	 * @param g
	 * @param b
	 */
	void setRGBb(unsigned char r, unsigned char g, unsigned char b);

	/***
	 * Set mode: On, Off, Flash, etc
	 * @param m
	 */
	void setMode(RGBMode m);

	/***
	 * tick function called by agent on each loop to update the led.
	 */
	void tick();

private:
	unsigned char redPin;
	unsigned char greenPin;
	unsigned char bluePin;

	uint16_t rgb[3];
	bool changed = false;
	RGBMode mode = RGBModeOff;
	RGBMode prevMode = RGBModeOff;
	unsigned int tickCount = 0;
	bool state = false;


	void off();
	void on();
	void fade(unsigned char lvl);
	void rainbow(unsigned int lvl);


};

#endif /* RGBPWM_H_ */
