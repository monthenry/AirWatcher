#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include <list>

class View {
public:
    static void displayMenu();
    static int getUserChoice() ;
    static void createAccount();
    static bool login();
    static void displayActionsMenu();
   
    static void manageUsers();
    static void manageSensors();
    static void retrieveAccountInformation();
    static void requestSensorDataAnalysis();
    static std::list<std::string>* requestGlobalStatistics();
    static void requestAirQualityAtLocation();
    static string requestSensorRanking();
    static void requestCleanerStatistics();
    static void togglePerformanceMetrics();
};

#endif  // VIEW_H
