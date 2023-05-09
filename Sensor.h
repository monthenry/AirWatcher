#ifndef SENSOR_H
#define SENSOR_H

using namespace std;

#include <string>
#include<iostream>




class Sensor {
    public:
        Sensor(string id, double lng, double lat, bool func);

        string getSensorId();

        double getLongitude();
        void setLongitude(double lng);
        
        double getLatitude();
        void setLatitude(double lat);

        bool getFunctionning();
        void setFunctionning(bool func);

    private:
        string sensorID;
        double latitude;
        double longitude;
        bool functionning;

        friend std::ostream& operator<<(std::ostream& os, const Sensor& sensor);
};

std::ostream& operator<<(std::ostream& os, const Sensor& sensor) {
    os << sensor.sensorID << ", longitude=" << sensor.longitude << ", latitude=" << sensor.latitude <<" functionning : "<< sensor.functionning;
    return os;
}


#endif