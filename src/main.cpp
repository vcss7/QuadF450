#include "Teensy41PinMap.hpp"

#include <Arduino.h>
#include <I2CDevice.hpp>
#include <Peripheral.hpp>

// function prototypes
void initLed ();
void blinkLed ();

// setup
void setup ()
{
    initLed ();
}

// loop
void loop ()
{
    blinkLed ();
}

// function definitions
void initLed ()
{
    pinMode (LED_BUILTIN, OUTPUT);
}

void blinkLed ()
{
    static const uint16_t INTERVAL_MS = 1000;
    digitalWrite (LED_BUILTIN, millis () % (INTERVAL_MS * 2) > INTERVAL_MS);
}
