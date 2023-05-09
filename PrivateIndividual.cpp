/*************************************************************************
                           PrivateIndividual  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <PrivateIndividual> (fichier PrivateIndividual.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "PrivateIndividual.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void PrivateIndividual::afficher ( ) const
// Algorithme :
// On affiche les infos générales du User composé puis on appel la méthode afficher
// sur la liste de Users composant le User composé.
{
    cout << "User : " << userID << ", " << password << endl;
} //----- Fin de Afficher

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

