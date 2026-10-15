#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Item.h"
//singleton pentru inventarul jucatorului, o singura instanta, gestiune iteme cu addItem, removeItem, decreaseItem, hasItemOfTip
//cerinta: clasa singleton (tema 3), constructor privat, instanta statica, reset la pornirea unui joc nou

class Inventory {
private:
    static Inventory* instanta;
    std::vector<Item*> items;
    Inventory() {}
public:
    static Inventory* getInstance();
    static void reset();
    void addItem(Item* item);
    void removeItem(const std::string& name);
    void decreaseItem(const std::string& name);
    void setCantitate(const std::string& name, int cant);
    std::vector<Item*> getItems() const;
    bool isEmpty() const;
    bool hasItemOfTip(const std::string& tip) const;
    void afiseaza() const;
    friend std::ostream& operator<<(std::ostream& out, const Inventory& inv);
};
