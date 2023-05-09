#include "Attribute.h"
    
Attribute::Attribute(string id, string u, string descr){
    attributeId= id;
    unit= u;
    description=descr;

}

Attribute::Attribute(){

}
        
string Attribute::getAttributeId(){
    return attributeId;
}

string Attribute::getUnit(){
    return unit;
}

void Attribute::setUnit(string u){
    unit=u;
}

string Attribute::getDescription(){
    return description;
}

void Attribute::setDescription(string descr){
    description=descr;
}