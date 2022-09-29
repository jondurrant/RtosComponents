/*
 * WatchdogBlinkAgent.h
 *
 *  Created on: 27 Nov 2021
 *      Author: jondurrant
 */

#ifndef WATCHDOGBLINKAGENT_H_
#define WATCHDOGBLINKAGENT_H_

#include <stdlib.h>
#include "BlinkAgent.h"

class WatchdogBlinkAgent : public BlinkAgent {
public:
	WatchdogBlinkAgent(uint8_t ledPad, unsigned int delay = 500, uint8_t watchdogSeconds=8);
	virtual ~WatchdogBlinkAgent();

	/***
	 *  create the vtask, will get picked up by scheduler
	 *
	 *  */
	virtual  bool start(UBaseType_t priority = tskIDLE_PRIORITY);

protected:

	void run();

	static void vTask( void * pvParameters );

	uint8_t watchdogTime = 8;// Seconds


};

#endif /* WATCHDOGBLINKAGENT_H_ */
