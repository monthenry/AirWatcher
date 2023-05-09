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
char* Trajet::getUserID ( ) const
// Algorithme :
// Retourne l'id d'utilisateur.
{
    return userID;
} //----- Fin de GetVilleDepart

String User::getPassword ( ) const
// Algorithme :
// Retourne le mot de passe.
{
    return password;
} //----- Fin de GetVilleArrivee

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

User::User ( String id, String pwd )
{
    #ifdef MAP
        cout << "Appel au constructeur de <User>" << endl;
    #endif

    userID = id;
    pwd = pwd;

} //----- Fin de User


User::~User ( )
{
    #ifdef MAP
        cout << "Appel au destructeur de <User>" << endl;
    #endif

} //----- Fin de ~User


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées