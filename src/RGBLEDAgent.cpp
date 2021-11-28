/*
 * RGBLEDAgent.cpp
 *
 *  Created on: 24 Oct 2021
 *      Author: jondurrant
 */

#include "FreeRTOS.h"
#include "RGBLEDAgent.h"
#include <stdio.h>


RGBLEDAgent::~RGBLEDAgent() {
	// TODO Auto-generated destructor stub
}

RGBLEDAgent::RGBLEDAgent(unsigned char redPin, unsigned char greenPin, unsigned char bluePin){
	rgbPWM.setup(redPin, greenPin, bluePin);
}

bool RGBLEDAgent::set(RGBMode m, unsigned char r, unsigned char g, unsigned char b){
	unsigned char cmd[4];
	cmd[0] = m;
	cmd[1]= r;
	cmd[2] = g;
	cmd[3] = b;
	if (xRGBQueue != NULL){
		return (xQueueSendToBack( xRGBQueue,
				( void * ) &cmd,
				( TickType_t ) 10
			) == pdPASS);
	}
	return false;
}

bool RGBLEDAgent::start(UBaseType_t priority){
	BaseType_t xReturned;
	xRGBQueue = xQueueCreate( 10, sizeof( unsigned char[4] ) );
	if (xRGBQueue != NULL){
		/* Create the ta
		 * sk, storing the handle. */
		xReturned = xTaskCreate(
			RGBLEDAgent::vTask,       /* Function that implements the task. */
			"RGB",   /* Text name for the task. */
			100,             /* Stack size in words, not bytes. */
			( void * ) this,    /* Parameter passed into the task. */
			priority,/* Priority at which the task is created. */
			&xHandle
		);
		return (xReturned == pdPASS);
	}
	return false;
}


void RGBLEDAgent::vTask( void * pvParameters )
{
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below.
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
    */
	RGBLEDAgent *task = (RGBLEDAgent *) pvParameters;
	task->run();
}

void RGBLEDAgent::run(){
	unsigned char cmd[4];

	rgbPWM.setRGBb(0xFF,0xFF,0xFF);
	rgbPWM.setMode(RGBModeOff);
    for( ;; )
    {
    	if (uxQueueMessagesWaiting(xRGBQueue)> 0){
    		if( xQueueReceive( xRGBQueue,
				 cmd, ( TickType_t ) 0 ) == pdPASS ){
    			rgbPWM.setRGBb(cmd[1], cmd[2], cmd[3]);
    			rgbPWM.setMode((RGBMode)cmd[0]);
    		}
    	}
    	rgbPWM.tick();
		vTaskDelay(1);
    }
}
