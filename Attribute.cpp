#include "Attribute.h"
    
Attribute::Attribute(string id, string u, string descr){
    attributeID= id;
    unit= u;
    description=descr;

}
        
string Attribute::getAttributeId(){
    return attributeId;
}
string Attribute::setAttributeId(string id){
    attributeId=id;
}

string Attribute::getUnit(){
    return unit;
}

string Attribute::setUnit(string u){
    unit=u;
}

string Attribute::getDescription(){
    return description;
}

string Attribute::setDescription(string descr){
    description=descr;
}