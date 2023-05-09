#if ! defined ( MEASUREMENT_H )
#define MEASUREMENT_H

#include <ctime> 
using namespace std;

class Measurement {
    public: 

        Measurement(time_t time, float value);
        time_t getTime();
        float getValue();





    private: 
        float value ;
        time_t time ;
};
#endif