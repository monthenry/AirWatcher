#ifndef CONTROLLER_H
#define CONTROLLER_H

using namespace std;

#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "Measurement.h"
#include "Attribute.h"

class Controller {

    public:
        Controller();

        void initModel();

        map<string, Attribute*> getMapAttributes();

    private:
        // parsers
        Measurement* parseMeasurement(string line);
        Attribute* parseAttribute(string line);

        // file readers
        bool initMeasurements(string filename);
        bool initAttributes(string filename);

        map<string, Attribute*> mapAttributes;
        
};

#endif 