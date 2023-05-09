#ifndef SENSOR_H
#define SENSOR_H

using namespace std;

#include <string>

class Sensor {
    public:
        Sensor(string id, int lng, int lat, bool func);

        string getSensorId();

        int getLongitude();
        void setLongitude(int lng);
        
        int getLatitude();
        void setLatitude(int lat);

        bool getFunctionning();
        void setFunctionning(bool func);

    private:
        string sensorID;
        int latitude;
        int longitude;
        bool functionning;
};

#endif