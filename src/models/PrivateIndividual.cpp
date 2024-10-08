#include "PrivateIndividual.h"

/*----------------------------------------------------------------------------------------------------
CONSTRUCTOR
----------------------------------------------------------------------------------------------------*/

PrivateIndividual::PrivateIndividual ( string id,  string pwd, int p, int r )
    : User ( id, pwd ), points(p), reliable(r)
{

}


PrivateIndividual::~PrivateIndividual ( )
{

}

/*----------------------------------------------------------------------------------------------------
GETTER
----------------------------------------------------------------------------------------------------*/

int PrivateIndividual::getPoints() const
{
    return points;
}

bool PrivateIndividual::getReliable() const
{
    return reliable;
}

list<Sensor*> PrivateIndividual::getSensors() const{

    return sensors;
}

/*----------------------------------------------------------------------------------------------------
SETTER
----------------------------------------------------------------------------------------------------*/

void PrivateIndividual::setPoints(int p)
{
    points = p;
}

void PrivateIndividual::setReliable(bool r)
{
    reliable = r;
}

int PrivateIndividual::setSensors(list<Sensor*> s){
    sensors=s;
}

/*----------------------------------------------------------------------------------------------------
CORE FUNCTIONALITY
----------------------------------------------------------------------------------------------------*/

void PrivateIndividual::addSensor(Sensor* s) {
    sensors.push_back(s);
}