//
// Created by Iida Rinnasto on 13/02/2019.
//
#include "CompositeElement.h"

CompositeElement::CompositeElement(const Element &e1, const Element &e2, const CEFFunction &op, char &opc){
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
    if (this != &e) {
        CompositeElement temp{e};
        std::swap(*this, temp);
    }
    return *this;
}
std::unique_ptr<Element> CompositeElement::clone() const {
    return nullptr;
}

std::string CompositeElement::toString() const {
    std::stringstream ss;
    ss << '(' << opmd1->toString() << op_ch << opmd2->toString() << ')';
    return ss.str();
}

int CompositeElement::evaluate(const Valuation &val) const {
    return op_fun(opmd1->evaluate(val),opmd2->evaluate(val));
}
