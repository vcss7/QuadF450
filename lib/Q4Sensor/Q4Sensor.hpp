/**
 * @file Q4Sensor.hpp
 * @author Victor Solis
 */

namespace Q4
{

class Sensor
{
public:
    virtual void open ()  = 0;
    virtual void close () = 0;
    virtual void read ()  = 0;
    virtual void write () = 0;

    virtual ~Sensor () = default;
};

}  // namespace Q4
