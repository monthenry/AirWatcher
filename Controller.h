#if ! defined ( Controller_H )
#define Controller_H

#include <string>
#include <tuple>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <functional>
#include <ctime>
#include <math.h>
#include <map>

#include "Attribute.h"
#include "Sensor.h"
#include "Measurement.h"
#include "View.h"
#include "Sensor.h"
#include "User.h"
#include "PrivateIndividual.h"

using namespace std;

class Controller {
    public: 
        Controller();

        void initController();
        void initModel();
        map<string,tuple<int,int,int> > statMean(int x, int y,int d, time_t debut, time_t fin);
        list<pair<string, int>>* getSensorRanking(Sensor mySensor, time_t startTime, time_t endTime);
        time_t convertDateTimeToTimeT(const std::string& dateTimeString);

        void Scenario3(list<string>* data);
        void Test1_Scenario3();
        void Test2_Scenario3();
        void Test1_Scenario1();
        void Test2_Scenario1();
};
#endif
