#include <Arduino.h>

#include "config.h"
#include "globals.h"
#include "settings.h"
#include "screens.h"

// #include "UNIT_HBRIDGE.h"

//#include "tools-log.h"

void halt(const char*);

uint32_t scan_keys();

time_t _update = 0;

void updateMotorValues()
{
	for (size_t i = 0; i < NUMBER_OF_CHANNELS; i++)
	{
		float vin = drvs[i]->getAnalogInput(_8bit);
		vin_raw[i] = vin / 254.0f * 3.3f / 0.09f;
	} 
};

void setup()
{
	Serial.begin(115200);

    // Init IO
	digitalWrite(PIN_SPEAKER, LOW);
	pinMode(PIN_SPEAKER, OUTPUT);
	pinMode(PIN_BTN_A, INPUT);
	pinMode(PIN_BTN_B, INPUT);
	pinMode(PIN_BTN_C, INPUT);

    // Start up GUI
	gui.begin();

	// Initialize sensors etc
	int i2cAdress = 0x20;

	for(int i = 0; i < NUMBER_OF_CHANNELS; i++)
	{
		drvs[i]->begin(&Wire, i2cAdress, GPIO_NUM_21, GPIO_NUM_22, 400000L);
		i2cAdress++;
		motorSpeed[i] = DEFAULT_SPEED;
		delayMicroseconds(500);
		drvs[i]->setDriverSpeed8Bits(motorSpeed[i] * SPEED_MULTIPLIER);		
	};

	for(int i = 0; i < NUMBER_OF_CHANNELS; i++)
	{
		

		if(drvs[i]->getDriverSpeed8Bits() != 125)
		{
			drvs[i]->setDriverSpeed8Bits(motorSpeed[i] * SPEED_MULTIPLIER);	
			Serial.printf("i2c adress %d has motor speed of %d \n", drvs[i]->getI2CAddress(), drvs[i]->getDriverSpeed8Bits());

		};
	
	};
	
    // Bootstrap
    ScreenPtr scr = std::make_shared<BootScreen>(gui);
    gui.pushScreen(scr);
	
};

void loop()
{
	time_t now = millis();
	if(now < _update)updateMotorValues();
	_update = now + I2C_LOOP_MS;

    soogh_event_t e = static_cast<soogh_event_t>(key2event(scan_keys()));
	gui.handle(e);

	setman.loop();
	gui.loop();
};

void halt(const char* error)
{
	gui.showMessage("HALT:", error);
	// DBG("HALT: %s", error);
	while(true)
		gui.loop();
};

uint32_t scan_keys()
{
	// Read current states
	uint32_t pressed = KEY_NONE;
	if(digitalRead(PIN_BTN_A) == LOW)
		pressed |= KEY_A;
	if(digitalRead(PIN_BTN_B) == LOW)
		pressed |= KEY_B;
	if(digitalRead(PIN_BTN_C) == LOW)
		pressed |= KEY_C;
	// if(digitalRead(PIN_POWERINT) == LOW)
	// 	pressed |= KEY_P;
	return pressed;
};
