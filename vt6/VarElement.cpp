//
// Created by Matias Lang on 13/02/2019.
//

#include "VarElement.h"



VariableElement::VariableElement() : var('x'){

}

VariableElement::VariableElement(char v) : var(v){}

void VariableElement::setVal(char v) {
    var = v;
}

char VariableElement::getVal() const {
    return var;
}

std::unique_ptr<Element> VariableElement::clone() const{
    return std::unique_ptr<VariableElement>(new VariableElement(*this));
}


int VariableElement::evaluate(const Valuation &val) const {
    return val.at(var);
}

std::string VariableElement::toString() const {
    std::stringstream ss;
    ss << var;
    return ss.str();
}

bool VariableElement::operator==(const VariableElement &i) const {
    if(var != i.var){
        return false;
    }else{
        return true;
    }
}

