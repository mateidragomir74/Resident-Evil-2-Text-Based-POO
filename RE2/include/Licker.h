#pragma once
#include <iostream>
#include <string>
#include "Enemy.h"
//derivata din enemy, atribut bool aAtacat, damage dublu dupa primul atac, suprascrie attack(), citire(), afisare(), cc si operator=
//cerinta: derivata din clasa abstracta enemy, folosita in downcast cu dynamic_cast in combat()

class Licker : public Enemy {
private:
    bool aAtacat;
public:
    Licker(std::string nume = "Licker", int hp = 150, int damage = 20, bool aAtacat = false);
    Licker(const Licker& altul);
    ~Licker();
    Licker& operator=(const Licker& altul);
    friend std::ostream& operator<<(std::ostream& out, const Licker& l);
    int attack() const override;
    Enemy* clone() const override;
    void citire(std::istream& in) override;
    void afisare(std::ostream& out) const override;
    void setAtacat(bool atacat) { this->aAtacat = atacat; }
    bool hasAttacked() const { return this->aAtacat; }
};
