#pragma once
#include <iostream>
#include <string>
//clasa completa cu toti operatorii ceruti, enum weapontype, atribut static numarArme, fire cu exceptie, reload, lovituraCritica
//cerinta: clasa cu toti operatorii (tema 1), enum (tema 2), atribut si functie statica, operator membru si non-membru
enum class WeaponType { PISTOL, SHOTGUN, ROCKET_LAUNCHER };
class Weapon {
private:
    std::string nume;
    int damage;
    int ammoCount;
    WeaponType tip;
    static int numarArme;

public:
    Weapon();
    Weapon(const std::string& nume, WeaponType tip, int damage, int ammoCount);
    Weapon(const Weapon& altul);
    ~Weapon();
    Weapon& operator=(const Weapon& altul);
    friend std::ostream& operator<<(std::ostream& out, const Weapon& w);
    friend std::istream& operator>>(std::istream& in, Weapon& w);
    int operator[](int index) const;   
    Weapon& operator++();             
    int operator+(int bonus) const;    //membra
    int operator-(int used) const;
    friend int operator+(int bonus, const Weapon& w);//non membra
    bool operator==(const Weapon& alta) const;
    bool operator<(const Weapon& alta) const;
    std::string getNume() const;
    int getDamage() const;
    int getAmmoCount() const;
    WeaponType getTip() const;
    void citire(std::istream& in);
    void fire();
    int lovituraCritica() const;
    void reload(int gloanteNoi);
    static int getNumarArme();
};