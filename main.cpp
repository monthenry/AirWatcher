#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Sensor.h"
#include "Controller.h"
#include "User.h"
using namespace std;

Sensor* parseSensor(string s);

int main(int argc, char* argv[]) {
    bool c = User::initUsers("./data/users.csv");
    cout << c << endl;
    return 0;
}
