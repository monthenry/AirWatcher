#include "Sensor.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

Sensor* parseSensor(string s);

int main() {
    //placeholder

    Sensor *s = parseSensor("1;45;-1;");
    cout<<*s;
    // cout<<s->getSensorId()<<endl;
    // cout<<s->getLongitude()<<endl;
    // cout<<s->getLatitude()<<endl;
    
    // ifstream fichier("./data/sensors.csv");
    // string ligne;
    // if(fichier){
    //     while( not fichier.eof() and getline(fichier,ligne) ){
    //         Sensor *s = parseSensor(ligne);
    //         cout<<s->getSensorId()<<endl;
    //         cout<<s->getLongitude()<<endl;
    //         cout<<s->getLatitude()<<endl;
    //     }
    // }
    


    
    


    return 0;
}


Sensor* parseSensor(string line){


    istringstream istream (line);
    string champ;

    getline(istream,champ,';');
    string id = champ;
    cout<<id<<endl;

    getline(istream,champ,';');
    double longitude = stod(champ);
    cout<<longitude<<endl;

    
    getline(istream,champ,';');
    double lat=stod(champ);
    cout<<lat<<endl;


    Sensor *s = new Sensor(id, lat,longitude, true);
    return s;
}
