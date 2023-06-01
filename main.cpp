#include <string>
#include <tuple>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <functional>
#include "Sensor.h"
#include "Controller.h"
#include "User.h"
#include <ctime>
#include <math.h>
using namespace std;

Sensor* parseSensor(string s);
map<string,tuple<int,int,int> > statMean(int x, int y,int d, time_t debut, time_t fin);

void displayStats(std::map<std::string, std::tuple<int, int, int>>* mapMean) {
    for (std::map<std::string, std::tuple<int, int, int>>::iterator it = mapMean->begin(); it != mapMean->end(); ++it) {
        std::cout << it->first << " : mean = " << std::get<0>(it->second) << "; max = " << std::get<1>(it->second) << "; min = " << std::get<2>(it->second) << std::endl;
    }
}

template<typename F>
double measurePerformance(F&& func)
{
    // Start the timer
    auto startTime = std::chrono::high_resolution_clock::now();

    // Call the function
    std::forward<F>(func)();

    // End the timer and calculate the duration
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;

    // Return the duration in seconds
    return duration.count();
}

list<string>* requestGlobalStatistics() {
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

        return params;
    }



time_t convertDateTimeToTimeT(const std::string& dateTimeString) {
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




void Scenario3(list<string>* data){
    
    map<string,tuple<int, int, int> > mapMean;
    if (!data->empty()&& data->size() >= 5) {
        try {
            std::list<std::string>::iterator it = data->begin();
            int lat = std::stoi(*it);
            std::advance(it, 1);
            int longitude = std::stoi(*it);
            std::advance(it, 1);
            int radius =std::stoi(*it) ;
            std::advance(it, 1);
            time_t timeD=convertDateTimeToTimeT(*it);
            std::advance(it, 1);
            time_t timeF= convertDateTimeToTimeT(*it);

            if(timeD>= timeF){
                std::cerr << "Error: Beginning time is larger than ending time" << std::endl;
            }else{
                mapMean= statMean(lat, longitude,radius, timeD, timeF);
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: Unable to convert the first element to an integer." << std::endl;
        }
    } else {
        std::cout << "Error: The list of arguments is incomplete." << std::endl;
    }
    displayStats(&mapMean);
}






map<string,tuple<int, int, int> > statMean(int x, int y,int d, time_t debut, time_t fin){

    
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
void exampleFunction()
{
    // Perform some time-consuming task
    for (int i = 0; i < 1000000; ++i) {
        // Do some computation
    }
}
void Test2_Scenario3() {
    cout << "Test 2 of scenario 3: No sensor associated with input" << endl;
    std::list<std::string> stringList {"0", "0", "0", "01/01/2019 12:00:00", "10/01/2019 12:00:00"};
    Scenario3(&stringList);

}

void Test1_Scenario3() {
    cout << "Test 2 of scenario 3: Beginning time larger than ending time" << endl;
    std::list<std::string> stringList {"44", "0", "5", "10/01/2019 12:00:00", "01/01/2019 12:00:00"};
    Scenario3(&stringList);

}


int main(int argc, char* argv[]) {
    Controller c;
    c.initModel();
    Test2_Scenario3();
    Test1_Scenario3();
    double executionTime = measurePerformance(exampleFunction);
    
    // Print the execution time
    std::cout << "Execution time: " << executionTime << " seconds" << std::endl;
    

    return 0;

}