#include "../include/Enemy.h"
//implementare enemy, constructori, operator=, operator<<, takeDamage, isAlive, citire si afisare virtuale cu acces direct la date private
using namespace std;

Enemy::Enemy(string nume, int hp, int damage) {
    this->nume = nume;
    this->hp = hp;
    this->damage = damage;
}

Enemy::Enemy(const Enemy& altul) {
    this->nume = altul.nume;
    this->hp = altul.hp;
    this->damage = altul.damage;
}

Enemy::~Enemy() {}

Enemy& Enemy::operator=(const Enemy& altul) {
    if (this != &altul) {
        this->nume = altul.nume;
        this->hp = altul.hp;
        this->damage = altul.damage;
    }
    return *this;
}

ostream& operator<<(ostream& out, const Enemy& e) {
    e.afisare(out);
    return out;
}

istream& operator>>(istream& in, Enemy& e) {
    e.citire(in);
    return in;
}

void Enemy::citire(istream& in) {
    cout << "  Nume: "; in >> this->nume;
    cout << "  HP: ";   in >> this->hp;
    cout << "  Damage: "; in >> this->damage;
}

void Enemy::afisare(ostream& out) const {
    out << "Nume: "   << this->nume   << "\n";
    out << "HP: "     << this->hp     << "\n";
    out << "Damage: " << this->damage << "\n";
}

int Enemy::takeDamage(int damageDePrimit) {
    this->hp -= damageDePrimit;
    if (this->hp < 0) this->hp = 0;
    return this->hp;
}

bool Enemy::isAlive() const { return this->hp > 0; }
string Enemy::getNume() const { return this->nume; }
int Enemy::getHP() const { return this->hp; }
int Enemy::getDamage() const { return this->damage; }
