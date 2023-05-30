#ifndef SENSOR_H
#define SENSOR_H

using namespace std;

#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <iostream>
#include <sstream>
#include "Measurement.h"
#include <map>


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
        static map<string, Sensor*> getSensorMap();

        static bool initSensor(string filename);
    
        list<Measurement*> getMeasurements();
        void setMeasurements(list<Measurement*> m);   
        void addMeasurement(Measurement* m);

        int getAtmoIndex(time_t start, time_t end);

    private:
        static Sensor* parseSensor(string s);
        string sensorID;
        double latitude;
        double longitude;
        bool functionning;
        list<Measurement*> measurements;
        static map<string, Sensor*> mapSensor;

        friend ostream& operator<<(ostream& os, const Sensor& sensor) {
            os << sensor.sensorID << ", longitude=" << sensor.longitude << ", latitude=" << sensor.latitude <<" functionning : "<< sensor.functionning;
            return os;
        }

};

#endif