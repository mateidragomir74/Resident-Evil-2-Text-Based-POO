#pragma once
#include <iostream>
#include <string>
#include "Item.h"
//derivata din item, munitie cu tip char (p=pistol, s=shotgun), suprascrie use(), cc si operator=
//cerinta: derivata din clasa abstracta item

class Ammo : public Item {
private:
    char tip;
public:
    Ammo(std::string nume = "Ammo", char tip = 'P', std::string descriere = "O ammo", int cantitate = 1);
    Ammo(const Ammo& altul);
    ~Ammo();
    Ammo& operator=(const Ammo& altul);
    friend std::ostream& operator<<(std::ostream& out, const Ammo& a);
    char getTip() const;
    void use(Player& player) override;
};
