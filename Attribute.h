#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

using namespace std;

#include <string>
#include <sstream>
#include <fstream>
#include <map>

class Attribute{

    public :
        Attribute(string id, string u, string descr);
        Attribute();

        string getAttributeId();

        string getUnit();
        void setUnit(string u);

        string getDescription();
        void setDescription(string descr);

        static map<string, Attribute*> getMapAttributes();

        static bool initAttributes(string filename);

    private :
        static Attribute* parseAttribute(string line);

        string attributeId;
        string unit;
        string description;

        static map<string, Attribute*> mapAttributes;
};

#endif