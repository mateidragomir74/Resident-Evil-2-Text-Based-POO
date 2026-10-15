#pragma once
#include <iostream>
#include <string>
#include "Item.h"
//derivata din item, cheie pentru usa blocata cu atribut tipCheie, suprascrie use(), cc si operator=
//cerinta: derivata din item, folosita cu noKeyException in gameloop

class KeyItem : public Item {
private:
    std::string tipCheie;
public:
    KeyItem(std::string nume = "KeyItem", std::string descriere = "Un item cheie", int cantitate = 1, std::string tipCheie = "Unknown");
    KeyItem(const KeyItem& altul);
    ~KeyItem();
    KeyItem& operator=(const KeyItem& altul);
    friend std::ostream& operator<<(std::ostream& out, const KeyItem& k);
    std::string getTipCheie() const;
    void use(Player& player) override;
};
