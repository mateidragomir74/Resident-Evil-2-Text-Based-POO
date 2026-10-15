#include "../include/Heal.h"
#include "../include/Player.h"
//implementare heal, use() vindeca playerul cu hpVindecare si scade cantitatea din inventar prin player
using namespace std;

Heal::Heal(string nume, string descriere, int cantitate, int hpVindecare)
    : Item(nume, "Heal", descriere, cantitate) {
    this->hpVindecare = hpVindecare;
}

Heal::Heal(const Heal& altul) : Item(altul) {
    this->hpVindecare = altul.hpVindecare;
}

Heal::~Heal() {}

Heal& Heal::operator=(const Heal& altul) {
    if (this != &altul) {
        Item::operator=(altul);
        this->hpVindecare = altul.hpVindecare;
    }
    return *this;
}

ostream& operator<<(ostream& out, const Heal& h) {
    out << static_cast<const Item&>(h);
    out << "HP Vindecare: " << h.hpVindecare << "\n";
    return out;
}

int Heal::getHpVindecare() const { return this->hpVindecare; }

void Heal::use(Player& player) {
    cout << "Folosind " << this->getNume() << " — vindeci " << this->hpVindecare << " HP.\n";
    player.decreaseItem(this->getNume());
    player.heal(this->hpVindecare);
}
