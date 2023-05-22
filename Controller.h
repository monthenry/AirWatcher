#ifndef CONTROLLER_H
#define CONTROLLER_H

using namespace std;

#include "Measurement.h"
#include "Attribute.h"

class Controller {

    public:
        Controller();

        void initModel();

    private:
        // parsers
        Measurement* parseMeasurement(string line);

        // file readers
        bool initMeasurements(string filename);
        
};

#endif 