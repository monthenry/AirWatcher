#if ! defined ( PrivateIndividual_H )
#define PrivateIndividual_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
#include "User.h"
#include "Sensor.h"
using namespace std;

//------------------------------------------------------------------------

class PrivateIndividual : public User
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    int getPoints() const;

    bool getReliable() const;

    void setPoints(int p);

    void setReliable(bool r);

    list<Sensor*> getSensors() const;

    int setSensors(list<Sensor*> s);

    void addSensor(Sensor* s) ;

//-------------------------------------------- Constructeurs - destructeur
    PrivateIndividual ( string id,  string pwd, int p, int r );

    virtual ~PrivateIndividual ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés

    int points;
    bool reliable;
    list<Sensor*> sensors;
};

#endif // PrivateIndividual_H
