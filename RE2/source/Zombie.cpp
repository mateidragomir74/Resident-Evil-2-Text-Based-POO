#include "../include/Zombie.h"
//implementare zombie, apeleaza constructorul enemy, suprascrie attack() cu logica de decapitare, citire si afisare cu apel la parinte
using namespace std;

Zombie::Zombie(string nume, int hp, int damage, bool eDecapitat) : Enemy(nume, hp, damage) {
    this->eDecapitat = eDecapitat;
}

Zombie::Zombie(const Zombie& altul) : Enemy(altul) {
    this->eDecapitat = altul.eDecapitat;
}

Zombie::~Zombie() {}

Zombie& Zombie::operator=(const Zombie& altul) {
    if (this != &altul) {
        Enemy::operator=(altul);
        this->eDecapitat = altul.eDecapitat;
    }
    return *this;
}

ostream& operator<<(ostream& out, const Zombie& z) {
    out << static_cast<const Enemy&>(z);
    out << "Decapitat: " << (z.eDecapitat ? "Da" : "Nu") << "\n";
    return out;
}

void Zombie::citire(istream& in) {
    Enemy::citire(in);
    cout << "  Decapitat (0=Nu, 1=Da): ";
    int d; in >> d;
    this->eDecapitat = (d == 1);
}

void Zombie::afisare(ostream& out) const {
    Enemy::afisare(out);
    out << "Decapitat: " << (this->eDecapitat ? "Da" : "Nu") << "\n";
}

int Zombie::attack() const {
    if (this->eDecapitat) return this->getDamage() / 2;
    return this->getDamage();
}

Enemy* Zombie::clone() const { return new Zombie(*this); }
void Zombie::decapitate() { this->eDecapitat = true; }
bool Zombie::isDecapitated() const { return this->eDecapitat; }
