#pragma once
#include <iostream>
#include <string>
#include "Enemy.h"
//derivata din enemy, atribut bool eDecapitat, suprascrie attack() cu logica de decapitare, citire(), afisare(), cc si operator=
//cerinta: derivata din clasa abstracta enemy, apeleaza constructorul parintelui in lista de initializare

class Zombie : public Enemy {
private:
    bool eDecapitat;
public:
    Zombie(std::string nume = "Zombie", int hp = 100, int damage = 10, bool eDecapitat = false);
    Zombie(const Zombie& altul);
    ~Zombie();
    Zombie& operator=(const Zombie& altul);
    friend std::ostream& operator<<(std::ostream& out, const Zombie& z);
    int attack() const override;
    Enemy* clone() const override;
    void citire(std::istream& in) override;
    void afisare(std::ostream& out) const override;
    void decapitate();
    bool isDecapitated() const;
};
