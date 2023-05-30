#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include <list>

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

    static list<std::string>* requestAreaStatistics();
    static void displayAreaStatistics();

    static string requestSensorRanking();
    static void displaySensorRanking();

    // ------------Not implemented----------------
    static void manageUsers();
    static void manageSensors();
    static void retrieveAccountInformation();
    static void requestSensorDataAnalysis();
    static void requestAirQualityAtLocation();
    static void requestCleanerStatistics();
    static void togglePerformanceMetrics();
};

#endif  // VIEW_H
