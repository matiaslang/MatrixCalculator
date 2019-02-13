//
// Created by Iida Rinnasto on 05/02/2019.
//

#ifndef ET3_ELEMENT_H
#define ET3_ELEMENT_H

#include <memory>
#include <string>
#include <map>
#include <algorithm>
#include <ostream>
#include "Valuation.h"


////muuttaa cloonit niin että kutsutaan kopio koneen contructoria, jos se palauttaa normaali pointterin, nii toimis jos shared, muttta uniquie pointterilla ei ole vastaavaa toimimassa, tulis kahen pointterin ongelma


using Valuation = std::map<char, int>;

class Element {
public:
    virtual ~Element() = default;
    virtual std::unique_ptr<Element> clone() const = 0;
    virtual std::string toString() const = 0;
    virtual int evaluate(const Valuation &val) const = 0;
};


std::ostream& operator<<(std::ostream&, const Element&);
//std::istream& operator>>(std::istream&, Element&);

//IIDAMAIJAN TESTAUSTA! :)=))



#endif //ET3_ELEMENT_H
