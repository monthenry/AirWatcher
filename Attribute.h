#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

using namespace std;

#include <string>

class Attribute{

    public :
        Attribute(string id, string u, string descr);
        Attribute();

        string getAttributeId();
        string getUnit();
        void setUnit(string u);
        string getDescription();
        void setDescription(string descr);
    private :
        string attributeId;
        string unit;
        string description;
};

#endif