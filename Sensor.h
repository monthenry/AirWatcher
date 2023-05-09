#ifndef SENSOR_H
#define SENSOR_H

using namespace std;

#include <string>
#include <list>
#include "Measurement.h"
#include<iostream>

class Measurement;
class Sensor {
    public:

        Sensor();
        Sensor(string id, double lng, double lat, bool func);

        string getSensorId();

        double getLongitude();
        void setLongitude(double lng);
        
        double getLatitude();
        void setLatitude(double lat);

        bool getFunctionning();
        void setFunctionning(bool func);

    
        list<Measurement*> getMeasurements();
        void setMeasurements(list<Measurement*> m);   
        void addMeasurement(Measurement* m);

    private:
        string sensorID;
        double latitude;
        double longitude;
        bool functionning;
        list<Measurement*> measurements;

        friend ostream& operator<<(ostream& os, const Sensor& sensor) {
            os << sensor.sensorID << ", longitude=" << sensor.longitude << ", latitude=" << sensor.latitude <<" functionning : "<< sensor.functionning;
            return os;
        }

};

#endif