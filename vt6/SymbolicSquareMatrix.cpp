//
// Created by Iida Rinnasto on 08/02/2019.
//
#include "SymbolicSquareMatrix.h"
#include "sstream"
#include "iostream"
#include "algorithm"
/**
 * @brief vakiokonstruktori SymbolicSquareMatrix -luokan olioille.
 */
SymbolicSquareMatrix::SymbolicSquareMatrix() { n = 0;}


/**
 * @brief vakio dekonstruktori SymbolicSquareMatrix -luokan olioille
 */

SymbolicSquareMatrix::~SymbolicSquareMatrix() {}


/**
 * @brief Konstruktori luokan SymbolicSquareMatrix luokan olioille, jotka luodaan käyttäen string tyyppistä muuttujaa
 * @param str_m Luodaan olio String -tyyppisestä muuttujasta, jonka tulee olla muotoa [[1,2,3][4,5,6][7,8,9]]
 * @param ss Käsitellään str_m -muuttujaa käyttäen stringstreamia
 * @param tempChar tallennetaan merkki kerrallaan tempChar muuttujaan
 * @param tempVarChar muuttuja jonka avulla luodaan variableElemen muuttuja
 * @param tempInt tallennetaan merkki tähän, jos kyseessä Int
 * @param choice määrittää luodaanko intElement vai VariableElement
 */

SymbolicSquareMatrix::SymbolicSquareMatrix(const std::string& str_m) {
    if (str_m.empty()) {
        throw std::runtime_error("Invalid String");
    }
    std::stringstream ss{str_m};
    char tempChar;
    char tempVarChar;
    int tempInt;
    int choice = 0;

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
            if(std::isalpha(ss.peek())){
                ss >> tempVarChar;
                choice = 1;
                if (!ss.good()) {
                    throw std::runtime_error("Invalid String OR CHAR 1");
                }
            }
            if(std::isdigit(ss.peek())) {
                choice = 2;
                ss >> tempInt;
                if (!ss.good()) {
                    throw std::runtime_error("Invalid String OR CHAR 2");
                }
            }
            if(choice == 2) {
                this->elements.back().push_back(std::unique_ptr<Element>{new IntElement{tempInt}});
            }
            if(choice == 1){
                this->elements.back().push_back(std::unique_ptr<Element>{new VariableElement{tempVarChar}});
            }
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
 * @brief konstruktori joka luo uuden SymbolicSquareMatrix -olion käyttäen toista oliota
 * @param m osoittee olioon, jonka sisältö siirretään luotavaan olioon.
 */

SymbolicSquareMatrix::SymbolicSquareMatrix(const SymbolicSquareMatrix &m) {
    for(auto &temp : m.elements){
        std::vector<std::unique_ptr<Element>> newRow;
        for(auto &temp2 : temp){
            newRow.push_back(std::unique_ptr<Element>(temp2->clone()));

        }
        elements.push_back(std::move(newRow));
    }
    n = m.n;
}

SymbolicSquareMatrix::SymbolicSquareMatrix(SymbolicSquareMatrix &&m) noexcept: n(m.n), elements(std::move(m.elements)){}

SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(const SymbolicSquareMatrix &m) {
    if (this != &m) {
        SymbolicSquareMatrix temp{m};
        std::swap(*this, temp);
    }
    return *this;
}

SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(SymbolicSquareMatrix &&m) noexcept {
    if (this != &m) {
        this->n = m.n;
        this->elements = std::move(m.elements);
    }
    return *this;
}

bool SymbolicSquareMatrix::operator==(const SymbolicSquareMatrix &m) const {
    if(n != m.n){
        return false;
    }
    if(toString() == m.toString()){
        return true;
    }else{
        return false;
    }
}

std::string SymbolicSquareMatrix::toString() const {
    std::stringstream ss;
    print(ss);
    return ss.str();
}

SymbolicSquareMatrix SymbolicSquareMatrix::transpose() const {
    //Kääntää squarematrixin rivit sarakkeiksi ja toisinpäin, ja palauttaa käännetyn
    // [[1,2][3,4]] -> [[1,3][2,4]]
    SymbolicSquareMatrix transpose;
    transpose.n = n;
    transpose.elements = std::vector<std::vector<std::unique_ptr<Element>>>(n);
    int col_num = 0;
    for(auto &row : elements){
        for(auto &element : row){
            transpose.elements[col_num].push_back(std::unique_ptr<Element>(element->clone()));
            col_num = (col_num + 1) % n;
        }
    }
    return transpose;
}

void SymbolicSquareMatrix::print(std::ostream &os) const {
    std::stringstream ss;
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
    std::cout << ss.str() << std::endl;
}

ConcreteSquareMatrix SymbolicSquareMatrix::evaluate(const Valuation &val) const{
    //Muutaa Squarematrixin muodosta [[1,a][2,b]] -> [[1,3][2,4]]
    //toimii kuten aieminkin numeroiden kanssa mutta jos isalpha niin sit luetaan niitä, pitää käyttää .clear tai se ei pysty lukeen erroreiden läpi mitään
    std::stringstream ss(this->toString());
    std::stringstream cSqMat;
    int tempInt;
    int tempVarInt;
    char tempChar;
    int i = 0;
    bool first = true;
    VariableElement tempVarElem;

    if(n <= 0){
        return ConcreteSquareMatrix();
    }


    ss >> tempChar;
    cSqMat << tempChar;
    while(i < this->n){
        if(first) {
            ss >> tempChar;
            cSqMat << tempChar;
        }
        while(tempChar != ']'){
            if(std::isalpha(ss.peek())){
                ss >> tempChar;
                tempVarElem.setVal(tempChar);
                tempVarInt = tempVarElem.evaluate(val);
                cSqMat << tempVarInt;
            }
            if(std::isdigit(ss.peek())){
                ss >> tempInt;
                cSqMat << tempInt;
            }
            ss >> tempChar;
            cSqMat << tempChar;
        }
        first = false;
        ss >> tempChar;
        cSqMat << tempChar;
        i++;
    }
    ConcreteSquareMatrix tempSq = ConcreteSquareMatrix(cSqMat.str());
    return tempSq;
}
std::ostream& operator<<(std::ostream& os, const SymbolicSquareMatrix& m){
    os << m.toString();
    return os;
}