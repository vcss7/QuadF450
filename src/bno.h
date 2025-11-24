#include <Arduino.h>
#include <math.h>

/*************************************/
/* IMU Instructions                  */
/*************************************/
// Calibrate the Accelerometer
// Calibrate the Magnetometer
// Calibrate the Gyroscope

/*************************************/
/* IMU Conventions/Behavior          */
/*************************************/
// Rotation Angle Conventions
// ====================================
// Pitch +180 to -180 (clockwise increase)
// Roll -90 to 90 (forward inclination increase)
// Yaw 0 to 360 (clockwise increase)

/*************************************/
/* type definitions                  */
/*************************************/
typedef struct EulerAngle
{
    float pitch;
    float roll;
    float yaw;
} EulerAngle;

typedef struct Quaternion
{
    float w;
    float x;
    float y;
    float z;
} Quaternion;

enum BNO055__OpMode : uint8_t
{
    CONFIGMODE   = 0x00,  // setup and calibration
    ACCONLY      = 0x01,  // accelerometer only
    MAGONLY      = 0x02,  // magnetometer only
    GYROONLY     = 0x03,  // gyrpscope only
    ACCMAG       = 0x04,  // accelerometer + magenetometer
    ACCGYRO      = 0x05,  // accelerometer + gyroscope
    MAGGYRO      = 0x06,  // magnetometer + gyroscope
    AMG          = 0x07,  // accelerometer + magnetometer + gyroscope
    IMU          = 0x08,  // IMU fusion (no magnetometer)
    COMPASS      = 0x09,  // Compass fusion
    M4G          = 0x0A,  // Magnetometer for gaming
    NDOF_FMC_OFF = 0x0B,  // 9DOF without fast mag calibration
    NDOF         = 0x0C,  // Full 9DOF sensor fusion
};

typedef uint8_t bno_op_mode_t;

struct OpModeAlgoFreq
{
    bno_op_mode_t opMode;
    uint8_t freq;
};

/*************************************/
/* euler and quaternion functions    */
/*************************************/
Quaternion eulerToQuaternion (EulerAngle euler);
EulerAngle quaternionToEuler (Quaternion quat);

/*************************************/
/* imu functions                     */
/*************************************/
bool bno055__init ();
bool bno055__setOpMode ();
bool bno055__read ();

/*************************************/
/* function implementations          */
/*************************************/
Quaternion eulerToQuaternion (EulerAngle euler)
{
    Quaternion quat = {0, 0, 0, 0};

    return quat;
}

EulerAngle quaternionToEuler (Quaternion quat)
{
    EulerAngle angles = {0, 0, 0};

    return angles;
}

bool bno055__init ()
{
    // at this point, the IMU is assumed to be powered and properly connected
    // this function is to verify communication and do some basic setup to make
    // the IMU usable (note: this function will NOT configure the IMU)
    return false;
}

bool bno055__setOpMode ()
{
    return false;
}

bool bno055__read ()
{
    return false;
}
