#include "Sensor.h"
    
Sensor::Sensor(string id, int lat, int lng, bool func) {
    sensorID = id;
    lat = latitude;
    longitude = lng;
    functionning = func;
}

Sensor::Sensor(){

}

string Sensor::getSensorId() {
    return sensorID;
}

int Sensor::getLongitude() {
    return longitude;
}
void Sensor::setLongitude(int lng) {
    longitude = lng;
}

int Sensor::getLatitude() {
    return latitude;
}

void Sensor::setLatitude(int lat) {
    latitude = lat;
}

bool Sensor::getFunctionning() {
    return functionning;
}

void Sensor::setFunctionning(bool func) {
    functionning = func;
}

list<Measurement*> Sensor::getMeasurements(){
    return measurements;
}


void Sensor::setMeasurements(list<Measurement*> m){
    measurements=m;
}