/*
 * BlinkAgent.cpp
 *
 *  Created on: 27 Nov 2021
 *      Author: jondurrant
 */

#include "BlinkAgent.h"


BlinkAgent::BlinkAgent(unsigned int delay) {
	this->delay = delay;
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
}

BlinkAgent::~BlinkAgent() {
	//NOP
}

bool BlinkAgent::start(UBaseType_t priority){
	BaseType_t res;
	res = xTaskCreate(
		BlinkAgent::vTask,       /* Function that implements the task. */
		"Blink",   /* Text name for the task. */
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
 void BlinkAgent::vTask( void * pvParameters ){
	 BlinkAgent *task = (BlinkAgent *) pvParameters;
	 if (task != NULL){
		 task->run();
	 }
 }

 /***
  * Main Run Task for agent
  */
 void BlinkAgent::run(){

	for( ;; )
	{
		blink();
	}

 }


 void BlinkAgent::blink(){
	gpio_put(LED_PIN, 1);
	vTaskDelay(delay);
	gpio_put(LED_PIN, 0);
	vTaskDelay(delay);
 }
