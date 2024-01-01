#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_BME280.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include "Adafruit_BME280.h"
#include "Adafruit_SSD1306.h"

// variables
const uint32_t LED_PIN = 13;

// functions prototypes
void scanI2CBus();

/* uncomment precompiler definitions as needed */
#define UTC602602_ENABLED     // display
//#define BNO055_ENABLED        // orienation
//#define BME280_ENABLED        // press/humid/temp

// display initialization
#ifdef UTC602602_ENABLED
const uint32_t SCREEN_WIDTH = 128;
const uint32_t SCREEN_HEIGHT = 32;
const int8_t OLED_RESET = -1;
const uint32_t SCREEN_ADDRESS = 0x3C;
Adafruit_SSD1306 utc602602(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// utc function prototypes
void init_utc602602();
void draw_line();
#endif

// orientation sensor initialization
#ifdef BNO055_ENABLED
// bno variable declarations
Adafruit_BNO055 bno055 = Adafruit_BNO055(55);
imu::Quaternion quat;

// bno function prototypes
void init_bno055();
bool read_bno055_data();
#endif

// press/humid/temp sensor initialization
#ifdef BME280_ENABLED
// bme variable declarations
Adafruit_BME280 bme280 = Adafruit_BME280();
// update to hPa of sea level for location and day for accurate altitude data
const float SEA_LEVEL_PRESSURE_HPA = 1013.25; 
float temp;
float pressure;
float humidity;
float altitude;

// bme function prototypes
void init_bme280();
bool read_bme280_data();
#endif

/***** setup *****/
void setup()
{
    pinMode(LED_PIN, OUTPUT);
    Wire.begin();
    Serial.begin(9600);

#ifdef UTC602602_ENABLED
    init_utc602602();
#endif
#ifdef BNO055_ENABLED
    init_bno055();
#endif
#ifdef BME280_ENABLED
    init_bme280();
#endif
    delay(1000);
    utc602602.clearDisplay();
    utc602602.setTextSize(1);
    utc602602.setTextColor(WHITE);
    utc602602.setCursor(0, 10);
    utc602602.print("Finished Setup!");
    utc602602.display();
    delay(100);
}

/***** loop *****/
void loop()
{
    digitalWrite(LED_PIN, millis() % 1000 > 500);

#ifdef BNO055_ENABLED
    read_bno055_data();
#endif
#ifdef BME280_ENABLED
    read_bme280_data();
#endif
}


// functions 
void scanI2CBus()
{
    byte error, address;

    for(address = 1; address < 127; address++)
    {
        digitalWrite(LED_PIN, millis() % 200 > 100);
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if(error == 0)
        {
            Serial.print("Device found at Address 0x");
        }
        else
        {
            Serial.print("No Device at Address 0x");
        }

        if(address < 16)
        {
            Serial.print("0");
        }
        Serial.println(address, HEX);

        delay(100);
    }
}

#ifdef UTC602602_ENABLED
void init_utc602602()
{
    while(!utc602602.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.print("UTC602602 Module not detected. Check your wiring or I2C ADDR!");
        delay(1000);
    }

    utc602602.drawPixel(10, 10, SSD1306_WHITE);
    utc602602.display();
    delay(100);
}

void draw_line()
{
}
#endif

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

