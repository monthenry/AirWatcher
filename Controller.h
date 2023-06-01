#if ! defined ( Controller_H )
#define Controller_H

#include <ctime> 
#include <iostream>
#include <utility>
#include <string>

#include "Attribute.h"
#include "Sensor.h"
#include "Measurement.h"
#include "User.h"
#include "PrivateIndividual.h"
#include "View.h"

using namespace std;

class Controller {
    public: 
        Controller();
        void initController();

    public:
        void initModel();
        list<pair<string, int>>* getSensorRanking(Sensor mySensor, time_t startTime, time_t endTime);
};
#endif
