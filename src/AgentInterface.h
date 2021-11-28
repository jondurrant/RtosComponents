/*
 * AgentInterface.h
 *
 * Abstract interface to Agents to run as task within RTOS
 *
 *  Created on: 27 Nov 2021
 *      Author: jondurrant
 */

#ifndef AGENTINTERFACE_H_
#define AGENTINTERFACE_H_

#include <FreeRTOS.h>
#include <task.h>

class AgentInterface {
public:
	AgentInterface();
	virtual ~AgentInterface();

	/***
	 *  create the vtask, will get picked up by scheduler
	 *
	 *  */
	virtual  bool start(UBaseType_t priority = tskIDLE_PRIORITY) = 0;

	/***
	 * Stop task
	 * @return
	 */
	virtual void stop();


	/***
	 * Get high water for stack
	 * @return close to zero means overflow risk
	 */
	virtual unsigned int getStakHighWater();

	/***
	 * Get the FreeRTOS task being used
	 * @return
	 */
	virtual TaskHandle_t getTask();

protected:

	//The task
	TaskHandle_t xHandle = NULL;

};

#endif /* AGENTINTERFACE_H_ */
