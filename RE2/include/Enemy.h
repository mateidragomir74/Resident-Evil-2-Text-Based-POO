#pragma once
#include <iostream>
#include <string>
//clasa de baza abstracta pentru inamici, constructor, cc, destructor virtual, operator=, operator<<, attack() pur virtual, citire si afisare virtuale, takeDamage si isAlive
//cerinta: clasa abstracta cu functie pur virtuala, baza pentru ierarhia zombie, licker, mrx
class Enemy {
private:
    std::string nume;
    int hp;
    int damage;
public:
    Enemy(std::string nume = "Enemy", int hp = 100, int damage = 10);
    Enemy(const Enemy& altul);
    virtual ~Enemy();
    Enemy& operator=(const Enemy& altul);
    friend std::ostream& operator<<(std::ostream& out, const Enemy& e);
    friend std::istream& operator>>(std::istream& in, Enemy& e);
    virtual int attack() const = 0;
    virtual Enemy* clone() const = 0;
    virtual void citire(std::istream& in);
    virtual void afisare(std::ostream& out) const;
    int takeDamage(int damageDePrimit);
    bool isAlive() const;
    std::string getNume() const;
    int getHP() const;
    int getDamage() const;
};
