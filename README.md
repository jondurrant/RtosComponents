# RtosComponents (C++)
FreeRtos Components to run RGB LED and Watchdogs, etc.

A collection of Task agents to do reusable functions within the FreeRTOS operating system. Written for the Raspberry PI Pico Microcontroller (RP2040).

## Dependencies
+ [FreeRTOS Core](https://www.freertos.org/index.html)
+ [Raspberry Pico SDK](https://raspberrypi.github.io/pico-sdk-doxygen/index.html)
++ [Watchdog](https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__watchdog.html)
++ [PWM] (https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__pwm.html)


## Example Usage

See example repo: https://github.com/jondurrant/RTOSComponentExample

## Classes

+ AgentInterface - Abstract Agent interface for starting and managing my task agents
+ BlinkAgent - simple agent to blink the Pico on board LED
+ WatchdogBlinkAgent - Blink on board LED and maintain the Pico Watchdog at same time.
+ RGBLEDAgent = Common Cathode LED driver agent that can blink dim and colour change LED. Including strobing through the rainbow

