/*************************************************************************
                           User  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <User> (fichier User.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "User.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

map<string, User*> User::mapUsers={};

string User::getUserID ( ) const
// Algorithme :
// Retourne l'id d'utilisateur.
{
    return userID;
} //----- Fin de GetVilleDepart

string User::getPassword ( ) const
// Algorithme :
// Retourne le mot de passe.
{
    return password;
} //----- Fin de GetVilleArrivee

User* User::parseUser(string ligne) {
    istringstream istream(ligne);
    string id, pwd;

    getline(istream, id, ';');
    getline(istream, pwd, ';');

    return new User(id, pwd);
}

bool User::initUsers(string filename) {
    ifstream fichier(filename);
    bool done = fichier.good();
    string ligne;

    if(done) {
        while ((not fichier.eof()) and getline(fichier, ligne)) {
            User* user = parseUser(ligne);
            mapUsers.insert(pair<string, User*>(user->getUserID(), user));
        }
    }

    return done;
}

map<string, User*> User::getMapUsers(){
    return mapUsers;
}


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

User::User ( string id, string pwd )
{
    #ifdef MAP
        cout << "Appel au constructeur de <User>" << endl;
    #endif

    userID = id;
    password = pwd;

} //----- Fin de User

User::User ( )
{
    #ifdef MAP
        cout << "Appel au constructeur de <User>" << endl;
    #endif

} //----- Fin de User

User::~User ( )
{
    #ifdef MAP
        cout << "Appel au destructeur de <User>" << endl;
    #endif

} //----- Fin de ~User


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
