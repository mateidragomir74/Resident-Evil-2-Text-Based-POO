#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "Enemy.h"
#include "Weapon.h"
//camera de joc, contine vectori de pointeri la iteme si inamici, usa blocata, adauga si sterge elemente
//cerinta: compunere cu enemy* si item* (destructorul sterge inamicii cu delete)

class Room {
private:
    std::string nume;
    std::vector<Item*> items;
    std::vector<Enemy*> enemies;
    bool areUsaInchisa;
public:
    Room(std::string nume = "Camera", bool areUsaInchisa = false);
    Room(const Room& altul);
    ~Room();
    Room& operator=(const Room& altul);
    void addItem(Item* item);
    void addEnemy(Enemy* enemy);
    bool hasItems() const { return !items.empty(); }
    bool hasEnemies() const { return !enemies.empty(); }
    bool isLocked() const { return this->areUsaInchisa; }
    void setUsaInchisa(bool inchisa) { this->areUsaInchisa = inchisa; }
    void removeItem(const std::string& itemName);
    void removeEnemy(const std::string& enemyName);
    std::vector<Item*> getItems() const;
    std::vector<Enemy*> getEnemies() const;
    std::string getNume() const;
};
