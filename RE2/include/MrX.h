#pragma once
#include <iostream>
#include "Enemy.h"
//derivata din enemy, boss final cu hp si damage mari, suprascrie attack(), operator<<, fara atribute proprii suplimentare
//cerinta: derivata din clasa abstracta enemy, instanciata in bossFight()

class MrX : public Enemy {
public:
    MrX(std::string nume = "Mr. X", int hp = 500, int damage = 30);
    MrX(const MrX& altul);
    MrX& operator=(const MrX& altul);
    ~MrX();
    int attack() const override;
    Enemy* clone() const override;
    friend std::ostream& operator<<(std::ostream& out, const MrX& m);
};
