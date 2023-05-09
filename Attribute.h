#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

using namespace std;

#include <string>

class Attribute{

    public :
        Attribute(string id, string u, string descr);
        
        string getAttributeId();
        string getUnit();
        string getDescription();

    private :
        string attributeId;
        string unit;
        string description;
};

#endif