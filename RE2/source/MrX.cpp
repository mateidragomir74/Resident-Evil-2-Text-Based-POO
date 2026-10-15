#include "../include/MrX.h"
//implementare mrx, boss final, apeleaza constructorul enemy, attack() returneaza damage fix, operator<< prin upcast
using namespace std;

MrX::MrX(string nume, int hp, int damage) : Enemy(nume, hp, damage) {}

MrX::MrX(const MrX& altul) : Enemy(altul) {}

MrX::~MrX() {}

MrX& MrX::operator=(const MrX& altul) {
    if (this != &altul)
        Enemy::operator=(altul);
    return *this;
}

Enemy* MrX::clone() const { return new MrX(*this); }

int MrX::attack() const {
    return this->getDamage();
}

ostream& operator<<(ostream& out, const MrX& m) {
    out << static_cast<const Enemy&>(m);
    return out;
}
