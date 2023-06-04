#include "Controller.h"

Controller::Controller(){
}

void Controller::initModel() {
    Sensor::initSensor("./data/sensors.csv");
    Attribute::initAttributes("./data/attributes.csv");
    Measurement::initMeasurements("./data/measurements.csv");
}

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
                map<string, Sensor*> sensors = Sensor::getSensorMap();
                View::displaySensorList(sensors);
                View::getEnterToContinue();
                break;
            }

            case 1: {
                /* Request for global statistics in an area */                
                list<string>* data = View::getAreaStatisticsInput();
                Scenario3(data);
                View::getEnterToContinue();
                break;
    		}

            case 2: {
                /* Request for sensor ranking in similarity to a specified sensor */
                list<string>* userInput = View::getSensorRankingInput();

                auto it = userInput->begin();

                string sensorID = *it;
                map<string, Sensor*> sensors = Sensor::getSensorMap();
                Sensor targetSensor = *(sensors[sensorID]);

                advance(it, 1);
                string startDate = *it;
                time_t start = convertDateTimeToTimeT(startDate);

                advance(it, 1);
                string endDate = *it;
                time_t end = convertDateTimeToTimeT(endDate);
                
                list<pair<string, int>>* rankedSensors = computeSensorRanking(targetSensor, start, end);
                View::displaySensorRanking(sensorID, targetSensor.getAtmoIndex(start, end), rankedSensors);
                View::getEnterToContinue();
                break;
            }

            case 3: {
                /* Launch tests */
                Test1_Scenario3();
                View::getEnterToContinue();
                Test2_Scenario3();
                View::getEnterToContinue();
                break;
            }

            case 4: {
                // Display a message on user exiting the application
                View::displayLogoutMessage();
                break;
            }
            
            default: {
                // On wrong user input, display error and go back to menu
                View::displayNotImplementedError();
                View::getEnterToContinue();
                break;
            }
        }
    }
}

list<pair<string, int>>* Controller::computeSensorRanking(Sensor mySensor, time_t startTime, time_t endTime) {
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

time_t Controller::convertDateTimeToTimeT(const string& dateTimeString) {
    tm timeStruct = {};
    istringstream ss(dateTimeString);
    ss >> get_time(&timeStruct, "%d/%m/%Y %H:%M:%S");
    if (ss.fail()) {
        cerr << "Error parsing date and time." << endl;
        return 0; // Return 0 to indicate an error
    }

    time_t timeT = mktime(&timeStruct);
    if (timeT == -1) {
        cerr << "Error converting date and time to time_t." << endl;
        return 0; // Return 0 to indicate an error
    }
    return timeT;   
}

map<string,tuple<int, int, int> > Controller::computeAreaStatistics(int x, int y, int d, time_t debut, time_t fin){
    map<string, Sensor*> sensorMap = Sensor::getSensorMap();
    map<string, tuple<int,int,int> > mapMean;
    int cptO3=0,cptNO2=0,cptSO2=0, cptPM10=0;
    int sumO3=0,sumNO2=0,sumSO2=0,sumPM10=0;
    int minO3=INT32_MAX,minSO2=INT32_MAX,minNO2=INT32_MAX,minPM10=INT32_MAX;
    int maxO3=0, maxSO2=0,maxNO2=0,maxPM10=0;
    int compteur =0;

    for ( map < string, Sensor* >::iterator it = sensorMap.begin ( ) ; it != sensorMap.end ( ) ; ++it ){
    //     cout<<(*it->second)<<endl;
    //     cout<<(sqrt(pow(it->second->getLatitude() - y, 2) + pow(it->second->getLongitude() - x, 2)))<<endl;
        if(it->second->getFunctionning() && sqrt(pow(it->second->getLatitude() - y, 2) + pow(it->second->getLongitude() - x, 2))<=d){
            //cout<<it->second;
            list<Measurement*> m = it->second->getMeasurements();
            
            for (list<Measurement*>::iterator innerIt = m.begin(); innerIt != m.end(); ++innerIt) {
                if ((*innerIt)->getTime() < fin && (*innerIt)->getTime() > debut) {
                    compteur ++;
                    //cout<<(*innerIt)->getAttribute()->getAttributeId()<<endl;
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


    if(compteur==0){
        cerr<<"Error: There is no sensor data corresponding to your demand"<<endl;

    }else{
        mapMean.insert(pair<string, tuple<int, int, int> >("O3", make_tuple((sumO3 / cptO3), maxO3, minO3)));
        mapMean.insert(pair<string, tuple<int, int, int> >("NO2", make_tuple((sumNO2 / cptNO2), maxNO2, minNO2)));
        mapMean.insert(pair<string, tuple<int, int, int> >("SO2", make_tuple((sumSO2 / cptSO2), maxSO2, minSO2)));
        mapMean.insert(pair<string, tuple<int, int, int> >("PM10", make_tuple((sumPM10 / cptPM10), maxPM10, minPM10)));
    
    }
  
    return mapMean;
}

void Controller::Scenario3(list<string>* data){
    map<string,tuple<int, int, int> > mapMean;
    if (!data->empty()&& data->size() >= 5) {
        try {
            list<string>::iterator it = data->begin();
            int lat = stoi(*it);
            advance(it, 1);
            int longitude = stoi(*it);
            advance(it, 1);
            int radius = stoi(*it);
            advance(it, 1);
            time_t timeD = convertDateTimeToTimeT(*it);
            advance(it, 1);
            time_t timeF = convertDateTimeToTimeT(*it);

            if(timeD >= timeF){
                cerr << "Error: Beginning time is larger than ending time" << endl;
            }else{
                mapMean = computeAreaStatistics(lat, longitude,radius, timeD, timeF);
            }
        } catch (const invalid_argument& e) {
            cout << "Error: Unable to convert the first element to an integer." << endl;
        }
    } else {
        cout << "Error: The list of arguments is incomplete." << endl;
    }
    View::displayAreaStatistics(&mapMean);
}

void Controller::Test1_Scenario3() {
    View::displayTitleSeparator("Global statistics, Test 1 : Beginning time larger than ending time");
    list<string> stringList {"44", "0", "5", "10/01/2019 12:00:00", "01/01/2019 12:00:00"};
    Scenario3(&stringList);
    View::displayEndSeparator();
}

void Controller::Test2_Scenario3() {
    View::displayTitleSeparator("Global statistics, Test 2 : No sensor associated with input");
    list<string> stringList {"0", "0", "0", "01/01/2019 12:00:00", "10/01/2019 12:00:00"};
    Scenario3(&stringList);
    View::displayEndSeparator();
}