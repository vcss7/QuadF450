#include <Arduino.h>
#include <math.h>

/*************************************/
/* type definitions                  */
/*************************************/
typedef struct EulerAngle
{
    float yaw;
    float pitch;
    float roll;
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
