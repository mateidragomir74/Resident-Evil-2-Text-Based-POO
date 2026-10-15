#include "../include/Item.h"
//implementare item, constructori, operator=, operator<< pentru afisare, getteri pentru campurile private
using namespace std;

Item::Item(string nume, string tip, string descriere, int cantitate) {
    this->nume = nume;
    this->tip = tip;
    this->descriere = descriere;
    this->cantitate = cantitate;
}

Item::Item(const Item& other) {
    this->nume = other.nume;
    this->tip = other.tip;
    this->descriere = other.descriere;
    this->cantitate = other.cantitate;
}

Item& Item::operator=(const Item& other) {
    if (this != &other) {
        this->nume = other.nume;
        this->tip = other.tip;
        this->descriere = other.descriere;
        this->cantitate = other.cantitate;
    }
    return *this;
}

Item::~Item() {}

ostream& operator<<(ostream& os, const Item& i) {
    os << "Nume: " << i.nume << "\n";
    os << "Tip: " << i.tip << "\n";
    os << "Cantitate: " << i.cantitate << "\n";
    return os;
}

string Item::getNume() const { return this->nume; }
string Item::getTip() const { return this->tip; }
string Item::getDescriere() const { return this->descriere; }
int Item::getCantitate() const { return this->cantitate; }
void Item::setCantitate(int c) { this->cantitate = c; }
