//
// Created by Matias Lang on 13/02/2019.
//

#include "IntElement.h"


IntElement::IntElement(int val) : val(val) {}

int IntElement::getVal() const {
    return val;
}
void IntElement::setVal(int v){
    val = v;
}
IntElement& IntElement::operator*=(const IntElement &i){
    val *= i.val;
    return *this;
}
IntElement& IntElement::operator+=(const IntElement &i) {
    val += i.val;
    return *this;
}
IntElement& IntElement::operator-=(const IntElement &i) {
    val -= i.val;
    return *this;
}
bool IntElement::operator==(const IntElement &i) const{
    return (i.getVal() == this->getVal());
}
bool IntElement::operator!=(const IntElement &obj) const {
    return this->val != obj.val;
}
IntElement operator*(const IntElement& i, const IntElement& o){
    IntElement temp1 = i;
    temp1 *= o;
    return temp1;
}
IntElement operator+(const IntElement& i, const IntElement & j){
    IntElement temp2 = i;
    temp2 += j;
    return temp2;
}
IntElement operator-(const IntElement& i, const IntElement & k){
    IntElement temp3 = i;
    temp3 -= k;
    return temp3;
}
std::ostream& operator<<(std::ostream& os, const Element& i) {
    os << i.toString();
    return os;
}
int IntElement::evaluate(const Valuation &v) const {
    return v.at(val);
}
std::string IntElement::toString() const {
    return std::to_string(val);
}
std::unique_ptr<Element> IntElement::clone() const {
    return std::unique_ptr<Element>(new IntElement(*this));
}

