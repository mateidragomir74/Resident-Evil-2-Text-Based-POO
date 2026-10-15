#pragma once
#include <iostream>
#include <string>
//clasa abstracta de baza pentru iteme, use() pur virtual, date private, operator<<, forward declaration pentru player pentru a evita dependenta circulara
//cerinta: clasa abstracta cu functie pur virtuala, baza pentru ierarhia heal, ammo, keyitem
class Player;

class Item {
private:
    std::string nume;
    std::string tip;
    std::string descriere;
    int cantitate;
public:
    Item(std::string nume = "", std::string tip = "",
         std::string descriere = "", int cantitate = 0);
    Item(const Item& other);
    Item& operator=(const Item& other);
    virtual ~Item();
    friend std::ostream& operator<<(std::ostream& os, const Item& i);
    virtual void use(Player& player) = 0;
    void setCantitate(int c);
    std::string getNume() const;
    int getCantitate() const;
    std::string getTip() const;
    std::string getDescriere() const;
};
