#ifndef SENSOR_H
#define SENSOR_H

using namespace std;

#include <string>
#include <list>
#include "Measurement.h"
using namespace std;

class Measurement;
class Sensor {
    public:
        Sensor(string id, int lng, int lat, bool func);
        Sensor();

        string getSensorId();

        int getLongitude();
        void setLongitude(int lng);
        
        int getLatitude();
        void setLatitude(int lat);

        bool getFunctionning();
        void setFunctionning(bool func);

    
        list<Measurement*> getMeasurements();
        void setMeasurements(list<Measurement*> m);

        

    private:
        string sensorID;
        int latitude;
        int longitude;
        bool functionning;
        list<Measurement*> measurements;
};

#endif