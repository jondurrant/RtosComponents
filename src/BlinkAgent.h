/*
 * BlinkAgent.h
 *
 *  Created on: 27 Nov 2021
 *      Author: jondurrant
 */

#ifndef BLINKAGENT_H_
#define BLINKAGENT_H_

#include "AgentInterface.h"
#include "pico/stdlib.h"
#include "stdio.h"

class BlinkAgent : public AgentInterface{
public:
	BlinkAgent(uint8_t ledPad, unsigned int delay = 500);
	virtual ~BlinkAgent();

	/***
	 *  create the vtask, will get picked up by scheduler
	 *
	 *  */
	virtual  bool start(UBaseType_t priority = tskIDLE_PRIORITY);

protected:

	void run();

	void blink();

	static void vTask( void * pvParameters );

	unsigned int delay;

	uint8_t LED_PIN;

};

#endif /* BLINKAGENT_H_ */
