#include "../include/Player.h"
#include "../include/Inventory.h"
//implementare player, toate operatiile cu iteme delega catre inventory singleton, getWeapon arunca out_of_range la index invalid
using namespace std;

Player::Player(string nume, int hp) {
    this->nume = nume;
    this->hp = hp;
}

Player::Player(const Player& altul) {
    this->nume = altul.nume;
    this->hp = altul.hp;
    this->weapons = altul.weapons;
}

Player::~Player() {
    this->weapons.clear();
}

Player& Player::operator=(const Player& altul) {
    if (this != &altul) {
        this->nume = altul.nume;
        this->hp = altul.hp;
        this->weapons = altul.weapons;
    }
    return *this;
}

ostream& operator<<(ostream& out, const Player& p) {
    out << "Nume: " << p.nume << endl;
    out << "HP: " << p.hp << endl;
    out << *Inventory::getInstance();
    out << "Arme: " << p.weapons.size() << " arme\n";
    for (size_t i = 0; i < p.weapons.size(); i++)
        out << "  Arma " << i + 1 << ": " << p.weapons[i] << endl;
    return out;
}

istream& operator>>(istream& in, Player& p) {
    cout << "Nume player: ";
    getline(in, p.nume);
    cout << "HP: ";
    in >> p.hp;
    in.ignore();
    return in;
}

void Player::addItem(Item* item) {
    Inventory::getInstance()->addItem(item);
}

void Player::addWeapon(const Weapon& weapon) {
    this->weapons.push_back(weapon);
}

void Player::removeItem(const string& itemName) {
    Inventory::getInstance()->removeItem(itemName);
}

void Player::removeWeapon(const string& weaponName) {
    for (size_t i = 0; i < this->weapons.size(); i++) {
        if (this->weapons[i].getNume() == weaponName) {
            this->weapons.erase(this->weapons.begin() + i);
            return;
        }
    }
}

vector<Item*> Player::getInventory() const {
    return Inventory::getInstance()->getItems();
}

vector<Weapon> Player::getWeapons() const {
    return this->weapons;
}

string Player::getNume() const {
    return this->nume;
}

int Player::getHP() const {
    return this->hp;
}

bool Player::isAlive() const {
    return this->hp > 0;
}

void Player::takeDamage(int damageDePrimit) {
    this->hp -= damageDePrimit;
    if (this->hp < 0) this->hp = 0;
}

void Player::heal(int hpVindecare) {
    this->hp += hpVindecare;
    if (this->hp > 100) this->hp = 100;
}

void Player::decreaseItem(const string& itemName) {
    Inventory::getInstance()->decreaseItem(itemName);
}

void Player::setCantitate(const string& itemName, int cantitateNoua) {
    Inventory::getInstance()->setCantitate(itemName, cantitateNoua);
}

Weapon& Player::getWeapon(int index) {
    if (index >= 0 && index < (int)this->weapons.size())
        return this->weapons[index];
    throw out_of_range("Index arma invalid");
}
