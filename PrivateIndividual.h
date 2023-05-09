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
};

//-------------------------------- Autres définitions dépendantes de <PrivateIndividual>

#endif // PrivateIndividual_H
