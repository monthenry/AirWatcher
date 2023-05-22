#include "Sensor.h"
#include <fstream>
#include <sstream>

map<string, Sensor*> Sensor::mapSensor ;

Sensor::Sensor(string id, double lat, double lng, bool func) {
    sensorID = id;
    latitude = lat;
    longitude = lng;
    functionning = func;
}

Sensor::Sensor() {
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

list<Measurement*> Sensor::getMeasurements() {
    return measurements;
}

void Sensor::addMeasurement(Measurement* m) {
    measurements.push_back(m);
}

void Sensor::setMeasurements(list<Measurement*> m) {
    measurements = m;
}

Sensor* Sensor::parseSensor(string line) {
    istringstream istream(line);
    string champ;

    getline(istream, champ, ';');
    string id = champ;

    getline(istream, champ, ';');
    double longitude = stod(champ);

    getline(istream, champ, ';');
    double lat = stod(champ);

    Sensor* s = new Sensor(id, lat, longitude, true);
    return s;
}
map<string, Sensor*> Sensor::getSensorMap(){
    return mapSensor;
}

bool Sensor::initSensor(string filename) {
    ifstream fichier(filename);
    bool done = fichier.good();
    cout<<done;
    string ligne;

    if (done) {
        while (getline(fichier, ligne)) {
                

            Sensor* sens = parseSensor(ligne);
            cout<<*sens<<endl;
            mapSensor.insert(pair<string, Sensor*>(sens->getSensorId(), sens));
        }
    }

    return done;
}

