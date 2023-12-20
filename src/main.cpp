#include "Arduino.h"

uint32_t led_pin = 13;

void setup()
{
    pinMode(led_pin, OUTPUT);
}

void loop()
{
    digitalWrite(led_pin, true);
    delay(1000);
    digitalWrite(led_pin, false);
    delay(1000);
}

