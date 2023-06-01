
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
                Sensor sensorToRank = Sensor::getSensorMap.find(View::getSensorID());
                time_t start = convertDateTimeToTimeT();
                time_t end = convertDateTimeToTimeT();
                list<pair<string, int>>* rankedSensors = getSensorRanking(sensorToRank, start, end);
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

time_t Controller::convertDateTimeToTimeT(const std::string& dateTimeString) {
    std::tm timeStruct = {};
    std::istringstream ss(dateTimeString);
    ss >> std::get_time(&timeStruct, "%d/%m/%Y %H:%M:%S");
    if (ss.fail()) {
        std::cerr << "Error parsing date and time." << std::endl;
        return 0; // Return 0 to indicate an error
    }

    std::time_t timeT = std::mktime(&timeStruct);
    if (timeT == -1) {
        std::cerr << "Error converting date and time to time_t." << std::endl;
        return 0; // Return 0 to indicate an error
    }
    return timeT;   
}

map<string,tuple<int, int, int> > Controller::statMean(int x, int y,int d, time_t debut, time_t fin){

    
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
        std::cerr<<"Error: There is no sensor data corresponding to your demand"<<std::endl;

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
            std::list<std::string>::iterator it = data->begin();
            int lat = std::stoi(*it);
            std::advance(it, 1);
            int longitude = std::stoi(*it);
            std::advance(it, 1);
            int radius = std::stoi(*it) ;
            std::advance(it, 1);
            time_t timeD = convertDateTimeToTimeT(*it);
            std::advance(it, 1);
            time_t timeF = convertDateTimeToTimeT(*it);

            if(timeD>= timeF){
                std::cerr << "Error: Beginning time is larger than ending time" << std::endl;
            }else{
                mapMean = statMean(lat, longitude,radius, timeD, timeF);
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: Unable to convert the first element to an integer." << std::endl;
        }
    } else {
        std::cout << "Error: The list of arguments is incomplete." << std::endl;
    }
    View::displayStats(&mapMean);
}

void Controller::Test1_Scenario3() {
    cout << "Test 2 of scenario 3: Beginning time larger than ending time" << endl;
    std::list<std::string> stringList {"44", "0", "5", "10/01/2019 12:00:00", "01/01/2019 12:00:00"};
    Scenario3(&stringList);

}

void Controller::Test2_Scenario3() {
    cout << "Test 2 of scenario 3: No sensor associated with input" << endl;
    std::list<std::string> stringList {"0", "0", "0", "01/01/2019 12:00:00", "10/01/2019 12:00:00"};
    Scenario3(&stringList);
}