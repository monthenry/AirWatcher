#ifndef Controller_H
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
using namespace std::chrono;

class Controller {
    public:
        Controller();

        // main process
        void startController();

    private:
        // initialisation function
        void initModel();

        // core functionality
        map<string,tuple<int,int,int> > computeAreaStatistics(int x, int y,int d, time_t debut, time_t fin);
        void runAreaStatistics(list<string>* input);
        list<pair<string, int>>* computeSensorRanking(Sensor mySensor, time_t startTime, time_t endTime);
        void runSensorRanking(list<string>* input);

        // tools
        time_t convertDateTimeToTimeT(const std::string& dateTimeString);

        // Test function
        double Test1_AreaStatistics();
        double Test2_AreaStatistics();
        double Test3_AreaStatistics();
        double Test4_AreaStatistics();
        double Test1_SensorRanking();
        double Test2_SensorRanking();
        double Test3_SensorRanking();
        double Test4_SensorRanking();
};
#endif
