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

#include "User.h"
#include "Sensor.h"
#include "Controller.h"

using namespace std;

template<typename F>
double measurePerformance(F&& func)
{
    // Start the timer
    auto startTime = std::chrono::high_resolution_clock::now();

    // Call the function
    std::forward<F>(func)();

    // End the timer and calculate the duration
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;

    // Return the duration in seconds
    return duration.count();
}

int main(int argc, char* argv[]) {
    Controller c;
    c.initModel();

    c.initController();

    return 0;

}