//------------------------------------------------------ Include personnel
#include "PrivateIndividual.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

int PrivateIndividual::getPoints() const
{
    return points;
}

bool PrivateIndividual::getReliable() const
{
    return reliable;
}

void PrivateIndividual::setPoints(int p)
{
    points = p;
}

void PrivateIndividual::setReliable(bool r)
{
    reliable = r;
}
list<Sensor*> PrivateIndividual::getSensors() const{

    return sensors;
}

void PrivateIndividual::addSensor(Sensor* s) {
    sensors.push_back(s);
}

int PrivateIndividual::setSensors(list<Sensor*> s){
    sensors=s;
}
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
PrivateIndividual::PrivateIndividual ( string id,  string pwd, int p, int r )
    : User ( id, pwd ), points(p), reliable(r)
// Algorithme :
// On initialise les villes de départ et d'arrivée via le constructeur père
// On passe le pointeur de liste l à notre pointeur de liste membre.
{
    #ifdef MAP
        cout << "Appel au constructeur de <PrivateIndividual>" << endl;
    #endif

} //----- Fin de PrivateIndividual


PrivateIndividual::~PrivateIndividual ( )
// Algorithme :
// Libère l'espace mémoire sur lequel pointe listeUsers
{
    #ifdef MAP
    cout << "Appel au destructeur de <PrivateIndividual>" << endl;
    #endif

} //----- Fin de ~PrivateIndividual


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
