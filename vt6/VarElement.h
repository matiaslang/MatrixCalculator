//
// Created by Iida Rinnasto on 12/02/2019.
//
/**
 * VarElement luokan ja sen funktioiden alustus
 */
#ifndef ET6_VARELEMENT_H
#define ET6_VARELEMENT_H

#include "Element.h"
#include <sstream>

class VariableElement : public Element{
public:
    VariableElement();
    VariableElement(char v);
    VariableElement(const VariableElement &m) = default;
    ~VariableElement()=default;
    /**
     * Getteri palauttaa muuttujan val arvon ja setteri asettaa muuttujan val arvon
     */
    char getVal() const;
    void setVal(char v);
    /**
     * Rajapinnan tarjoamat funktiot
     */
    std::unique_ptr<Element> clone() const;
    std::string toString() const;
    int evaluate(const Valuation &val) const;
    /**
     * Bool operaattori
     */
    bool operator==(const VariableElement &i) const;
private:
    char var;
};

#endif //ET6_VARELEMENT_H
