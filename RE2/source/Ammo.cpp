#include "../include/Ammo.h"
#include "../include/Player.h"
//implementare ammo, use() consuma munitia si scade cantitatea din inventar prin player
using namespace std;

Ammo::Ammo(string nume, char tip, string descriere, int cantitate)
    : Item(nume, "Ammo", descriere, cantitate) {
    this->tip = tip;
}

Ammo::Ammo(const Ammo& altul) : Item(altul) {
    this->tip = altul.tip;
}

Ammo::~Ammo() {}

Ammo& Ammo::operator=(const Ammo& altul) {
    if (this != &altul) {
        Item::operator=(altul);
        this->tip = altul.tip;
    }
    return *this;
}

ostream& operator<<(ostream& out, const Ammo& a) {
    out << static_cast<const Item&>(a);
    out << "Tip: " << a.tip << "\n";
    return out;
}

char Ammo::getTip() const { return this->tip; }

void Ammo::use(Player& player) {
    cout << "Folosesti " << this->getNume() << " — +" << this->getCantitate() << " gloante.\n";
    player.getWeapon(0).reload(this->getCantitate());
    player.removeItem(this->getNume());
}
