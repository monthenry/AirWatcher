/*************************************************************************
                           GovernmentAgent  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <GovernmentAgent> (fichier GovernmentAgent.h) ----------------
#if ! defined ( GovernmentAgent_H )
#define GovernmentAgent_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
#include "User.h"
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <GovernmentAgent>


//------------------------------------------------------------------------

class GovernmentAgent : public User
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    GovernmentAgent ( string id,  string pwd );

    virtual ~GovernmentAgent ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <GovernmentAgent>

#endif // GovernmentAgent_H
