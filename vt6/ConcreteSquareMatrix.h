//
// Created by Iida Rinnasto on 05/02/2019.
//

#ifndef ET3_CONCRETEMATRIX_H
#define ET3_CONCRETEMATRIX_H

#include "string"
#include "IntElement.h"
#include "VarElement.h"
#include "Element.h"
#include "vector"


class ConcreteSquareMatrix{
public:
    bool isSquareMatrix(const std::string &str);
    ConcreteSquareMatrix();
    virtual ~ConcreteSquareMatrix() = default;
    ConcreteSquareMatrix(const std::string& s);
    ConcreteSquareMatrix(const ConcreteSquareMatrix& m);
    ConcreteSquareMatrix(ConcreteSquareMatrix &&obj) noexcept;
    ConcreteSquareMatrix &operator+=(const ConcreteSquareMatrix& m);
    ConcreteSquareMatrix &operator-=(const ConcreteSquareMatrix& m);
    ConcreteSquareMatrix &operator*=(const ConcreteSquareMatrix& m);
    ConcreteSquareMatrix &operator=(const ConcreteSquareMatrix& m);
    ConcreteSquareMatrix &operator=(ConcreteSquareMatrix&& m) noexcept;
    ConcreteSquareMatrix transpose() const;
    bool operator==(const ConcreteSquareMatrix& m) const;
    bool operator!=(const ConcreteSquareMatrix &obj) const;
    void print(std::ostream &os) const;
    std::string toString() const;
    int getN() const;


private:
    int n;
    std::vector<std::vector<std::unique_ptr<IntElement>>> elements;
};
ConcreteSquareMatrix operator+(const ConcreteSquareMatrix&, const ConcreteSquareMatrix);//kaikki nää uusia
ConcreteSquareMatrix operator-(const ConcreteSquareMatrix&, const ConcreteSquareMatrix);
ConcreteSquareMatrix operator*(const ConcreteSquareMatrix&, const ConcreteSquareMatrix);
std::ostream& operator<<(std::ostream&, const ConcreteSquareMatrix&);


#endif //ET3_CONCRETEMATRIX_H
