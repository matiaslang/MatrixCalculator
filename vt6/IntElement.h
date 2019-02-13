//
// Created by Iida Rinnasto on 12/02/2019.
//
/**
 * IntElement luokan ja sen funktioiden alustus
 */
#ifndef ET6_INTELEMENT_H
#define ET6_INTELEMENT_H


#include "Element.h"

class IntElement : public Element{
public:
    ~IntElement()=default; //lisätty virtual ja default
    IntElement(const IntElement &m) = default;
    IntElement(int v);
    IntElement() : val(0) {}
    /**
     * Getteri palauttaa muuttujan val arvon ja setteri asettaa muuttujan val arvon
     */
    int getVal() const;
    void setVal(int v);
    /**
     *
     */
    IntElement &operator=(const IntElement &i) = default;
    IntElement &operator+=(const IntElement& i);
    IntElement &operator-=(const IntElement& i);
    IntElement &operator*=(const IntElement& i);
    /**
     * Boolean operaattorit
     */
    bool operator==(const IntElement& i) const;
    bool operator!=(const IntElement &i) const;
    /**
     * Rajapinnan tarjoamat funktiot
     */
    std::unique_ptr<Element> clone() const;
    int evaluate(const Valuation &val) const;
    std::string toString() const;
private:
    int val;
};
IntElement operator+(const IntElement&, const IntElement&);
IntElement operator-(const IntElement&, const IntElement&);
IntElement operator*(const IntElement&, const IntElement&);
#endif //ET6_INTELEMENT_H

