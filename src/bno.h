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

/*************************************/
/* euler and quaternion functions    */
/*************************************/
Quaternion eulerToQuaternion (EulerAngle euler);
EulerAngle quaternionToEuler (Quaternion quat);

/*************************************/
/* imu functions                     */
/*************************************/
bool initImuBno055 ();
bool readImuBno055 ();

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

bool initImuBno055 ()
{
    return false;
}

bool readImuBno055 ()
{
    return false;
}
