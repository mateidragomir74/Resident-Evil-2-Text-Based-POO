#include "../include/Room.h"
//implementare room, destructorul sterge inamicii cu delete (compunere), itemele sunt doar clearate, remove cauta dupa nume
//cerinta: compunere demonstrata in destructor prin delete enemies[i]
using namespace std;

Room::Room(string nume, bool areUsaInchisa) {
    this->nume = nume;
    this->areUsaInchisa = areUsaInchisa;
}

Room::Room(const Room& altul) {
    this->nume = altul.nume;
    this->areUsaInchisa = altul.areUsaInchisa;
    this->items = altul.items;
    for (size_t i = 0; i < altul.enemies.size(); i++)
        this->enemies.push_back(altul.enemies[i]->clone());
}

Room::~Room() {
    this->items.clear();
    for (size_t i = 0; i < enemies.size(); i++)
        delete enemies[i];
    this->enemies.clear();
}

Room& Room::operator=(const Room& altul) {
    if (this != &altul) {
        for (size_t i = 0; i < enemies.size(); i++)
            delete enemies[i];
        this->enemies.clear();
        this->nume = altul.nume;
        this->areUsaInchisa = altul.areUsaInchisa;
        this->items = altul.items;
        for (size_t i = 0; i < altul.enemies.size(); i++)
            this->enemies.push_back(altul.enemies[i]->clone());
    }
    return *this;
}

void Room::addItem(Item* item) { this->items.push_back(item); }

void Room::addEnemy(Enemy* enemy) { this->enemies.push_back(enemy); }

void Room::removeItem(const string& itemName) {
    for (size_t i = 0; i < this->items.size(); i++) {
        if (this->items[i]->getNume() == itemName) {
            this->items.erase(this->items.begin() + i);
            return;
        }
    }
}

void Room::removeEnemy(const string& enemyName) {
    for (size_t i = 0; i < this->enemies.size(); i++) {
        if (this->enemies[i]->getNume() == enemyName) {
            this->enemies.erase(this->enemies.begin() + i);
            return;
        }
    }
}

vector<Item*> Room::getItems() const { return this->items; }
vector<Enemy*> Room::getEnemies() const { return this->enemies; }
string Room::getNume() const { return this->nume; }
