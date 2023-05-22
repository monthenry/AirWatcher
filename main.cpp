// #include "Sensor.h"
// #include "Controller.h"
// #include "User.h"
// #include <string>
// #include <sstream>
// #include <iostream>
// #include <fstream>
// using namespace std;

// Sensor* parseSensor(string s);

// int main(int argc, char* argv[]) {
//     //cout.flush();
//     //Sensor *s = parseSensor("1;45;-1;");

//    // User *u= User::parseUser("User1;matheojtm;");

//     cout << "u->getUserID()" << endl;
//     cout << "u->getUserID()" << endl;
//     //cout << *s << endl;
    
//     // Controller ctrl;
//     // ctrl.initModel();

//     // cout << ctrl.getMapAttributes()["O3"]->getDescription() << endl;
//     // cout << ctrl.getMapAttributes()["SO2"]->getDescription() << endl;
//     // cout << ctrl.getMapAttributes()["NO2"]->getDescription() << endl;
//     // cout << ctrl.getMapAttributes()["PM10"]->getDescription() << endl;;

//     return 0;
// }


// Sensor* parseSensor(string line){


//     istringstream istream (line);
//     string champ;

//     getline(istream,champ,';');
//     string id = champ;
//     cout<<id<<endl;

//     getline(istream,champ,';');
//     double longitude = stod(champ);
//     cout<<longitude<<endl;

    
//     getline(istream,champ,';');
//     double lat=stod(champ);
//     cout<<lat<<endl;


//     Sensor *s = new Sensor(id, lat,longitude, true);
//     return s;
// }
#include <iostream>

int main() {
    std::cout << "Hello, world!" << std::endl;
    return 0;
}