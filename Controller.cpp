
#include "Controller.h"

Controller::Controller(){
}

void Controller::initModel() {
    Sensor::initSensor("./data/sensors.csv");
    Attribute::initAttributes("./data/attributes.csv");
    Measurement::initMeasurements("./data/measurements.csv");
}

void Controller::initController() {
    initModel();

    int userChoice = -1;

    while (userChoice == -1)
    {
        // Display connexion menu
        View::displayConnexionMenu();
        userChoice = View::getUserChoice();
    }
    
    switch (userChoice)
    {
    case 1:
        // display account creation menu (not implemented dummy interface)
        View::displayAccountCreationMenu();
        break;
    case 2:
        // display login menu (not implemented dummy interface)
        View::displayLoginMenu();
        break;
    default:
        return;
        break;
    }

    // Display home menu (where user is presented with application function)
    userChoice = -1;
    while (userChoice == -1 || userChoice != 10)
    {
        // Display action menu
        View::displayActionMenu();
        userChoice = View::getUserChoice();

        switch (userChoice)
        {
            case 1:
                /* Manage users (not implemented)*/
                break;

            case 2:
                /* Manage sensors (not implemented)*/
                break;

            case 3:
                /* Retrieve account information (not implemented)*/
                break;

            case 4:
                /* Request sensor data analysis (not implemented)*/
                break;

            case 5:{
                /* Request for global statistics in an area */
                list<string>* userRequest = View::requestAreaStatistics();
                break;
    		}
            case 6:
                /* Request for air quality at a precise location (not implemented)*/
                break;

            case 7:
                /* Request for sensor ranking in similarity to a specified sensor */
                break;

            case 8:
                /* Request statistics for a cleaner (not implemented)*/
                break;

            case 9:
                /* Toggle performance metrics (not implemented)*/
                break;
            
            default:
                View::displayNotImplementedError();
                break;
        }
    }
    
    // Display a message on user exiting the application
    View::displayLogoutMessage();
}

list<pair<string, int>>* Controller::getSensorRanking(Sensor mySensor, time_t startTime, time_t endTime) {
    int mySensorAtmo = mySensor.getAtmoIndex(startTime, endTime);

    // Looping through the sensor map
    map<string, Sensor*> sensors = Sensor::getSensorMap();
    list<pair<string, int>>* rankedSensors = new list<pair<string, int>>(sensors.size());
    int value;

    for (auto it = sensors.begin(); it != sensors.end(); ++it) {
        Sensor theSensor = *(it->second);
        int theSensorAtmo = theSensor.getAtmoIndex(startTime, endTime);
        value = abs(mySensorAtmo - theSensorAtmo);
        for (auto it2 = rankedSensors->begin(); it2 != rankedSensors->end(); ++it2) {
            int currentSensorAtmo = it2->second;
            if(abs(mySensorAtmo-currentSensorAtmo) > value){
                pair<string, int> newSensor;
                newSensor.first = theSensor.getSensorId();
                newSensor.second = theSensorAtmo;
                rankedSensors->insert(it2, newSensor);
                break;
            }
        }
    }

    return rankedSensors;
}
