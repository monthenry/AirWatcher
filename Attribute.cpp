#include "Attribute.h"

/*----------------------------------------------------------------------------------------------------
CONSTRUCTOR
----------------------------------------------------------------------------------------------------*/

map<string, Attribute*> Attribute::mapAttributes = {};

Attribute::Attribute(){

}

Attribute::Attribute(string id, string u, string descr){
    attributeId = id;
    unit = u;
    description = descr;
}

/*----------------------------------------------------------------------------------------------------
GETTER
----------------------------------------------------------------------------------------------------*/
        
string Attribute::getAttributeId(){
    return attributeId;
}

string Attribute::getUnit(){
    return unit;
}

string Attribute::getDescription(){
    return description;
}

map<string, Attribute*> Attribute::getMapAttributes() {
    return mapAttributes;
}

/*----------------------------------------------------------------------------------------------------
SETTER
----------------------------------------------------------------------------------------------------*/

void Attribute::setDescription(string descr){
    description=descr;
}

void Attribute::setUnit(string u){
    unit=u;
}

/*----------------------------------------------------------------------------------------------------
CORE FUNCTIONALITY
----------------------------------------------------------------------------------------------------*/

Attribute* Attribute::parseAttribute(string ligne) {
    istringstream istream(ligne);
    string id, unit, desc;

    getline(istream, id, ';');
    getline(istream, unit, ';');
    getline(istream, desc, ';');

    return new Attribute(id, unit, desc);
}

bool Attribute::initAttributes(string filename) {
    ifstream fichier(filename);
    bool done = fichier.good();
    string ligne;

    if(done) {
        while ((not fichier.eof()) and getline(fichier, ligne)) {
            Attribute* attr = parseAttribute(ligne);

            mapAttributes.insert(pair<string, Attribute*>(attr->getAttributeId(), attr));
        }
    }

    return done;
}

