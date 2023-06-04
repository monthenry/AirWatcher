#include "Controller.h"

/*----------------------------------------------------------------------------------------------------
INITIALISATION FUNCTION
----------------------------------------------------------------------------------------------------*/

Controller::Controller(){
}

void Controller::initModel() {
    Sensor::initSensor("./data/sensors.csv");
    Attribute::initAttributes("./data/attributes.csv");
    Measurement::initMeasurements("./data/measurements.csv");
}

/*----------------------------------------------------------------------------------------------------
MAIN PROCESS
----------------------------------------------------------------------------------------------------*/

void Controller::startController() {
    View::clearScreen();
    initModel();

    // Display functionality list and prompt user for choice
    int userChoice = -1;
    while (userChoice == -1 || userChoice != 4)
    {
        // Display action menu
        View::clearScreen();
        View::displayFunctionalityList();
        userChoice = View::getUserChoice();
        View::clearScreen();

        switch (userChoice)
        {
            case 0: {
                /* Display sensor list */
                map<string, Sensor*> sensorsList = Sensor::getSensorMap();
                View::displaySensorList(sensorsList);
                View::getEnterToContinue();
                break;
            }

            case 1: {
                /* Request for global statistics in an area */                
                list<string>* userInput = View::getAreaStatisticsInput();
                runAreaStatistics(userInput);
                View::getEnterToContinue();
                break;
    		}

            case 2: {
                /* Request for sensor ranking in similarity to a specified sensor */
                list<string>* userInput = View::getSensorRankingInput();
                runSensorRanking(userInput);
                View::getEnterToContinue();
                break;
            }

            case 3: {
                /* Launch tests */
                double test1_1 = Test1_AreaStatistics();
                View::getEnterToContinue();
                double test1_2 = Test2_AreaStatistics();
                View::getEnterToContinue();
                double test1_3 = Test3_AreaStatistics();
                View::getEnterToContinue();
                double test1_4 = Test4_AreaStatistics();
                View::getEnterToContinue();
                double test2_1 = Test1_SensorRanking();
                View::getEnterToContinue();
                double test2_2 = Test2_SensorRanking();
                View::getEnterToContinue();
                double test2_3 = Test3_SensorRanking();
                View::getEnterToContinue();
                double test2_4 = Test4_SensorRanking();
                View::getEnterToContinue();
                View::displayPerformanceTestResult(test1_1, test1_2, test1_3, test1_4, test2_1, test2_2, test2_3, test2_4);
                View::getEnterToContinue();
                break;
            }

            case 4: {
                // Display a message on user exiting the application
                View::displayTitleSeparator("Thanks for using AirWatcher ! ");
                break;
            }
            
            default: {
                // On wrong user input, display error and go back to menu
                View::displayErrorMessage("/!\\ Functionality not implemented yet /!\\");
                View::getEnterToContinue();
                break;
            }
        }
    }
}

/*----------------------------------------------------------------------------------------------------
CORE FUNCTIONALITY
----------------------------------------------------------------------------------------------------*/

map<string,tuple<int, int, int>> Controller::computeAreaStatistics(int x, int y, int d, time_t debut, time_t fin) {
    map<string, Sensor*> sensorMap = Sensor::getSensorMap();
    map<string, tuple<int,int,int> > mapMean;
    int cptO3 = 0, cptNO2 = 0, cptSO2 = 0, cptPM10 = 0;
    int sumO3 = 0, sumNO2 = 0, sumSO2 = 0, sumPM10=0;
    int minO3 = INT32_MAX, minSO2 = INT32_MAX, minNO2 = INT32_MAX, minPM10 = INT32_MAX;
    int maxO3 = 0, maxSO2 = 0, maxNO2 = 0, maxPM10 = 0;
    int compteur = 0;

    for ( map < string, Sensor* >::iterator it = sensorMap.begin ( ) ; it != sensorMap.end ( ) ; ++it ){
        if(it->second->getFunctionning() && sqrt(pow(it->second->getLatitude() - y, 2) + pow(it->second->getLongitude() - x, 2))<=d){
            list<Measurement*> m = it->second->getMeasurements();
            
            for (list<Measurement*>::iterator innerIt = m.begin(); innerIt != m.end(); ++innerIt) {
                if ((*innerIt)->getTime() < fin && (*innerIt)->getTime() > debut) {
                    compteur ++;

                    if((*innerIt)->getAttribute()->getAttributeId()=="O3"){
                        if((*innerIt)->getValue()>maxO3){
                            maxO3=(*innerIt)->getValue();
                        }
                        if((*innerIt)->getValue()<minO3){
                            minO3=(*innerIt)->getValue();
                        }
                        cptO3++;
                        sumO3+=(*innerIt)->getValue();
                    }

                    if((*innerIt)->getAttribute()->getAttributeId()=="NO2"){
                        if((*innerIt)->getValue()>maxNO2){
                            maxNO2=(*innerIt)->getValue();
                        }
                        if((*innerIt)->getValue()<minNO2){
                            minNO2=(*innerIt)->getValue();
                        }
                        cptNO2++;
                        sumNO2+=(*innerIt)->getValue();
                    }

                    if((*innerIt)->getAttribute()->getAttributeId()=="SO2"){
                        if((*innerIt)->getValue()>maxSO2){
                            maxSO2=(*innerIt)->getValue();
                        }
                        if((*innerIt)->getValue()<minSO2){
                            minSO2=(*innerIt)->getValue();
                        }
                        cptSO2++;
                        sumSO2+=(*innerIt)->getValue();
                    }

                    if((*innerIt)->getAttribute()->getAttributeId()=="PM10"){
                        if((*innerIt)->getValue()>maxPM10){
                            maxPM10=(*innerIt)->getValue();
                        }
                        if((*innerIt)->getValue()<minPM10){
                            minPM10=(*innerIt)->getValue();
                        }
                        cptPM10++;
                        sumPM10+=(*innerIt)->getValue();
                    }
                }
            }
        }
    }


    if(compteur != 0) {
        mapMean.insert(pair<string, tuple<int, int, int> >("O3", make_tuple((sumO3 / cptO3), maxO3, minO3)));
        mapMean.insert(pair<string, tuple<int, int, int> >("NO2", make_tuple((sumNO2 / cptNO2), maxNO2, minNO2)));
        mapMean.insert(pair<string, tuple<int, int, int> >("SO2", make_tuple((sumSO2 / cptSO2), maxSO2, minSO2)));
        mapMean.insert(pair<string, tuple<int, int, int> >("PM10", make_tuple((sumPM10 / cptPM10), maxPM10, minPM10)));
    }
  
    return mapMean;
}

void Controller::runAreaStatistics(list<string>* userInput){
    map<string,tuple<int, int, int> > mapMean;
    if (!userInput->empty()&& userInput->size() >= 5) {
        try {
            list<string>::iterator it = userInput->begin();
            int lat = stoi(*it);
            advance(it, 1);
            int longitude = stoi(*it);
            advance(it, 1);
            int radius = stoi(*it);
            advance(it, 1);
            time_t timeD = convertDateTimeToTimeT(*it);
            advance(it, 1);
            time_t timeF = convertDateTimeToTimeT(*it);

            if(timeD >= timeF) {
                View::displayErrorMessage("Beginning time is larger than ending time");
            } else if(timeD == 0 || timeF == 0) {
                View::displayErrorMessage("Wrong date format");
            } else {
                mapMean = computeAreaStatistics(lat, longitude,radius, timeD, timeF);

                if (mapMean.size() != 0)
                {
                    View::displayAreaStatistics(&mapMean);
                } else {
                    View::displayErrorMessage("There is no sensor data corresponding to your demand");
                }
            }
        } catch (const invalid_argument& e) {
            View::displayErrorMessage("Unable to convert the first element to an integer.");
        }
    } else {
        View::displayErrorMessage("The list of arguments is incomplete.");
    }
}

list<pair<string, int>>* Controller::computeSensorRanking(Sensor mySensor, time_t startTime, time_t endTime) {
    int mySensorAtmo = mySensor.getAtmoIndex(startTime, endTime);

    // Looping through the sensor map
    map<string, Sensor*> sensorsList = Sensor::getSensorMap();
    list<pair<string, int>>* rankedSensors = new list<pair<string, int>>(1);
    int value;

    if(mySensorAtmo != 0) {
        for (auto it = sensorsList.begin(); it != sensorsList.end(); ++it) {
            Sensor theSensor = *(it->second);
            int theSensorAtmo = theSensor.getAtmoIndex(startTime, endTime);
            if(theSensorAtmo != 0) {
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
        }
    }

    return rankedSensors;
}

void Controller::runSensorRanking(list<string>* userInput){
    if (!userInput->empty() && userInput->size() >= 3) {
        try {
            list<string>::iterator it = userInput->begin();

            string sensorID = *it;
            map<string, Sensor*> sensorsList = Sensor::getSensorMap();

            if(!(sensorsList.count(sensorID) > 0)) {
                View::displayErrorMessage("This sensor does not exist");
                return;
            }
            Sensor targetSensor = *(sensorsList[sensorID]);

            advance(it, 1);
            string startDate = *it;
            time_t start = convertDateTimeToTimeT(startDate);
            

            advance(it, 1);
            string endDate = *it;
            time_t end = convertDateTimeToTimeT(endDate);
            
            if(startDate >= endDate){
                View::displayErrorMessage("Beginning time is larger than ending time");
            } else if(start == 0 || end == 0) {
                View::displayErrorMessage("Wrong date format");
            } else{
                list<pair<string, int>>* rankedSensors = computeSensorRanking(targetSensor, start, end);
                if (rankedSensors->size() != 1)
                {
                    View::displaySensorRanking(sensorID, targetSensor.getAtmoIndex(start, end), rankedSensors);
                } else {
                    View::displayErrorMessage("There is no sensor data corresponding to your demand");
                }
            }
        } catch (const invalid_argument& e) {
            View::displayErrorMessage("Unable to convert the first element to an integer.");
        }
    } else {
        View::displayErrorMessage("The list of arguments is incomplete.");
    }
}

/*----------------------------------------------------------------------------------------------------
TOOLS
----------------------------------------------------------------------------------------------------*/

time_t Controller::convertDateTimeToTimeT(const string& dateTimeString) {
    tm timeStruct = {};
    istringstream ss(dateTimeString);
    ss >> get_time(&timeStruct, "%d/%m/%Y %H:%M:%S");
    if (ss.fail()) {
        View::displayErrorMessage("Error parsing date and time.");
        return 0; // Return 0 to indicate an error
    }

    time_t timeT = mktime(&timeStruct);
    if (timeT == -1) {
        View::displayErrorMessage("Error converting date and time to time_t.");
        return 0; // Return 0 to indicate an error
    }
    return timeT;   
}

/*----------------------------------------------------------------------------------------------------
TESTS
----------------------------------------------------------------------------------------------------*/

double Controller::Test1_AreaStatistics() {
    steady_clock::time_point start = steady_clock::now();

    View::displayTitleSeparator("Global statistics, Test 1 : \nInput : 44, 0, 5, 10/01/2019 12:00:00, 01/01/2019 12:00:00 \nExpected Output : Beginning time larger than ending time");
    list<string> stringList {"44", "0", "5", "10/01/2019 12:00:00", "01/01/2019 12:00:00"};
    runAreaStatistics(&stringList);

    steady_clock::time_point end = steady_clock::now();
    duration<double> duration = end - start;
    return duration.count();
}

double Controller::Test2_AreaStatistics() {
    steady_clock::time_point start = steady_clock::now();

    View::displayTitleSeparator("Global statistics, Test 2 : \nInput : 0, 0, 0, 01/01/2019 12:00:00, 10/01/2019 12:00:00 \nExpected Output : No sensor associated with input");
    list<string> stringList {"0", "0", "0", "01/01/2019 12:00:00", "10/01/2019 12:00:00"};
    runAreaStatistics(&stringList);

    steady_clock::time_point end = steady_clock::now();
    duration<double> duration = end - start;
    return duration.count();
}

double Controller::Test3_AreaStatistics() {
    steady_clock::time_point start = steady_clock::now();
    
    View::displayTitleSeparator("Global statistics, Test 3 : \nInput : 0, 0, 0, egfsgesgsegs, 10/01/2019 12:00:00 \nExpected Output : Date could not be parsed");
    list<string> stringList {"40", "4", "100", "egfsgesgsegs", "01/01/2500 12:00:00"};
    runAreaStatistics(&stringList);

    steady_clock::time_point end = steady_clock::now();
    duration<double> duration = end - start;
    return duration.count();
}

double Controller::Test4_AreaStatistics() {
    steady_clock::time_point start = steady_clock::now();

    View::displayTitleSeparator("Global statistics, Test 4 : \nInput : 0, 0, 0, 01/01/2019 12:00:00, 10/01/2019 12:00:00 \nExpected Output : mean, min and max over all measurements (wide timeframe and location)");
    list<string> stringList {"40", "4", "100", "01/01/1500 12:00:00", "01/01/2500 12:00:00"};
    runAreaStatistics(&stringList);

    steady_clock::time_point end = steady_clock::now();
    duration<double> duration = end - start;
    return duration.count();
}

double Controller::Test1_SensorRanking() {
    steady_clock::time_point start = steady_clock::now();

    View::displayTitleSeparator("SensorRanking, Test 1 : \nInput : Senseuuur0 01/01/1500 12:00:00 01/01/2500 12:00:00 \nExpected Output : Sensor does not exist");
    list<string> stringList {"Senseuuur0", "01/01/1500 12:00:00", "01/01/2500 12:00:00"};
    runSensorRanking(&stringList);

    steady_clock::time_point end = steady_clock::now();
    duration<double> duration = end - start;
    return duration.count();
}

double Controller::Test2_SensorRanking() {
    steady_clock::time_point start = steady_clock::now();

    View::displayTitleSeparator("SensorRanking, Test 2 : \nInput : Sensor0 01/01/2500 12:00:00 01/01/1500 12:00:00 \nExpected Output : Start date is larger than end date");
    list<string> stringList {"Sensor0", "01/01/2500 12:00:00", "01/01/1500 12:00:00"};
    runSensorRanking(&stringList);

    steady_clock::time_point end = steady_clock::now();
    duration<double> duration = end - start;
    return duration.count();
}

double Controller::Test3_SensorRanking() {
    steady_clock::time_point start = steady_clock::now();

    View::displayTitleSeparator("SensorRanking, Test 3 : \nInput : Sensor0 01/01/2010 10:00:00 01/01/2010 10:10:00 \nExpected Output : Sensor does not exist");
    list<string> stringList {"Sensor0", "01/01/2010 10:00:00", "01/01/2010 10:10:00"};
    runSensorRanking(&stringList);

    steady_clock::time_point end = steady_clock::now();
    duration<double> duration = end - start;
    return duration.count();
}

double Controller::Test4_SensorRanking() {
    steady_clock::time_point start = steady_clock::now();

    View::displayTitleSeparator("SensorRanking, Test 4 : \nInput : Sensor0 01/01/1500 12:00:00 01/01/2500 12:00:00 \nExpected Output : Sensor list ranked by similarity to Sensor0");
    list<string> stringList {"Sensor0", "01/01/1500 12:00:00", "01/01/2500 12:00:00"};
    runSensorRanking(&stringList);

    steady_clock::time_point end = steady_clock::now();
    duration<double> duration = end - start;
    return duration.count();
}