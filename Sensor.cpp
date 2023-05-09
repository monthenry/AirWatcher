#include "Sensor.h"
    
Sensor::Sensor(string id, double lat, double lng, bool func){
    sensorID = id;
    latitude = lat;
    longitude = lng;
    functionning = func;
}

Sensor::Sensor(){

}

string Sensor::getSensorId() {
    return sensorID;
}

double Sensor::getLongitude() {
    return longitude;
}
void Sensor::setLongitude(double lng) {
    longitude = lng;
}

double Sensor::getLatitude() {
    return latitude;
}

void Sensor::setLatitude(double lat) {

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

ostream& operator<< (ostream &flux, Sensor  &sensor){
    flux<<sensor.getSensorId()<<""<< sensor.getLatitude()<<";"<<sensor.getLatitude()<<""<<sensor.getFunctionning();
    return flux;
}
