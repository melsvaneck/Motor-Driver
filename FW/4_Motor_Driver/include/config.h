#ifndef __CONFIG_H
#define __CONFIG_H

#include <Arduino.h>

#define _STRINGIFY(x)      #x
#define STRINGIFY(x)      _STRINGIFY(x)

#define VERSION                1
#define VERSIONSTR_LONG        STRINGIFY(GIT_BRANCH-VERSION)
#define VERSIONSTR_SHORT       STRINGIFY(VERSION)


#ifdef DEBUG
	// Enable DBG(...) globally:
	// #define TOOLS_LOG_DEBUG

	// Or per file:
	#define DEBUG_MAIN_CPP

	// Specific parts:
#endif

#define BOOTSCREEN_TIMEOUT_MS   2000

#define NUMBER_OF_CHANNELS      4

#define	NUMBER_OF_MOTORS 		4

#define MAIN_LOOP_MS			100

#define I2C_LOOP_MS				200

#define DEFAULT_SPEED           5
#define SPEED_MULTIPLIER       	25

#define SPEED_PERCENT			10

// PINS M5CORE2
// #define PIN_SCLK				GPIO_NUM_18
// #define PIN_MOSI				GPIO_NUM_23
// #define PIN_MISO				GPIO_NUM_38
// #define PIN_RXD0   			GPIO_NUM_3
// #define PIN_TXD0   			GPIO_NUM_1
// #define PIN_RXD2   			GPIO_NUM_13
// #define PIN_TXD2   			GPIO_NUM_14
// #define PIN_INT_SDA			GPIO_NUM_21
// #define PIN_INT_SCL			GPIO_NUM_22
#define PIN_SDA    			GPIO_NUM_21
#define PIN_SCL    			GPIO_NUM_22

// PINS M5Core
// #define PIN_SCLK				GPIO_NUM_18
#define PIN_TILT			GPIO_NUM_3
// #define PIN_MISO				GPIO_NUM_19
// #define PIN_RXD0          	GPIO_NUM_3
// #define PIN_TXD0          	GPIO_NUM_1
// #define PIN_RXD2          	GPIO_NUM_16
// #define PIN_TXD2          	GPIO_NUM_17
// #define PIN_SDA           	GPIO_NUM_21
// #define PIN_SCL           	GPIO_NUM_22
#define PIN_BTN_A			GPIO_NUM_39
#define PIN_BTN_B 			GPIO_NUM_38
#define PIN_BTN_C 			GPIO_NUM_37
#define PIN_SPEAKER			GPIO_NUM_25

#endif // __CONFIG_H

