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
    string ligne;

    if (done) {
        while (getline(fichier, ligne)) {
                
            Sensor* sens = parseSensor(ligne);
            mapSensor.insert(pair<string, Sensor*>(sens->getSensorId(), sens));
        }
    }

    return done;
}

int Sensor::getAtmoIndex(time_t start, time_t end) {
    int cptO3=0, cptNO2=0, cptSO2=0, cptPM10=0;
    int sumO3=0, sumNO2=0, sumSO2=0, sumPM10=0;

    for (list<Measurement*>::iterator it = measurements.begin(); it != measurements.end(); ++it) {
        if ((*it)->getTime() < start || (*it)->getTime() > end) {
            continue;
        }

        if((*it)->getAttribute()->getAttributeId()=="O3"){
            cptO3++;
            sumO3+=(*it)->getValue();
        } else if((*it)->getAttribute()->getAttributeId()=="NO2"){
            cptNO2++;
            sumNO2+=(*it)->getValue();
        } else if((*it)->getAttribute()->getAttributeId()=="SO2"){
            cptSO2++;
            sumSO2+=(*it)->getValue();
        } else if((*it)->getAttribute()->getAttributeId()=="PM10"){
            cptPM10++;
            sumPM10+=(*it)->getValue();
        }
    }

    int meanO3 = sumO3/cptO3, meanNO2 = sumNO2/cptNO2, meanSO2 = sumSO2/cptSO2, meanPM10 = sumPM10/cptPM10, atmoIndex = 0;

    if (meanO3 >= 240 || meanSO2 >= 500 || meanNO2 >= 400 || meanPM10 >= 80) {
        atmoIndex = 10;
    } else if (meanO3 >= 210 || meanSO2 >= 400 || meanNO2 >= 275 || meanPM10 >= 65) {
        atmoIndex = 9;
    } else if (meanO3 >= 180 || meanSO2 >= 300 || meanNO2 >= 200 || meanPM10 >= 50) {
        atmoIndex = 8;
    } else if (meanO3 >= 150 || meanSO2 >= 250 || meanNO2 >= 165 || meanPM10 >= 42) {
        atmoIndex = 7;
    } else if (meanO3 >= 130 || meanSO2 >= 200 || meanNO2 >= 135 || meanPM10 >= 35) {
        atmoIndex = 6;
    } else if (meanO3 >= 105 || meanSO2 >= 160 || meanNO2 >= 110 || meanPM10 >= 28) {
        atmoIndex = 5;
    } else if (meanO3 >= 80 || meanSO2 >= 120 || meanNO2 >= 85 || meanPM10 >= 21) {
        atmoIndex = 4;
    } else if (meanO3 >= 55 || meanSO2 >= 80 || meanNO2 >= 55 || meanPM10 >= 14) {
        atmoIndex = 3;
    } else if (meanO3 >= 30 || meanSO2 >= 40 || meanNO2 >= 30 || meanPM10 >= 7) {
        atmoIndex = 2;
    } else if (meanO3 >= 0 || meanSO2 >= 0 || meanNO2 >= 0 || meanPM10 >= 0) {
        atmoIndex = 1;
    }

    return atmoIndex;
}