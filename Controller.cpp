#include "Controller.h"

Controller::Controller() {

}

void Controller::initModel() {
    Sensor::initSensor("./data/sensors.csv");
    Attribute::initAttributes("./data/attributes.csv");
    Measurement::initMeasurements("./data/measurements.csv");
}


