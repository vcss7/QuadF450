#include <Arduino.h>
#include <UltimateGPS.h>
#include <unity.h>

void setUp (void)
{
    // set stuff up here
    Serial.begin (115200);
}

void tearDown (void)
{
    // clean stuff up here
}

// test function prototypes
void test_calculateChecksumXor ();
void test_hasValidXorChecksum ();

int main (int argc, char **argv)
{
    UNITY_BEGIN ();

    RUN_TEST (test_calculateChecksumXor);
    RUN_TEST (test_hasValidXorChecksum);

    UNITY_END ();
}

void test_calculateChecksumXor ()
{
    vcss::UltimateGPS gps = vcss::UltimateGPS (SERIAL_PORT_HARDWARE);

    // setup test cases
    const char *testString1 = "PMTK605";
    const char *testString2 = "PMTK869,2,0";
    const char *testString3 = "PMTK223,1,25,180000,60000";

    // expected results
    const uint8_t expectedResult1 = 0x31;
    const uint8_t expectedResult2 = 0x37;
    const uint8_t expectedResult3 = 0x38;

    // run function
    uint8_t result1 = gps.calculateXorChecksum (testString1);
    uint8_t result2 = gps.calculateXorChecksum (testString2);
    uint8_t result3 = gps.calculateXorChecksum (testString3);

    // asserts
    TEST_ASSERT_TRUE (result1 == expectedResult1);
    TEST_ASSERT_TRUE (result2 == expectedResult2);
    TEST_ASSERT_TRUE (result3 == expectedResult3);
}

void test_hasValidXorChecksum ()
{
    vcss::UltimateGPS gps = vcss::UltimateGPS (SERIAL_PORT_HARDWARE1);

    // setup test cases
    const char *testString1 = "$PMTK530,0*28\r\n";
    const char *testString2 = "$PMTK226,3,30*4\r\n";
    const char *testString3 = "$PMTK225,0*2B\r\n";

    // run function
    bool result1 = gps.hasValidXorChecksum (testString1);
    bool result2 = gps.hasValidXorChecksum (testString2);
    bool result3 = gps.hasValidXorChecksum (testString3);

    // asserts
    TEST_ASSERT_TRUE (result1);
    TEST_ASSERT_TRUE (result2);
    TEST_ASSERT_TRUE (result3);
}