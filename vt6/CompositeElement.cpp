//
// Created by Iida Rinnasto on 13/02/2019.
//
#include "CompositeElement.h"

CompositeElement::CompositeElement(const Element &e1, const Element &e2, const std::function<int(int, int)> &op, char &opc){
    opmd1 = e1.clone();
    opmd2 = e2.clone();
    op_fun = op;
    op_ch = opc;
}
CompositeElement::CompositeElement(const CompositeElement &e) {
    *opmd1 = *e.opmd1;
    *opmd2 = *e.opmd2;
    this->op_fun = e.op_fun;
    this->op_ch = e.op_ch;
}
CompositeElement& CompositeElement::operator=(const CompositeElement &e){

}
std::unique_ptr<Element> CompositeElement::clone() const {
        return std::unique_ptr<Element>(new CompositeElement(*this));
}

std::string CompositeElement::toString() const {
    return '(' + &opmd1->toString() + op_ch + opmd2->toString() + ')';
}

int CompositeElement::evaluate(const Valuation &val) const {}