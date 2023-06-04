#include "View.h"

#ifdef _WIN32
    #include <windows.h>
    void View::clearScreen() {
        system("cls");
    }
#elif __linux__ || __APPLE__
    void View::clearScreen() {
        system("clear");
    }
#endif

int View::getUserChoice() {
    int choice;
    cout << "Please enter your choice : ";
    cin >> choice;
    cin.ignore(); // Ignore the newline character in the input buffer
    return choice;
}

void View::getEnterToContinue() {
    displayTitleSeparator("Press Enter to continue...");
    cin.ignore();
    clearScreen();
}

void View::displayTitleSeparator(string title) {
    cout << "--------------------------------------------------------------------" << endl;
    cout << title << endl;
    cout << "--------------------------------------------------------------------" << endl;
}

void View::displayEndSeparator() {
    cout << "--------------------------------------------------------------------" << endl << endl;
}

void View::displayNotImplementedError() {
    displayTitleSeparator("/!\\ Functionality not implemented yet /!\\");
    cout << endl;
}

void View::displayLogoutMessage() {
    displayTitleSeparator("Thanks for using AirWatcher ! ");
    cout << endl;
}

void View::displayFunctionalityList() {
    displayTitleSeparator("FUNCTIONALITY LIST");
    cout << "Choose the action to perform : " << endl;
    cout << "0. Display all sensors" << endl;
    cout << "1. Request global statistics in an area" << endl;
    cout << "2. Request sensors ranking in similarity to a specific sensor" << endl;
    cout << "3. Test all functionality" << endl;
    cout << "4. Exit AirWatcher" << endl;
    displayEndSeparator();
}

void View::displaySensorList(map<string, Sensor*> sensors) {
    displayTitleSeparator("SENSOR LIST");
    for(auto it=sensors.begin(); it != sensors.end(); ++it) {
        Sensor sensorToDisplay = *(it->second);
        cout << sensorToDisplay.getSensorId() << endl;
    }
    displayEndSeparator();
}

list<string>* View::getAreaStatisticsInput() {
    list<string>* params = new list<string>();
    cout << "To request for global statistics in an area provide the location, radius, and period of interest." << endl;

    cout << "Latitude: ";
    string latitude;
    getline(cin, latitude);
    params->push_back(latitude);

    cout << "Longitude: ";
    string longitude;
    getline(cin, longitude);
    params->push_back(longitude);

    cout << "Radius: ";
    string radius;
    getline(cin, radius);
    params->push_back(radius);

    cout << "Begining date with hour minute and second (dd/MM/YYYY HH:mm:ss)";
    string begin;
    getline(cin, begin);
    params->push_back(begin);

    cout << "Finishing date with hour minute and second (dd/MM/YYYY HH:mm:ss) ";
    string finish;
    getline(cin, finish);
    params->push_back(finish);

    displayEndSeparator();

    return params;
}

list<string>* View::getSensorRankingInput() {
    list<string>* params = new list<string>();

    cout << "Request sensors ranking in similarity to a specific sensor:";
    string sensorID;
    getline(cin, sensorID);
    params->push_back(sensorID);

    cout << "Begining date with hour minute and second (dd/MM/YYYY HH:mm:ss)";
    string begin;
    getline(cin, begin);
    params->push_back(begin);

    cout << "Finishing date with hour minute and second (dd/MM/YYYY HH:mm:ss) ";
    string finish;
    getline(cin, finish);
    params->push_back(finish);

    displayEndSeparator();
    
    return params;
}

void View::displayAreaStatistics(std::map<std::string, std::tuple<int, int, int>>* mapMean) {
    displayTitleSeparator("STATISTICS IN THE SELECTED AREA AND TIMEFRAME");
    for (std::map<std::string, std::tuple<int, int, int>>::iterator it = mapMean->begin(); it != mapMean->end(); ++it) {
        std::cout << it->first << " : mean = " << std::get<0>(it->second) << "; max = " << std::get<1>(it->second) << "; min = " << std::get<2>(it->second) << std::endl;
    }
    displayEndSeparator();
}

void View::displaySensorRanking(string sensorID, int atmoIndex, list<pair<string, int>>* sensorRanked) {
    string title = "SIMILARITY RANKING TO SENSOR : " + sensorID;
    displayTitleSeparator(title);
    for(auto it=sensorRanked->begin(); it != sensorRanked->end(); ++it) {
        if(it->first != "") {
            cout << "Sensor ID : " << it->first << " | " << "Atmo index : " << it->second << " | " << "Delta : " << abs(atmoIndex - it->second) << endl;
        }
    }
    displayEndSeparator(); 
}