//
// Created by Iida Rinnasto on 05/02/2019.
//

#ifndef ET3_SYMBOLICMATRIX_H
#define ET3_SYMBOLICMATRIX_H

#include <vector>
#include "Element.h"
#include "VarElement.h"
#include "ConcreteSquareMatrix.h"
#include "Valuation.h"

class SymbolicSquareMatrix{
private:
    int n;
    std::vector<std::vector<std::unique_ptr<Element>>> elements;

public:
    SymbolicSquareMatrix();
    SymbolicSquareMatrix(const std::string& str_m);
    SymbolicSquareMatrix(const SymbolicSquareMatrix &m);
    SymbolicSquareMatrix(SymbolicSquareMatrix &&m) noexcept;
    virtual ~SymbolicSquareMatrix();
    SymbolicSquareMatrix& operator=(const SymbolicSquareMatrix &m);
    SymbolicSquareMatrix& operator=(SymbolicSquareMatrix &&m) noexcept;
    SymbolicSquareMatrix transpose() const;
    bool operator==(const SymbolicSquareMatrix &m) const;
    void print(std::ostream &os) const;
    std::string toString() const;
    ConcreteSquareMatrix evaluate(const Valuation& val) const;

};
std::ostream& operator<<(std::ostream&, const SymbolicSquareMatrix&);

#endif //ET3_SYMBOLICMATRIX_H
