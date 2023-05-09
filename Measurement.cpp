

#include "Measurement.h"
#include <iostream>


float Measurement::getValue(){
    return value;
}

time_t Measurement::getTime(){
    return time;
}

Measurement::Measurement(time_t t, float val) : time(t), value(val){

}