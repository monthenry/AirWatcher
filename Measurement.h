#if ! defined ( MEASUREMENT_H )
#define MEASUREMENT_H

#include <ctime> 
#include "Attribute.h"
#include "Sensor.h"


using namespace std;

class Sensor;
class Measurement {
    public: 

        Measurement(time_t t, float val, Attribute* att, Sensor* s);
        time_t getTime();
        float getValue();
        Attribute* getAttribute();
        Sensor* getSensor();


    private: 
        float value ;
        time_t time ;
        Attribute* attribute;
        Sensor* sensor;
};
#endif