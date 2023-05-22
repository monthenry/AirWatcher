/*************************************************************************
                         User  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe  User> (fichier User.h) ----------------
#if ! defined ( User_H )
#define User_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe  <User>


//------------------------------------------------------------------------

class User 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    string getUserID (  ) const;

    string getPassword ( ) const;


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

    User ( string userID, string password );
    // Mode d'emploi :
    // Constructeur de la classe User
    // Contrat : 
    // 

    virtual  ~User ( );
    // Mode d'emploi :
    // Destructeur de la classe User
    // Contrat : 
    // 

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées


//----------------------------------------------------- Attributs protégés
    string userID;
    string password;
};

//-------------------------------- Autres définitions dépendantes de  User>

#endif // User_H
