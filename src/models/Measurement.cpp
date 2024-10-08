
#include "Measurement.h"

/*----------------------------------------------------------------------------------------------------
CONSTRUCTOR
----------------------------------------------------------------------------------------------------*/

Measurement::Measurement(){

}

Measurement::Measurement(time_t t, float val, Attribute* att, Sensor* s){
    time = t;
    value = val;
    attribute = att;
    sensor = s;
}

/*----------------------------------------------------------------------------------------------------
GETTER
----------------------------------------------------------------------------------------------------*/

float Measurement::getValue(){
    return value;
}

time_t Measurement::getTime(){
    return time;
}

Attribute* Measurement::getAttribute(){
    return attribute;
}

Sensor* Measurement::getSensor(){
    return sensor;
}

/*----------------------------------------------------------------------------------------------------
CORE FUNCTIONALITY
----------------------------------------------------------------------------------------------------*/

bool Measurement::initMeasurements(string filename) {
    ifstream fichier(filename);
    bool done = fichier.good();
    string ligne;

    if (done) {
        while (getline(fichier, ligne)) {
                
            Measurement* msrm = parseMeasurement(ligne);
            msrm->sensor->addMeasurement(msrm);
        }
    }

    return done;
}

Measurement* Measurement::parseMeasurement(string line) {
    istringstream istream(line);
    string champ;

    getline(istream, champ, ';');
    struct tm tm;
    strptime(champ.c_str(), "%F %H:%M:%S", &tm);
    time_t time = mktime(&tm);


    getline(istream, champ, ';');
    Sensor* sens = Sensor::getSensorMap()[champ];

    getline(istream, champ, ';');
    Attribute* attr = Attribute::getMapAttributes()[champ];

    getline(istream, champ, ';');
    float val = stof(champ);

    Measurement* m = new Measurement(time, val, attr, sens);
    return m;
}