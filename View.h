#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <map>

#include "Sensor.h"

using namespace std; 

class View {
public:
    // System call
    

    // User input
    static int getUserChoice();
    static void getEnterToContinue();
    static list<string>* getSensorRankingInput();
    static list<string>* getAreaStatisticsInput();

    // Display function
    static void clearScreen();
    static void displayTitleSeparator(string title);
    static void displayErrorMessage(string message);
    static void displayPerformanceTestResult(double test1_1, double test1_2, double test1_3, double test1_4, double test2_1, double test2_2, double test2_3, double test2_4);
    static void displayFunctionalityList();
    static void displaySensorList(map<string, Sensor*> sensors);
    static void displayAreaStatistics(map<string, tuple<int, int, int>>* mapMean);
    static void displaySensorRanking(string sensorID, int atmoIndex, list<pair<string, int>>* sensorRanked);
};

#endif  // VIEW_H
