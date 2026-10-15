#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Item.h"
#include "Weapon.h"
//jucatorul, vector de arme prin agregare, delegheaza toate operatiile cu iteme catre inventory singleton, hp, heal si takeDamage
//cerinta: agregare cu weapon (vector by value), delega iteme catre singleton inventory (tema 3)

class Player {
private:
    std::string nume;
    int hp;
    std::vector<Weapon> weapons;
public:
    Player(std::string nume = "Player", int hp = 100);
    Player(const Player& altul);
    ~Player();
    Player& operator=(const Player& altul);
    friend std::ostream& operator<<(std::ostream& out, const Player& p);
    friend std::istream& operator>>(std::istream& in, Player& p);
    void addItem(Item* item);
    void addWeapon(const Weapon& weapon);
    void removeItem(const std::string& itemName);
    void removeWeapon(const std::string& weaponName);
    std::vector<Item*> getInventory() const;
    std::vector<Weapon> getWeapons() const;
    std::string getNume() const;
    int getHP() const;
    bool isAlive() const;
    void takeDamage(int damageDePrimit);
    void heal(int hpVindecare);
    void setCantitate(const std::string& itemName, int cantitateNoua);
    void decreaseItem(const std::string& itemName);
    Weapon& getWeapon(int index);
};
