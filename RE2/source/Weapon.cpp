#include "../include/Weapon.h"
#include <cstdlib>
#include "../include/GameExceptions.h"
//implementare weapon, toti constructorii, toti operatorii, fire() cu logica pe tip arma si aruncare exceptie, lovituraCritica, reload, numarArme static
//cerinta: fire() arunca noammoexception, operator++ incrementeaza damage, numarArme static numara instantele
using namespace std;

int Weapon::numarArme = 0;

Weapon::Weapon() {
    string piscina[] = {"Beretta M9", "Shotgun W-870", "Rocket Launcher"};
    WeaponType tipuri[] = {WeaponType::PISTOL, WeaponType::SHOTGUN, WeaponType::ROCKET_LAUNCHER};
    int zar = rand() % 3;
    this->tip = tipuri[zar];
    this->nume = piscina[zar];
    if (this->tip == WeaponType::SHOTGUN)          { this->damage = 35;  this->ammoCount = 6; }
    else if (this->tip == WeaponType::PISTOL)      { this->damage = 15;  this->ammoCount = 15; }
    else                                            { this->damage = 100; this->ammoCount = 3; }
    numarArme++;
}

Weapon::Weapon(const string& nume, WeaponType tip, int damage, int ammoCount) {
    this->nume      = nume;
    this->tip       = tip;
    this->damage    = damage;
    this->ammoCount = ammoCount;
    numarArme++;
}

Weapon::Weapon(const Weapon& altul) {
    this->nume      = altul.nume;
    this->tip       = altul.tip;
    this->damage    = altul.damage;
    this->ammoCount = altul.ammoCount;
    numarArme++;
}

Weapon::~Weapon() {
    numarArme--;
}

Weapon& Weapon::operator=(const Weapon& altul) {
    if (this != &altul) {
        this->nume      = altul.nume;
        this->tip       = altul.tip;
        this->damage    = altul.damage;
        this->ammoCount = altul.ammoCount;
    }
    return *this;
}

ostream& operator<<(ostream& out, const Weapon& w) {
    string tipStr;
    if (w.tip == WeaponType::PISTOL) tipStr = "Pistol";
    else if (w.tip == WeaponType::SHOTGUN) tipStr = "Shotgun";
    else tipStr = "Rocket";
    out << "\nTip: " << tipStr;
    out << "\nDamage: " << w.damage;
    out << "\nAmmo: " << w.ammoCount;
    return out;
}

void Weapon::citire(istream& in) {
    cout << "Nume arma: ";
    in >> this->nume;
    int tipInt;
    cout << "Tip (0=Pistol, 1=Shotgun, 2=Rocket): ";
    in >> tipInt;
    if (tipInt < 0 || tipInt > 2) {
        cout << "Tip invalid, se foloseste Pistol.\n";
        tipInt = 0;
    }
    this->tip = static_cast<WeaponType>(tipInt);
    cout << "Damage: ";
    in >> this->damage;
    cout << "Ammo: ";
    in >> this->ammoCount;
}

istream& operator>>(istream& in, Weapon& w) {
    w.citire(in);
    return in;
}

int Weapon::operator[](int index) const {
    if (index == 0) return this->damage;
    if (index == 1) return this->ammoCount;
    return -1;
}

Weapon& Weapon::operator++() {
    this->damage += 5;
    return *this;
}

int Weapon::operator+(int bonus) const {
    return this->damage + bonus;
}

int operator+(int bonus, const Weapon& w) {
    return w.damage + bonus;
}

int Weapon::operator-(int used) const {
    return this->ammoCount - used;
}

bool Weapon::operator==(const Weapon& alta) const {
    return this->damage == alta.damage;
}

bool Weapon::operator<(const Weapon& alta) const {
    return this->damage < alta.damage;
}

string Weapon::getNume() const    { return this->nume; }
int Weapon::getDamage() const     { return this->damage; }
int Weapon::getAmmoCount() const  { return this->ammoCount; }
WeaponType Weapon::getTip() const { return this->tip; }
int Weapon::getNumarArme()        { return numarArme; }

void Weapon::fire() {
    if (this->ammoCount > 0) {
        this->ammoCount--;
        if (this->tip == WeaponType::ROCKET_LAUNCHER)
            cout << "BOOM! Racheta lansata! Ai dat " << this->damage << " damage. Rachete ramase: " << this->ammoCount << "\n";
        else
            cout << "BANG! Ai dat" << this->damage << " damage. Ammo ramas: " << this->ammoCount << "\n";
    } else {
        throw NoAmmoException("Nu ai gloante sa tragi!");
    }
}

int Weapon::lovituraCritica() const {
    return this->damage * 2;
}

void Weapon::reload(int gloanteNoi) {
    this->ammoCount += gloanteNoi;
    cout << "Incarcat! Ammo acum: " << this->ammoCount << "\n";
}
