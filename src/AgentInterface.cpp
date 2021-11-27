/*
 * AgentInterface.cpp
 *
 *  Created on: 27 Nov 2021
 *      Author: jondurrant
 */

#include "AgentInterface.h"

AgentInterface::AgentInterface() {
	// TODO Auto-generated constructor stub

}

AgentInterface::~AgentInterface() {
	stop();
}



/***
 * Stop task
 * @return
 */
void AgentInterface::stop(){
	if (xHandle != NULL){
		vTaskDelete(  xHandle );
		xHandle = NULL;
	}
}


/***
* Get high water for stack
* @return close to zero means overflow risk
*/
unsigned int AgentInterface::getStakHighWater(){
	if (xHandle != NULL)
		return uxTaskGetStackHighWaterMark(xHandle);
	else
		return 0;
}
