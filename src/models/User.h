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
#include <fstream>
#include <sstream>
#include <map>
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

    static bool initUsers(string filename);

    static map<string, User*> getMapUsers();


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
    User ( );
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

private:
//------------------------------------------------------------------ PRIVE
    static User* parseUser(string ligne);

protected:
//----------------------------------------------------- Méthodes protégées


//----------------------------------------------------- Attributs protégés
    string userID;
    string password;
    static map<string, User*> mapUsers;

    friend ostream& operator<<(ostream& os, const User& user) {
        os << user.userID << ", password=" << user.password;
        return os;
    }
};

//-------------------------------- Autres définitions dépendantes de  User>

#endif // User_H
