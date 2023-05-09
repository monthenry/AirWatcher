/*************************************************************************
                           GovernmentAgent  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <GovernmentAgent> (fichier GovernmentAgent.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "GovernmentAgent.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
GovernmentAgent::GovernmentAgent ( string id,  string pwd )
    : User ( id, pwd )
{
    #ifdef MAP
        cout << "Appel au constructeur de <GovernmentAgent>" << endl;
    #endif

} //----- Fin de GovernmentAgent


GovernmentAgent::~GovernmentAgent ( )
{
    #ifdef MAP
    cout << "Appel au destructeur de <GovernmentAgent>" << endl;
    #endif

} //----- Fin de ~GovernmentAgent


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
