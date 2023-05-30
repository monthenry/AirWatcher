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

        static bool initMeasurements(string filename);


    private:
        static Measurement* parseMeasurement(string line);

        float value ;
        time_t time ;
        Attribute* attribute;
        Sensor* sensor;

        friend ostream& operator<<(ostream& os, const Measurement& msrm) {
            os << "Mesure du " << msrm.sensor->getSensorId() << " : " <<  msrm.value << " " << msrm.attribute->getAttributeId() << " à " << msrm.time;
            return os;
        }
};
#endif