#include "View.h"

int View::getUserChoice() {
    int choice;
    cout << "Please enter your choice: ";
    cin >> choice;
    cin.ignore(); // Ignore the newline character in the input buffer
    return choice;
}

void View::displayNotImplementedError() {
    cout << "---------------------------" << endl;
    cout << "Functionality not implemented yet" << endl;
    cout << "---------------------------" << endl;
    cout << endl;
}

void View::displayLogoutMessage() {
    cout << "---------------------------" << endl;
    cout << "Thanks for using AirWatcher ! " << endl;
    cout << "---------------------------" << endl;
    cout << endl;
}

void View::displayConnexionMenu() {
    cout << "---------------------------" << endl;
    cout << "Welcome to AirWatcher, select an action to perform" << endl;
    cout << "---------------------------" << endl;
    cout << "1. Create account" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << endl;
}

void View::displayAccountCreationMenu() {
    string username, password, confirmPassword;
    cout << "Please enter your username: ";
    getline(cin, username);
    cout << "Please enter a password: ";
    getline(cin, password);
    cout << "Please confirm your password: ";
    getline(cin, confirmPassword);

    
    cout << "Account created successfully!" << endl;
    cout << endl;
}

bool View::displayLoginMenu() {
    string username, password;
    cout << "Please enter your username: ";
    getline(cin, username);
    cout << "Please enter your password: ";
    getline(cin, password);


    cout << "Login successful! (Not implemented yet)" << endl;
    cout << endl;
    return true;
}

void View::displayActionMenu() {
    cout << endl;
    cout << "---------------------------" << endl;
    cout << "Here is the list of actions you can perform" << endl;
    cout << "---------------------------" << endl;
    cout << "0. Display all sensors" << endl;
    cout << "1. Manage users (not implemented)" << endl;
    cout << "2. Manage sensors (not implemented)" << endl;
    cout << "3. Retrieve account information (not implemented)" << endl;
    cout << "4. Request sensor's data analysis (not implemented)" << endl;
    cout << "5. Request global statistics in an area" << endl;
    cout << "6. Request air quality at a precise location (not implemented)" << endl;
    cout << "7. Request sensors ranking in similarity to a specific sensor" << endl;
    cout << "8. Request statistics for a cleaner (not implemented)" << endl;
    cout << "9. Toggle performance metrics (not implemented)" << endl;
    cout << endl;
}

void View::displayAllSensors(map<string, Sensor*> sensors) {
    cout << endl;
    cout << "------------------------------------------" << endl;
    cout << "SENSOR LIST" << endl;
    cout << "------------------------------------------" << endl;
    for(auto it=sensors.begin(); it != sensors.end(); ++it) {
        Sensor sensorToDisplay = *(it->second);
        cout << sensorToDisplay.getSensorId() << endl;
    }
    cout << "------------------------------------------" << endl;
    cout << endl;
}

list<string>* View::requestGlobalStatistics() {
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

    cout << endl;

    return params;
}

list<string>* View::requestSensorRanking() {
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

    cout << endl;
    
    return params;
}

void View::displayStats(std::map<std::string, std::tuple<int, int, int>>* mapMean) {
    for (std::map<std::string, std::tuple<int, int, int>>::iterator it = mapMean->begin(); it != mapMean->end(); ++it) {
        std::cout << it->first << " : mean = " << std::get<0>(it->second) << "; max = " << std::get<1>(it->second) << "; min = " << std::get<2>(it->second) << std::endl;
    }
}

void View::displaySensorRanking(string sensorID, int atmoIndex, list<pair<string, int>>* sensorRanked) {
    cout << endl;
    cout << "------------------------------------------" << endl;
    cout << "SENSOR SIMILAR TO " << sensorID << endl;
    cout << "------------------------------------------" << endl;
    for(auto it=sensorRanked->begin(); it != sensorRanked->end(); ++it) {
        if(it->first != "") {
            cout << "Sensor ID : " << it->first << " | " << "Atmo index : " << it->second << " | " << "Delta : " << abs(atmoIndex - it->second) << endl;
        }
    }
    cout << "------------------------------------------" << endl;
    cout << endl;   
}