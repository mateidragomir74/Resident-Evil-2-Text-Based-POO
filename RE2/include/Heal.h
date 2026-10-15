#pragma once
#include <iostream>
#include <string>
#include "Item.h"
//derivata din item, vindeca jucatorul cu hpVindecare hp, atribut propriu hpVindecare, suprascrie use(), cc si operator=
//cerinta: derivata din clasa abstracta item, polimorfism prin use()

class Heal : public Item {
private:
    int hpVindecare;
public:
    Heal(std::string nume = "Heal", std::string descriere = "Vindecare", int cantitate = 1, int hpVindecare = 20);
    Heal(const Heal& altul);
    ~Heal();
    Heal& operator=(const Heal& altul);
    friend std::ostream& operator<<(std::ostream& out, const Heal& h);
    int getHpVindecare() const;
    void use(Player& player) override;
};
