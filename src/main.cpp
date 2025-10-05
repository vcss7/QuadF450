#include "Adafruit_BME280.h"
#include "Adafruit_BNO055.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_Sensor.h"
#include "Arduino.h"
#include "Wire.h"

// variables

// functions prototypes
void scanI2CBus ();

/* uncomment precompiler definitions as needed */
// #define UTC602602_ENABLED     // display
// #define BNO055_ENABLED        // 9-axis orienation
// #define BME280_ENABLED        // press/humid/temp
// #define ULTIMATEGPS_ENABLED   // gps

// display initialization
#ifdef UTC602602_ENABLED
constexpr byte UTC602602_ADDRESS = 0x3C;
constexpr uint32_t SCREEN_WIDTH  = 128;
constexpr uint32_t SCREEN_HEIGHT = 32;
constexpr int8_t OLED_RESET      = -1;
Adafruit_SSD1306 utc602602 (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// utc function prototypes
bool init_utc602602 ();
void print_sensors_initialized (bool bno_init, bool bme_init, bool gps_init);
#endif

// orientation sensor
#ifdef BNO055_ENABLED
// bno variable declarations
constexpr byte BNO055_ADDRESS = 0x28;
Adafruit_BNO055 bno055        = Adafruit_BNO055 (BNO055_ADDRESS);
imu::Quaternion quat;

// bno function prototypes
bool init_bno055 ();
bool read_bno055_data ();
#endif

// press/humid/temp sensor
#ifdef BME280_ENABLED
// bme variable declarations
// BME280_ADDRESS defined in Adafruit_BME280.h as 0x77
Adafruit_BME280 bme280 = Adafruit_BME280 ();
// update to hPa of sea level for location and day for accurate altitude data
constexpr float SEA_LEVEL_PRESSURE_HPA = 1013.25;
float temp;
float pressure;
float humidity;
float altitude;

// bme function prototypes
bool init_bme280 ();
bool read_bme280_data ();
#endif

/***** setup *****/
void setup ()
{
    pinMode (LED_BUILTIN, OUTPUT);
    Wire.begin ();
    Serial1.begin (9600);

    bool bno055_initialized      = false;
    bool bme280_initialized      = false;
    bool ultimategps_initialized = false;

#ifdef UTC602602_ENABLED
    init_utc602602 ();
#endif
#ifdef BNO055_ENABLED
    bno055_initilized = init_bno055 ();
#endif
#ifdef BME280_ENABLED
    bme280_initialized = init_bme280 ();
#endif
#ifdef ULTIMATEGPS_ENABLED
    // Serial1.write("PMTK314,0,10,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0");
    if (Serial1.available () > 0)
    {
        ultimategps_initialized = true;
    }
#endif

#ifdef UTC602602_ENABLED
    print_sensors_initialized (bno055_initialized, bme280_initialized,
                               ultimategps_initialized);
#endif
    delay (1000);
}

/***** loop *****/
void loop ()
{
    digitalWrite (LED_BUILTIN, millis () % 1000 > 500);

    // scanI2CBus();

#ifdef BNO055_ENABLED
    read_bno055_data ();
#endif
#ifdef BME280_ENABLED
    read_bme280_data ();
#endif
#ifdef ULTIMATEGPS_ENABLED
    if (Serial1.available ())
    {
#ifdef UTC602602_ENABLED
        utc602602.clearDisplay ();
        utc602602.setTextSize (1);
        utc602602.setCursor (0, 0);
        utc602602.setTextColor (WHITE);
        utc602602.print ("Serial1 available");
#endif
    }
#endif
}

// functions
void scanI2CBus ()
{
    byte error, address;

    for (address = 1; address < 127; address++)
    {
        digitalWrite (LED_BUILTIN, millis () % 200 > 100);
        Wire.beginTransmission (address);
        error = Wire.endTransmission ();

        if (error == 0)
            Serial.printf ("Device found at Address 0x%02X\r\n", address);
        else
            Serial.printf ("No Device at Address 0x%02X\r\n", address);

        delay (100);
    }
}

#ifdef UTC602602_ENABLED
bool init_utc602602 ()
{
    while (!utc602602.begin (SSD1306_SWITCHCAPVCC, UTC602602_ADDRESS))
    {
        Serial.printf ("UTC602602 Module not detected. Check your wiring or"
                      + " I2C ADDR!\r\n");
        delay (1000);
    }

    // some defaults
    utc602602.clearDisplay ();
    utc602602.setTextSize (1);
    utc602602.setTextColor (WHITE);
    utc602602.setCursor (0, 0);
    utc602602.print ("UTC Ready!");
    utc602602.display ();
    delay (100);

    return true;
}

void print_sensors_initialized (bool bno_init, bool bme_init, bool gps_init)
{
    int16_t cursor_x = 0, cursor_y = 0;

    utc602602.clearDisplay ();
    utc602602.setTextSize (1);
    utc602602.setTextColor (WHITE);
    utc602602.setCursor (cursor_x, cursor_y);
    utc602602.print ("SENSORS INITIALIZED");

#ifdef BNO055_ENABLED
    if (bno_init)
    {
        cursor_y += 10;
        utc602602.setCursor (cursor_x, cursor_y);
        utc602602.print ("BNO055 Initialized!");
    }
#endif
#ifdef BME280_ENABLED
    if (bme_init)
    {
        cursor_y += 10;
        utc602602.setCursor (cursor_x, cursor_y);
        utc602602.print ("BME280 Initialized!");
    }
#endif
#ifdef ULTIMATEGPS_ENABLED
    if (gps_init)
    {
        cursor_y += 10;
        utc602602.setCursor (cursor_x, cursor_y);
        utc602602.print ("UltimateGPS Initialized!");
    }
#endif

    utc602602.display ();
}
#endif

#ifdef BNO055_ENABLED
bool init_bno055 ()
{
    while (!bno055.begin ())
    {
        Serial.print ("No BNO055 detected. Check your wiring or I2C ADDR!");
        delay (1000);
    }
    delay (100);

    bno055.setExtCrystalUse (true);

    return true;
}

bool read_bno055_data ()
{
    quat = bno055.getQuat ();

    // TODO: check if it reads data
    return true;
}
#endif

#ifdef BME280_ENABLED
bool init_bme280 ()
{
    while (!bme280.begin ())
    {
        Serial.print ("No BME280 detected. Check your wiring or I2C ADDR!");
        delay (1000);
    }
    delay (100);

    return true;
}

bool read_bme280_data ()
{
    temp     = bme280.readTemperature ();
    pressure = bme280.readPressure ();
    humidity = bme280.readHumidity ();
    altitude = bme280.readAltitude (SEA_LEVEL_PRESSURE_HPA);

    // TODO: check if it reads data
    return true;
}
#endif
