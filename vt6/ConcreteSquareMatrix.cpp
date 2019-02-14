//
// Created by Iida Rinnasto on 08/02/2019.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ConcreteSquareMatrix.h"
#include "SymbolicSquareMatrix.h"
#include "map"
#include "CompositeElement.h"
#include "functional"

/**
 * Default empty constructor
 * no parameters
 */
ConcreteSquareMatrix::ConcreteSquareMatrix() {
    this->n = 1;
    this->elements.emplace_back();
    this->elements.back().push_back(std::unique_ptr<IntElement>{new IntElement{0}});
}
/**
 * @brief constructing new squarematrix by copying the contents of existing one
 * @param m SquareMatrix to be copied to this
 */
ConcreteSquareMatrix::ConcreteSquareMatrix(const ConcreteSquareMatrix &m) {
    this->n = m.n;
    this->elements.clear();

    for (const auto &row : m.elements) {
        this->elements.emplace_back();
        for (const auto &column : row) {
            this->elements.back().push_back(std::unique_ptr<IntElement>{new IntElement(*column)});
            //newrow.push_back(std::unique_ptr<IntElement> {dynamic_cast<IntElement*>(el->clone())});
        }
    }
}

ConcreteSquareMatrix::ConcreteSquareMatrix(ConcreteSquareMatrix &&m) noexcept {
    this->n = m.n;
    this->elements = std::move(m.elements);
    m.n = 1;
    m.elements.clear();
    m.elements.emplace_back();
    m.elements.back().push_back(std::unique_ptr<IntElement>{new IntElement{0}});
}

/**
 * @brief Constructing new SquareMatrix from string in a form of "[[a11,...,a1n][an1,ann]]"
 * @param s
 *
 */
ConcreteSquareMatrix::ConcreteSquareMatrix(const std::string &s) {
    if (s.empty()) {
        throw std::runtime_error("Invalid String");
    }

    std::stringstream ss{s};
    char tempChar;
    int tempInt;

    int row = 0;
    this->n = std::numeric_limits<int>::max();

    ss >> tempChar;
    if (!ss.good() || tempChar != '[') {
        throw std::runtime_error("Invalid String");
    }
    // Read rows
    while (row < this->n) {
        ss >> tempChar;
        if (!ss.good() || tempChar != '[') {
            throw std::runtime_error("Invalid String");
        }
        this->elements.emplace_back();

        int column = 0;
        while (tempChar != ']') {
            ss >> tempInt;
            if (!ss.good()) {
                throw std::runtime_error("Invalid String");
            }
            this->elements.back().push_back(std::unique_ptr<IntElement>{new IntElement{tempInt}});
            ss >> tempChar;
            if (!ss.good() || (tempChar != ',' && tempChar != ']')) {
                throw std::runtime_error("Invalid String");
            }
            column++;
        }
        if (row == 0) {
            this->n = column;
        }
        if (n != column) {
            throw std::runtime_error("Invalid String");
        }
        row++;
    }
    ss >> tempChar;
    if (!ss.good() || ss.peek() != EOF || tempChar != ']') {
        throw std::runtime_error("Invalid String");
    }
}
/**
 * operator -= to be used with SquareMatrixes.
 * we can only handle matrixes that are same size. Otherwise throw std::out_of_range
 * @param m
 * @return result
 */
ConcreteSquareMatrix& ConcreteSquareMatrix::operator-=(const ConcreteSquareMatrix &m) {
    if((m.n != this->n)){
        throw (std::out_of_range("size mismatch"));
    }
    auto firstRow = this->elements.begin();
    auto secondRow = m.elements.begin();
    while (firstRow != this->elements.end()) {
        auto firstColumn = firstRow->begin();
        auto secondColum = secondRow->begin();                 //first row and second row and column
        while (firstColumn != firstRow->end()) {
            **firstColumn -= **secondColum;
            firstColumn++;
            secondColum++;
        }
        firstRow++;
        secondRow++;
    }
    return *this;
}
/**
 * operator += to be used with SquareMatrixes.
 * we can only handle matrixes that are same size. Otherwise throw std::out_of_range
 * @param m
 * @return result
 */
ConcreteSquareMatrix& ConcreteSquareMatrix::operator+=(const ConcreteSquareMatrix &m) {
    if((m.n != this->n)){
        throw (std::out_of_range("size mismatch"));
    }
    auto firstRow = this->elements.begin();
    auto secondRow = m.elements.begin();
    while (firstRow != this->elements.end()) {
        auto firstColumn = firstRow->begin();
        auto secondColumn = secondRow->begin();                 //first row and second row and column
        while (firstColumn != firstRow->end()) {
            **firstColumn += **secondColumn;
            firstColumn++;
            secondColumn++;
        }
        firstRow++;
        secondRow++;
    }
    return *this;
}
/**
 * operator *= to be used with SquareMatrixes.
 * we can only handle matrixes that are same size. Otherwise throw std::out_of_range
 * @param m
 * @return result
 */
ConcreteSquareMatrix& ConcreteSquareMatrix::operator*=(const ConcreteSquareMatrix &m){
    if((m.n != this->n)){
        throw (std::out_of_range("size mismatch"));
    }
    ConcreteSquareMatrix temp{*this};
    ConcreteSquareMatrix rhs = m.transpose();
    for (auto row = this->elements.begin(); row != this->elements.end(); row++) {
        for (auto column = row->begin(); column != row->end(); column++) {
            **column = 0;
            auto i = std::distance(this->elements.begin(), row);
            auto j = std::distance(row->begin(), column);
            for (int k = 0; k < n; k++) {
                **column += (*temp.elements[i][k] * *rhs.elements[j][k]);
            }
        }
    }
    return *this;
}
/**
 * operator == to be used with SquareMatrixes.
 * we can only handle matrixes that are same size. Otherwise throw std::out_of_range
 * @param m
 * @return boolean result
 */
bool ConcreteSquareMatrix::operator==(const ConcreteSquareMatrix &m) const {
    if (this->n != m.n) {
        throw (std::out_of_range("size mismatch"));
    }
    auto f_row = this->elements.begin();
    auto s_row = m.elements.begin();

    while (f_row != this->elements.end()) {
        auto f_column = f_row->begin();
        auto s_column = s_row->begin();
        while (f_column != f_row->end()) {
            if (**f_column != **s_column) {
                return false;
            }
            f_column++;
            s_column++;
        }
        f_row++;
        s_row++;
    }
    return true;
}

bool ConcreteSquareMatrix::operator!=(const ConcreteSquareMatrix &obj) const {
    return !(*this == obj);
}
/**
 * Print function to be used to print matrix.
 * Usage for example SquareMatrix m: m.print(std::cout)
 * @param os to saving toString of given matrix
 * @return output stream os
 */
void ConcreteSquareMatrix::print(std::ostream& os) const{
    if (this->n == 0) {
        os << "";
    } else {
        os << "[";
        for (const auto &row : this->elements) {
            os << "[";
            for (const auto &column : row) {
                os << *column;
                if (column != row.back()) {
                    os << ",";
                }
            }
            os << "]";
        }
        os << "]";
    }
}
/*
 * returning String -presentation of matrix
 */
std::string ConcreteSquareMatrix::toString() const {
    std::stringstream ss;
    this->print(ss);
    return ss.str();
}

/*
 * Method transposes squarematrix, as in colums = rows and rows = columns.
 * returns result
 */
ConcreteSquareMatrix ConcreteSquareMatrix::transpose() const{ //edit

    ConcreteSquareMatrix tempSqMat{*this};
    tempSqMat.elements.clear();
    for (const auto &row : this->elements) {
        int i = 0;
        for (const auto &column : row) {
            if (row == this->elements.front()) {
                tempSqMat.elements.emplace_back();
            }
            tempSqMat.elements[i].push_back(std::unique_ptr<IntElement>{new IntElement{*column}});
            i++;
        }
    }
    return tempSqMat;
}


bool ConcreteSquareMatrix::isSquareMatrix(const std::string& str) {
    /***
     * @brief Function isSquareMatrix makes sure that given string is in correct form[[a11,a12,...,a1n][a21,a22,...,a2n][an1,an2,...,ann]] , returns boolean (true if correct)
     * @param i integer variable that contains number we are handling
     * @param c char variable that contains letter we are handling
     * @param rows integer variable that contains the number of row we are handling
     * @param counter integer variable that contains number of numbers each table includes
     * @param n integer variable that contains the number of rows the string should include
     * @param len integer variable which is the length of given string, in case we are handling 1*1 matrix (for example [2])
     */

    int i = 0;//käsittelyssä oleva merkki
    char c; //käsittelyssä oleva merkki
    int rows = 0;//rivi muuttuja hakasulkujen sisälle oleville merkkijonoille
    int counter = 0;
    int n = std::numeric_limits<int>::max();//laskurin arvo, maksimi c++
    int len = str.length();

    std::stringstream ss(str);//muutos tavallisesta string:stä stringstream muotoon, merkkijonon manipuloinnin mahdollistamisen vuoksi

    ss >> c;//siirretään stringstreamin arvo "c" muuttujaan
    if (c == '[' && len > 3) {//if luuppi alkaa, tarkistetaan, että ensimmäinen merkki on hakasulku
        while (rows <= n) {
            ss >> c;
            counter = 0;
            if (c == '[') {
                while (c != ']') {
                    ss >> i;
                    if (!ss.good()) {
                        std::cout << "Numero on virheellinen" << std::endl;
                        return false;
                    }
                    ss >> c;
                    if (c != ',' && c != ']') {
                        std::cout << "Virheellinen merkki" << std::endl;
                        return false;
                    }
                    else {
                        counter++;
                    }
                }
                if (rows == 0) {
                    n = counter;
                }
                if (rows > n) {
                    return false;
                }
                if(rows > 0 && counter != n){
                    return false;
                }
                if(counter == 0){
                    ss >> i;
                    if(!ss.good()) {
                        return false;
                    }
                }
                rows++;
            } else if (c == ']' && !ss.eof()) {
                ss >> c;
                if (ss.eof()) {
                    return true;
                }
            } else {
                std::cout << "Viimeinen merkki väärin" << std::endl;
                return false;
            }
        }
    }
    else if (len == 3) {
        ss >> i;
        if (!ss.good()) {
            return false;
        }
        ss >> c;
        if (c != ']') {
            return false;
        } else
            return true;
    }
    else if(len < 3) {
        return false;
    }


    return true;

}
/**
 * Method for providin n outside of squarematrix scope
 * @return
 */
int ConcreteSquareMatrix::getN() const{
    return n;
}

/**
 * operators +,-,= and * for SquareMatrixes
 */

ConcreteSquareMatrix &ConcreteSquareMatrix::operator=(ConcreteSquareMatrix &&m) noexcept {
    if (this != &m) {
        this->n = m.n;
        this->elements = std::move(m.elements);
    }
    return *this;
}

ConcreteSquareMatrix &ConcreteSquareMatrix::operator=(const ConcreteSquareMatrix &m) {
    if (this != &m) {
        ConcreteSquareMatrix temp{m};
        std::swap(*this, temp);
    }
    return *this;
}


std::ostream& operator<<(std::ostream& os, const ConcreteSquareMatrix& m){
    os << m.toString();
    return os;
}

ConcreteSquareMatrix operator+(const ConcreteSquareMatrix &m, const ConcreteSquareMatrix n){
    if((m.getN() != n.getN())){
        throw (std::out_of_range("size mismatch"));
    }
    ConcreteSquareMatrix temp = m;
    temp += n;
    return temp;
}
ConcreteSquareMatrix operator-(const ConcreteSquareMatrix &m, const ConcreteSquareMatrix n){
    if((m.getN() != n.getN())){
        throw (std::out_of_range("size mismatch"));
    }
    ConcreteSquareMatrix temp = m;
    temp -= n;
    return temp;
}
ConcreteSquareMatrix operator*(const ConcreteSquareMatrix &m, const ConcreteSquareMatrix n){
    if((m.getN() != n.getN())){
        throw (std::out_of_range("size mismatch"));
    }
    ConcreteSquareMatrix temp = m;
    temp *= n;
    return temp;
}




TEST_CASE("Right tests for IntElement"){
IntElement i = IntElement(2);
IntElement j = IntElement(4);
IntElement k = IntElement(8);
IntElement o = IntElement(10);

CHECK(i.getVal() == 2);
CHECK(j.getVal() == 4);
CHECK(k.getVal() == 8);
CHECK(o.getVal() == 10.0);

i.setVal(66);
j.setVal(9);
k.setVal(80000000);
o.setVal(100);

CHECK(i.getVal() == 66);
CHECK(j.getVal() == 9);
CHECK(k.getVal() == 80000000);
CHECK(o.getVal() == 100);

}

TEST_CASE("ConcreteSquarMat test"){
ConcreteSquareMatrix sq = ConcreteSquareMatrix("[[11111,2,3][4,5,6][7,8,9]]");
ConcreteSquareMatrix sq2 = ConcreteSquareMatrix("[[1,2,3][4,5,6][7,8,9]]");
ConcreteSquareMatrix sq3 = ConcreteSquareMatrix("[[1,2,3][4,5,6][7,8,9]]");


CHECK(sq.toString() == "[[11111,2,3][4,5,6][7,8,9]]");

ConcreteSquareMatrix k = sq;

CHECK(k.toString() == "[[11111,2,3][4,5,6][7,8,9]]");

sq2 += sq3;
CHECK(sq2.toString() == "[[2,4,6][8,10,12][14,16,18]]");

sq2 -= sq3;
CHECK(sq2.toString() == "[[1,2,3][4,5,6][7,8,9]]");

sq3.transpose();
CHECK(sq3.transpose().toString() == "[[1,4,7][2,5,8][3,6,9]]");

REQUIRE(sq2 == sq3);
sq2 *= sq3;
CHECK(sq2.toString() == "[[30,36,42][66,81,96][102,126,150]]");

}

TEST_CASE("Variable element tests"){
    Valuation val{};
    val['a'] = 1;
    val['b'] = 2;
    val['c'] = 3;

    VariableElement a = VariableElement('a');
    VariableElement b = VariableElement('b');
    VariableElement c = VariableElement('c');

    CHECK(c.evaluate(val) == 3);

}

TEST_CASE("SymbolicSquareMatrix test"){
    SymbolicSquareMatrix sq = SymbolicSquareMatrix("[[11111,2,3][4,5,6][7,8,9]]");
    SymbolicSquareMatrix sq2 = SymbolicSquareMatrix("[[1,a,3][4,b,6][7,c,9]]");
    SymbolicSquareMatrix sq3 = SymbolicSquareMatrix("[[1,2,3][4,5,6][7,8,9]]");
    SymbolicSquareMatrix sq4 = SymbolicSquareMatrix("[[a,b,c][1111111,2222222,3333333][c,b,a]]");
    SymbolicSquareMatrix sq5 = SymbolicSquareMatrix("[[a,b,c][a,b,c][a,b,c]]");
    SymbolicSquareMatrix sq6 = SymbolicSquareMatrix(sq5);
    Valuation val{};
    val['a'] = 1;
    val['b'] = 2;
    val['c'] = 3;

    CHECK(sq.toString() == "[[11111,2,3][4,5,6][7,8,9]]");
    CHECK(sq2.toString() == "[[1,a,3][4,b,6][7,c,9]]");


    SymbolicSquareMatrix k = sq;

    CHECK(k.toString() == "[[11111,2,3][4,5,6][7,8,9]]");

    CHECK(sq3.transpose().toString() == "[[1,4,7][2,5,8][3,6,9]]");

    CHECK(sq2.transpose().toString() == "[[1,4,7][a,b,c][3,6,9]]");

    CHECK(sq2.evaluate(val).toString() == "[[1,1,3][4,2,6][7,3,9]]");

    CHECK(sq4.evaluate(val).toString() == "[[1,2,3][1111111,2222222,3333333][3,2,1]]");

    CHECK(sq5.evaluate(val).toString() == "[[1,2,3][1,2,3][1,2,3]]");

    CHECK(sq6.toString() == "[[a,b,c][a,b,c][a,b,c]]");
}
    //TODO tests for composite element
/*TEST_CASE("CompositeElement tests"){
    IntElement a1{1};
    IntElement a2{2};
    std::function<int(int,int)> a3 = plus;
    char a4{'+'};
    CompositeElement c1 = CompositeElement(a1,a2,a3,a4);

    c1.toString();
}*/

TEST_CASE("Require Throws" ){
ConcreteSquareMatrix sq3 = ConcreteSquareMatrix("[[1,2,3][4,5,6][7,8,9]]");
ConcreteSquareMatrix sq4 = ConcreteSquareMatrix("[[1,2][4,5]]");

CHECK_THROWS(sq3 += sq4);
CHECK_THROWS(sq3 -= sq4);
CHECK_THROWS(sq3 *= sq4);
CHECK_THROWS(sq3 == sq4);




}

