#include <Arduino.h>
#include <I2CDevice.hpp>
#include <Logger.hpp>
#include <Peripheral.hpp>

const Q4::Logger::usb_serial_baud_t USB_BAUD = 115200;
Q4::Logger logger (&Serial, USB_BAUD);

// function prototypes
void initLed ();
void blinkLed ();

// setup
void setup ()
{
    delay (1000);
    logger.print ("Begin setup\r\n");
    initLed ();
    logger.print ("Setup complete\r\n");
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
