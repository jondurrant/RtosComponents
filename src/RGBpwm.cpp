/*
 * RGBpwm.cpp
 *
 *  Created on: 24 Oct 2021
 *      Author: jondurrant
 */

#include "RGBpwm.h"
#include <hardware/pwm.h>
#include <string.h>
#include <stdio.h>
#include "ColorUtils.h"


#define SLOWTICK  800
#define FASTTICK  200
#define RGBTICK  2000




RGBpwm::~RGBpwm() {
	// NOP
}

RGBpwm::RGBpwm(){
	//NOP
}

RGBpwm::RGBpwm(unsigned char redPin, unsigned char greenPin, unsigned char bluePin){
	setup(redPin, greenPin, bluePin);
}

void RGBpwm::setup(unsigned char redPin, unsigned char greenPin, unsigned char bluePin){
	this->redPin = redPin;
	this->greenPin = greenPin;
	this->bluePin = bluePin;

	gpio_init(redPin);
	gpio_set_function(redPin, GPIO_FUNC_PWM);
	pwm_set_gpio_level(redPin, 0);
	uint slice_num = pwm_gpio_to_slice_num(redPin);
	pwm_set_enabled(slice_num, true);

	gpio_init(greenPin);
	gpio_set_function(greenPin, GPIO_FUNC_PWM);
	pwm_set_gpio_level(greenPin, 0);
	slice_num = pwm_gpio_to_slice_num(greenPin);
	pwm_set_enabled(slice_num, true);

	gpio_init(bluePin);
	gpio_set_function(bluePin, GPIO_FUNC_PWM);
	pwm_set_gpio_level(bluePin, 0);
	slice_num = pwm_gpio_to_slice_num(bluePin);
	pwm_set_enabled(slice_num, true);

}


void RGBpwm::setRGB(uint16_t rgb[3]){
	memcpy(this->rgb, rgb, 3);
	changed = true;
}

void RGBpwm::setRGB(uint16_t r, uint16_t g, uint16_t b){
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;

	changed = true;
}

void RGBpwm::setRGBb(unsigned char r, unsigned char g, unsigned char b){
	rgb[0] = r * r;
	rgb[1] = g * g;
	rgb[2] = b * b;
	changed = true;
}

void RGBpwm::setMode(RGBMode m){
	prevMode = mode;
	mode = m;
	changed = true;
}

void RGBpwm::tick(){
	unsigned int lvl = 0;
	float f;

	tickCount = tickCount + 1;

	if (changed){
		changed = false;
		switch(mode){
		case RGBModeOff:
			off();
			break;
		case RGBModeOn:
			on();
			break;
		case RGBModeFast:
			tickCount = 0;
			state = true;
			on();
			break;
		case RGBModeSlow:
			tickCount = 0;
			state = true;
			on();
			break;
		case RGBModeOnce:
			tickCount = 0;
			state = false;
			off();
			break;
		}
	}

	//printf("tickCount = %d\n", tickCount);
	switch(mode){
	case RGBModeFast:
		if (tickCount >= FASTTICK){
			tickCount = 0;
			if (state == true){
				on();
				state = false;
			} else {
				off();
				state = true;
			}
		}
		break;
	case RGBModeSlow:
		if (tickCount >= SLOWTICK){
			tickCount = 0;
			if (state){
				on();
				state = false;
			} else {
				off();
				state = true;
			}
		}
		break;
	case RGBModeFade:
		if (tickCount >= SLOWTICK*2){
			tickCount = 0;
		}
		if (tickCount < (SLOWTICK )){
			lvl = tickCount;
		} else {
			lvl = tickCount - (SLOWTICK);
			lvl = (SLOWTICK) - lvl;
		}
		f = ((float)lvl / (float)(SLOWTICK)) * 255.0;
		fade((unsigned char)f);

		break;
	case RGBModeRainbow:
		if (tickCount >= RGBTICK*2){
			tickCount = 0;
		}
		if (tickCount < (RGBTICK )){
			lvl = tickCount;
		} else {
			lvl = tickCount - (RGBTICK);
			lvl = (RGBTICK) - lvl;
		}
		rainbow(lvl);
		break;
	case RGBModeOnce:
		if (tickCount >= FASTTICK){
			tickCount = 0;
			if (state == true){
				setMode(prevMode);
			} else {
				off();
				state = true;
			}
		}
		break;
	default:
		tickCount = 0;
		break;
	}
}


void RGBpwm::off(){
	pwm_set_gpio_level(redPin, 0);
	pwm_set_gpio_level(greenPin, 0);
	pwm_set_gpio_level(bluePin, 0);
}

void RGBpwm::on(){
	pwm_set_gpio_level(redPin, rgb[0]);
	pwm_set_gpio_level(greenPin, rgb[1]);
	pwm_set_gpio_level(bluePin, rgb[2]);
}


void RGBpwm::fade(unsigned char lvl){
	float r = ((float)rgb[0] / (float)0xff) * (float)lvl;
	float g = ((float)rgb[1] / (float)0xff) * (float)lvl;
	float b = ((float)rgb[2] / (float)0xff) * (float)lvl;
	pwm_set_gpio_level(redPin, (uint16_t)r);
	pwm_set_gpio_level(greenPin, (uint16_t)g);
	pwm_set_gpio_level(bluePin, (uint16_t)b);
}

void RGBpwm::rainbow(unsigned int lvl){
	double l = (double)lvl / (double)RGBTICK;
	unsigned char r, g, b;
	ColorUtils::valToRGB(l, r, g, b);
	pwm_set_gpio_level(redPin, (uint16_t)(r*r));
	pwm_set_gpio_level(greenPin, (uint16_t)(g*g));
	pwm_set_gpio_level(bluePin, (uint16_t)(b*b));
}
