#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include "Adafruit_BME280.h"

// variables
uint32_t led_pin = 13;

/* uncomment precompiler definitions as needed */
#define BNO055_ENABLED
#define BME280_ENABLED

// sensor initialization
#ifdef BNO055_ENABLED
// bno variable declarations
Adafruit_BNO055 bno055 = Adafruit_BNO055(55);
imu::Quaternion quat;

// bno functions declarations
void init_bno055();
bool read_bno055_data();
#endif

#ifdef BME280_ENABLED
// bme variable declarations
Adafruit_BME280 bme280 = Adafruit_BME280();
// update to hPa of sea level for location and day for accurate altitude data
const float SEA_LEVEL_PRESSURE_HPA = 1013.25; 
float temp;
float pressure;
float humidity;
float altitude;

// bme functions declarations
void init_bme280();
bool read_bme280_data();
#endif

/***** setup *****/
void setup()
{
    pinMode(led_pin, OUTPUT);
    Serial.begin(9600);

#ifdef BNO055_ENABLED
    init_bno055();
#endif
}

/***** loop *****/
void loop()
{
    digitalWrite(led_pin, millis() % 1000 > 500 ? true : false);

#ifdef BNO055_ENABLED
    read_bno055_data();
#endif
#ifdef BME280_ENABLED
    read_bme280_data();
#endif
}

// functions 
#ifdef BNO055_ENABLED
void init_bno055()
{
    while(!bno055.begin())
    {
        Serial.print("No BNO055 detected. Check your wiring or I2C ADDR!");
        delay(1000);
    }
    delay(100);

    bno055.setExtCrystalUse(true);
}

bool read_bno055_data()
{
    quat = bno055.getQuat();

    // TODO: check if it actually returns reads data
    return true;
}
#endif

#ifdef BME280_ENABLED
void init_bme280()
{
    while(!bme280.begin())
    {
        Serial.print("No BME280 detected. Check your wiring or I2C ADDR!");
        delay(1000);
    }
    delay(100);
}

bool read_bme280_data()
{
    temp = bme280.readTemperature();
    pressure = bme280.readPressure();
    humidity = bme280.readHumidity();
    altitude = bme280.readAltitude(SEA_LEVEL_PRESSURE_HPA);

    // TODO: check if it actually returns reads data
    return true;
}
#endif

