#include <string>
#include <tuple>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Sensor.h"
#include "Controller.h"
#include "User.h"
#include <ctime>
#include <math.h> 
using namespace std;

Sensor* parseSensor(string s);
map<string,tuple<int,int,int> > statMean(int x, int y,int d, time_t debut, time_t fin);

int main(int argc, char* argv[]) {
    Controller c;
    c.initModel();
    map<string,tuple<int, int, int> > mapMean =statMean(44,0,5,0,time(nullptr));
    for ( map < string, tuple<int,int,int> >::iterator it = mapMean.begin ( ) ; it != mapMean.end ( ) ; ++it ){
        cout << it->first << " : mean = " << get<0>(it->second) <<  "; max=" << get<1>(it->second) << "; min=" << get<2>(it->second) << endl;
    }
    return 0;
}


map<string,tuple<int, int, int> > statMean(int x, int y,int d, time_t debut, time_t fin){
    
    map<string, Sensor*> sensorMap = Sensor::getSensorMap();
    map<string, tuple<int,int,int> > mapMean;
    int cptO3=0,cptNO2=0,cptSO2=0, cptPM10=0;
    int sumO3=0,sumNO2=0,sumSO2=0,sumPM10=0;
    int minO3=INT32_MAX,minSO2=INT32_MAX,minNO2=INT32_MAX,minPM10=INT32_MAX;
    int maxO3=0, maxSO2=0,maxNO2=0,maxPM10=0;


    for ( map < string, Sensor* >::iterator it = sensorMap.begin ( ) ; it != sensorMap.end ( ) ; ++it ){
    //     cout<<(*it->second)<<endl;
    //     cout<<(sqrt(pow(it->second->getLatitude() - y, 2) + pow(it->second->getLongitude() - x, 2)))<<endl;
        if(it->second->getFunctionning() && sqrt(pow(it->second->getLatitude() - y, 2) + pow(it->second->getLongitude() - x, 2))<=d){
            //cout<<it->second;
            list<Measurement*> m = it->second->getMeasurements();
            for (list<Measurement*>::iterator innerIt = m.begin(); innerIt != m.end(); ++innerIt) {
                if ((*innerIt)->getTime() < fin && (*innerIt)->getTime() > debut) {
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



    // mapMean.insert(pair<string,tuple<int,int,int> >("O3",tuple<int,int,int>((sumO3/cptO3),maxO3,minO3)));
    // mapMean.insert(pair<string,tuple<int,int,int> >("NO2",tuple<int,int,int>((sumNO2/cptNO2),maxNO2,minNO2)));
    // mapMean.insert(pair<string,tuple<int,int,int> >("SO2",tuple<int,int,int>((sumSO2/cptSO2),maxSO2,minSO2)));
    // mapMean.insert(pair<string,tuple<int,int,int> >("PM10",tuple<int,int,int>((sumPM10/cptPM10),maxPM10,minPM10)));

    mapMean.insert(pair<string, tuple<int, int, int> >("O3", make_tuple((sumO3 / cptO3), maxO3, minO3)));
    mapMean.insert(pair<string, tuple<int, int, int> >("NO2", make_tuple((sumNO2 / cptNO2), maxNO2, minNO2)));
    mapMean.insert(pair<string, tuple<int, int, int> >("SO2", make_tuple((sumSO2 / cptSO2), maxSO2, minSO2)));
    mapMean.insert(pair<string, tuple<int, int, int> >("PM10", make_tuple((sumPM10 / cptPM10), maxPM10, minPM10)));
    
    return mapMean;
} 
