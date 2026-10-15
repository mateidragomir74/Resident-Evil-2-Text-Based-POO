#include "../include/Licker.h"
//implementare licker, suprascrie attack() cu damage dublu dupa primul atac, citire si afisare cu apel la parinte
using namespace std;

Licker::Licker(string nume, int hp, int damage, bool aAtacat) : Enemy(nume, hp, damage) {
    this->aAtacat = aAtacat;
}

Licker::Licker(const Licker& altul) : Enemy(altul) {
    this->aAtacat = altul.aAtacat;
}

Licker::~Licker() {}

Licker& Licker::operator=(const Licker& altul) {
    if (this != &altul) {
        Enemy::operator=(altul);
        this->aAtacat = altul.aAtacat;
    }
    return *this;
}

ostream& operator<<(ostream& out, const Licker& l) {
    out << static_cast<const Enemy&>(l);
    out << "A atacat: " << (l.aAtacat ? "Da" : "Nu") << "\n";
    return out;
}

void Licker::citire(istream& in) {
    Enemy::citire(in);
    cout << "  A atacat deja (0=Nu, 1=Da): ";
    int a; in >> a;
    this->aAtacat = (a == 1);
}

void Licker::afisare(ostream& out) const {
    Enemy::afisare(out);
    out << "A atacat: " << (this->aAtacat ? "Da" : "Nu") << "\n";
}

Enemy* Licker::clone() const { return new Licker(*this); }

int Licker::attack() const {
    if (this->aAtacat) return this->getDamage() * 2;
    return this->getDamage();
}
