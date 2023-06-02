#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include <list>
#include <map>

#include "Sensor.h"

using namespace std; 

class View {
public:
    static int getUserChoice();
    static void displayNotImplementedError();
    static void displayLogoutMessage();
    static void displayConnexionMenu();
    static void displayAccountCreationMenu();
    static bool displayLoginMenu();
    static void displayActionMenu();
    static void displayAllSensors(map<string, Sensor*> sensors);

    static list<string>* requestSensorRanking();
    static list<string>* requestGlobalStatistics();

    static void displayStats(map<string, tuple<int, int, int>>* mapMean);
    static void displaySensorRanking(string sensorID, int atmoIndex, list<pair<string, int>>* sensorRanked);
};

#endif  // VIEW_H
