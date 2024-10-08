#include "View.h"

/*----------------------------------------------------------------------------------------------------
INPUT FUNCTION
----------------------------------------------------------------------------------------------------*/

int View::getUserChoice() {
    int choice;
    cout << "Please enter your choice : ";
    cin >> choice;
    
    if(!cin) {
        cin.clear();
        cin.ignore(1024, '\n');
        return 999;
    }

    cin.ignore(); // Ignore the newline character in the input buffer
    return choice;
}

void View::getEnterToContinue() {
    displayTitleSeparator("Press Enter to continue...");
    cin.ignore();
    clearScreen();
}

list<string>* View::getAreaStatisticsInput() {
    list<string>* params = new list<string>();
    cout << "To request for global statistics in an area provide the location, radius, and period of interest." << endl;

    cout << "Latitude : ";
    string latitude;
    getline(cin, latitude);
    params->push_back(latitude);

    cout << "Longitude : ";
    string longitude;
    getline(cin, longitude);
    params->push_back(longitude);

    cout << "Radius : ";
    string radius;
    getline(cin, radius);
    params->push_back(radius);

    cout << "Begining date with hour minute and second (dd/MM/YYYY HH:mm:ss) : ";
    string begin;
    getline(cin, begin);
    params->push_back(begin);

    cout << "Finishing date with hour minute and second (dd/MM/YYYY HH:mm:ss) : ";
    string finish;
    getline(cin, finish);
    params->push_back(finish);

    return params;
}


list<string>* View::getSensorRankingInput() {
    list<string>* params = new list<string>();

    cout << "Request sensors ranking in similarity to a specific sensor : ";
    string sensorID;
    getline(cin, sensorID);
    params->push_back(sensorID);

    cout << "Begining date with hour minute and second (dd/MM/YYYY HH:mm:ss) : ";
    string begin;
    getline(cin, begin);
    params->push_back(begin);

    cout << "Finishing date with hour minute and second (dd/MM/YYYY HH:mm:ss) : ";
    string finish;
    getline(cin, finish);
    params->push_back(finish);
    
    return params;
}

/*----------------------------------------------------------------------------------------------------
DISPLAY FUNCTION
----------------------------------------------------------------------------------------------------*/

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

void View::displayTitleSeparator(string title) {
    cout << "--------------------------------------------------------------------" << endl;
    cout << title << endl;
    cout << "--------------------------------------------------------------------" << endl;
}

void View::displayErrorMessage(string message) {
    cout << "--------------------------------------------------------------------" << endl;
    cerr << "Error : " << message << endl;
    cout << "--------------------------------------------------------------------" << endl;
}

void View::displayPerformanceTestResult(double test1_1, double test1_2, double test1_3, double test1_4, double test2_1, double test2_2, double test2_3, double test2_4) {
    displayTitleSeparator("PERFORMANCE VALUES OF PREVIOUS TESTS (in seconds)");
    cout << fixed << setprecision(8);
    cout << "|-------------------------------------------------|" << endl;
    cout << "| Test number | Area Statistics | Sensors ranking |" << endl;
    cout << "|-------------|-----------------|-----------------|" << endl;
    cout << "|            1|       "<< test1_1 <<"|       "<< test2_1 <<"|" << endl;
    cout << "|-------------|-----------------|-----------------|" << endl;
    cout << "|            2|       "<< test1_2 <<"|       "<< test2_2 <<"|" << endl;
    cout << "|-------------|-----------------|-----------------|" << endl;
    cout << "|            3|       "<< test1_3 <<"|       "<< test2_3 <<"|" << endl;
    cout << "|-------------|-----------------|-----------------|" << endl;
    cout << "|            4|       "<< test1_4 <<"|       "<< test2_4 <<"|" << endl;
    cout << "|-------------------------------------------------|" << endl;
}

void View::displayFunctionalityList() {
    displayTitleSeparator("FUNCTIONALITY LIST");
    cout << "Choose the action to perform : " << endl;
    cout << "0. Display all sensors" << endl;
    cout << "1. Request global statistics in an area" << endl;
    cout << "2. Request sensors ranking in similarity to a specific sensor" << endl;
    cout << "3. Test all functionality" << endl;
    cout << "4. Exit AirWatcher" << endl;
    cout << "--------------------------------------------------------------------" << endl << endl;
}

void View::displaySensorList(map<string, Sensor*> sensors) {
    displayTitleSeparator("SENSOR LIST");

    for(auto it=sensors.begin(); it != sensors.end(); ++it) {
        Sensor sensorToDisplay = *(it->second);
        cout << sensorToDisplay.getSensorId() << endl;
    }
}

void View::displayAreaStatistics(std::map<std::string, std::tuple<int, int, int>>* mapMean) {
    displayTitleSeparator("STATISTICS IN THE SELECTED AREA AND TIMEFRAME");

    for (std::map<std::string, std::tuple<int, int, int>>::iterator it = mapMean->begin(); it != mapMean->end(); ++it) {
        std::cout << it->first << " : mean = " << std::get<0>(it->second) << "; max = " << std::get<1>(it->second) << "; min = " << std::get<2>(it->second) << std::endl;
    }
}

void View::displaySensorRanking(string sensorID, int atmoIndex, list<pair<string, int>>* sensorRanked) {
    string title = "SIMILARITY RANKING TO SENSOR : " + sensorID;
    displayTitleSeparator(title);

    for(auto it=sensorRanked->begin(); it != sensorRanked->end(); ++it) {
        if(it->first != "") {
            cout << "Sensor ID : " << it->first << " | " << "Atmo index : " << it->second << " | " << "Delta : " << abs(atmoIndex - it->second) << endl;
        }
    }
}