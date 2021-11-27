/*
 * WatchdogBlinkAgent.cpp
 *
 *  Created on: 27 Nov 2021
 *      Author: jondurrant
 */

#include "WatchdogBlinkAgent.h"
#include "hardware/watchdog.h"

WatchdogBlinkAgent::WatchdogBlinkAgent(unsigned int delay,
		uint8_t watchdogSeconds) : BlinkAgent(delay) {
	watchdogTime = watchdogSeconds;
}

WatchdogBlinkAgent::~WatchdogBlinkAgent() {
	//NOP
}

bool WatchdogBlinkAgent::start(UBaseType_t priority){
	BaseType_t res;
	res = xTaskCreate(
			WatchdogBlinkAgent::vTask,       /* Function that implements the task. */
		"Watchdog",   /* Text name for the task. */
		40,             /* Stack size in words, not bytes. */
		( void * ) this,    /* Parameter passed into the task. */
		priority,/* Priority at which the task is created. */
		&xHandle
	);
	return (res == pdPASS);
}


/***
 * Internal function used by FreeRTOS to run the task
 * @param pvParameters
 */
 void WatchdogBlinkAgent::vTask( void * pvParameters ){
	 WatchdogBlinkAgent *task = (WatchdogBlinkAgent *) pvParameters;
	 if (task != NULL){
		 task->run();
	 }
 }

 /***
  * Main Run Task for agent
  */
 void WatchdogBlinkAgent::run(){

	 uint32_t watchdogCount = 0x7fffff;
	 if ((watchdogTime > 0) && (watchdogTime < 8)){
		 watchdogCount = (watchdogCount /8) * watchdogTime;
	 }
	 watchdog_enable(watchdogCount, 1);


	for( ;; )
	{
		watchdog_update();
		blink();
	}

 }

