//
// Created by Iida Rinnasto on 12/02/2019.
//
/**
 * CompositeElementi luokan ja sen funktioiden alustus
 */
#ifndef ET6_COMPOSITEELEMENT_H
#define ET6_COMPOSITEELEMENT_H

#include "Element.h"
#include "Valuation.h"
#include <sstream>

using CEFFunction = std::function<int(int,int)>;


class CompositeElement : public Element{
public:
    CompositeElement(const Element &e1, const Element &e2, const CEFFunction &op, char &opc);
    CompositeElement(const CompositeElement &e);
    CompositeElement &operator=(const CompositeElement &e);
    ~CompositeElement()= default;
    std::unique_ptr<Element> clone() const final;
    std::string toString() const final;
    int evaluate(const Valuation &val) const final;


private:
    //Element* oprnd1;
    std::unique_ptr<Element> opmd1;
    // Element* oprnd2;
    std::unique_ptr<Element> opmd2;
    CEFFunction op_fun;
    char op_ch;
};


#endif //ET6_COMPOSITEELEMENT_H
