#include "Controller.h"

Controller::Controller() {

}

Attribute* Controller::parseAttribute(string ligne) {
    istringstream istream(ligne);
    string id, unit, desc;

    getline(istream, id, ';');
    getline(istream, unit, ';');
    getline(istream, desc, ';');

    return new Attribute(id, unit, desc);
}

bool Controller::initAttributes(string filename) {
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

void Controller::initModel() {
    initAttributes("./data/attributes.csv");
}

map<string, Attribute*> Controller::getMapAttributes() {
    return mapAttributes;
}
