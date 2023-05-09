
#include "Measurement.h"
#include <iostream>


float Measurement::getValue(){
    return value;
}

time_t Measurement::getTime(){
    return time;
}

Attribute* Measurement::getAttribute(){
    return attribute;
}

Sensor* Measurement::getSensor(){
    return sensor;
}

Measurement::Measurement(time_t t, float val, Attribute* att, Sensor* s){
    time=t;
    value=val;
    attribute=att;
    sensor=s;
}