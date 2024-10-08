#include "User.h"

map<string, User*> User::mapUsers={};

/*----------------------------------------------------------------------------------------------------
CONSTRUCTOR
----------------------------------------------------------------------------------------------------*/

User::User ( )
{

}

User::User ( string id, string pwd )
{
    userID = id;
    password = pwd;
}

User::~User ( )
{

}


/*----------------------------------------------------------------------------------------------------
GETTER
----------------------------------------------------------------------------------------------------*/

string User::getUserID ( ) const
{
    return userID;
}

string User::getPassword ( ) const
{
    return password;
}

map<string, User*> User::getMapUsers(){
    return mapUsers;
}

/*----------------------------------------------------------------------------------------------------
CORE FUNCTIONALITY
----------------------------------------------------------------------------------------------------*/

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

User* User::parseUser(string ligne) {
    istringstream istream(ligne);
    string id, pwd;

    getline(istream, id, ';');
    getline(istream, pwd, ';');

    return new User(id, pwd);
}