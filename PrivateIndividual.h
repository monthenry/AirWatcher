/*************************************************************************
                           PrivateIndividual  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <PrivateIndividual> (fichier PrivateIndividual.h) ----------------
#if ! defined ( PrivateIndividual_H )
#define PrivateIndividual_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
#include "User.h"
#include "Sensor.h"
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <PrivateIndividual>


//------------------------------------------------------------------------

class PrivateIndividual : public User
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    int getPoints() const;

    int getReliable() const;

    void setPoints(int p);

    void setReliable(bool r);

<<<<<<< HEAD
=======
    list<Sensor*> getSensors() const;

    int setSensors(list<Sensor*> s);

    void addSensor(Sensor* s) ;


>>>>>>> fd67540a928c18c48b4d678cde6aefea0546794c
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    PrivateIndividual ( string id,  string pwd, int p, int r );

    virtual ~PrivateIndividual ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

    int points;
    bool reliable;
    list<Sensor*> sensors;
};

//-------------------------------- Autres définitions dépendantes de <PrivateIndividual>

#endif // PrivateIndividual_H
