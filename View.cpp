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
    cout << "Functionality not implemented yet";
    cout << "---------------------------" << endl;
}

void View::displayLogoutMessage() {
    cout << "---------------------------" << endl;
    cout << "Thanks for using AirWatcher ! ";
    cout << "---------------------------" << endl;
}

void View::displayConnexionMenu() {
    cout << "Welcome to AirWatcher, select an action to perform:" << endl;
    cout << "1. Create account" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
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
    
}

bool View::displayLoginMenu() {
    string username, password;
    cout << "Please enter your username: ";
    getline(cin, username);
    cout << "Please enter your password: ";
    getline(cin, password);

    // Perform login authentication logic here

    // ...

    cout << "Login successful!" << endl;
    return true;
}

void View::displayActionMenu() {
    cout << "Here is the list of actions you can perform:" << endl;
    cout << "1. Manage users" << endl;
    cout << "2. Manage sensors" << endl;
    cout << "3. Retrieve account information" << endl;
    cout << "4. Request sensor's data analysis" << endl;
    cout << "5. Request global statistics in an area" << endl;
    cout << "6. Request air quality at a precise location" << endl;
    cout << "7. Request sensors ranking in similarity to a specific sensor" << endl;
    cout << "8. Request statistics for a cleaner" << endl;
    cout << "9. Toggle performance metrics" << endl;
}

void View::manageUsers() {
    cout << "Manage users:" << endl;
    cout << "To manage users, please enter the corresponding number to the action you want to perform and press Enter:" << endl;
    cout << "1. Add a user" << endl;
    cout << "2. Edit a user" << endl;
    cout << "3. Delete a user" << endl;
    cout << endl;
    
    int action;
    cout << "Please enter your choice: ";
    cin >> action;
    cin.ignore(); // Ignore the newline character in the input buffer

    // Perform the chosen action
    switch (action) {
        case 1:
            // Add a user logic
            cout << "Adding a user..." << endl;
            break;
        case 2:
            // Edit a user logic
            cout << "Editing a user..." << endl;
            break;
        case 3:
            // Delete a user logic
            cout << "Deleting a user..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}

list<string>* View::requestAreaStatistics() {
    list<string>* params = new list<string>();

    cout << "To request for global statistics in an area, enter '5' and press Enter," << endl;
    cout << "then provide the location, radius, and period of interest." << endl;

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

    cout << "Period: ";
    string period;
    getline(cin, period);
    params->push_back(period);
    return params;
}

void View::displayAreaStatistics() {
    // DISPLAY AREA STATISTICS HERE
}

string requestSensorRanking() {
    cout << "Request sensors ranking in similarity to a specific sensor:" << endl;
    // Prompt the user for sensor ID
    string sensorID;
    cout << "Enter sensor ID: ";
    cin >> sensorID;
    cout << endl;
    return sensorID;
}

void displaySensorRanking() {
    // DISPLAY SENSOR RANKING HERE
}

// --------------Not implemented--------------------

void manageSensors() {
    cout << "Manage sensors:" << endl;
    cout << "To manage sensors, please enter the corresponding number to the action you want to perform and press Enter:" << endl;
    cout << "1. Add a sensor" << endl;
    cout << "2. Edit a sensor" << endl;
    cout << "3. Delete a sensor" << endl;
    cout << endl;
    
    int action;
    cout << "Please enter your choice: ";
    cin >> action;
    cin.ignore(); // Ignore the newline character in the input buffer

    // Perform the chosen action
    switch (action) {
        case 1:
            // Add a sensor logic
            cout << "Adding a sensor..." << endl;
            break;
        case 2:
            cout << "Editing a sensor..." << endl;
            break;
        case 3:
            cout << "Deleting a sensor..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}
void View::retrieveAccountInformation() {
    cout << "Retrieve account information:" << endl;
    // Logic to retrieve and display account information
    cout << "Your username is: johndoe" << endl;
    cout << "Your user privilege: private user" << endl;
    cout << "Your number of points: 5" << endl;
    cout << endl;
}

void View::requestSensorDataAnalysis() {
    cout << "Request sensor's data analysis:" << endl;
    cout << "sensor ID: 12345" << endl;
    // Logic to perform sensor data analysis
    cout << "Performing sensor data analysis..." << endl;
    cout << endl;
}


void View::requestAirQualityAtLocation() {
    cout << "Request for air quality at a precise location:" << endl;
    // Prompt the user for location
    string latitude, longitude;
    cout << "latitude: ";
    cin >> latitude;
    cout << "longitude: ";
    cin >> longitude;
    cout << endl;
    // Logic to retrieve and display air quality at the specified location
    cout << "Retrieving air quality at location..." << endl;
    cout << endl;
}

string requestSensorRanking() {
    cout << "Request sensors ranking in similarity to a specific sensor:" << endl;
    // Prompt the user for sensor ID
    string sensorID;
    cout << "Enter sensor ID: ";
    cin >> sensorID;
    cout << endl;
    // Logic to retrieve and display sensor ranking
    cout << "Retrieving sensor ranking..." << endl;
    cout << endl;
    return sensorID;
}

void requestCleanerStatistics() {
    cout << "Request statistics for a cleaner:" << endl;
    // Prompt the user for cleaner ID
    string cleanerID;
    cout << "cleaner ID: ";
    cin >> cleanerID;
    cout << endl;
    // Logic to retrieve and display cleaner statistics
    cout << "Retrieving cleaner statistics..." << endl;
    cout << endl;
}

void togglePerformanceMetrics() {
    cout << "Toggle performance metrics:" << endl;
    // Logic to toggle performance metrics

    cout << "Toggling performance metrics activated" << endl;
    cout << endl;
}

