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
    // System call
    static void clearScreen();

    // User input
    static int getUserChoice();
    static void getEnterToContinue();
    static list<string>* getSensorRankingInput();
    static list<string>* getAreaStatisticsInput();

    // Display function
    static void displayTitleSeparator(string title);
    static void displayEndSeparator();
    static void displayNotImplementedError();
    static void displayLogoutMessage();
    static void displayFunctionalityList();
    static void displaySensorList(map<string, Sensor*> sensors);
    static void displayAreaStatistics(map<string, tuple<int, int, int>>* mapMean);
    static void displaySensorRanking(string sensorID, int atmoIndex, list<pair<string, int>>* sensorRanked);
};

#endif  // VIEW_H
