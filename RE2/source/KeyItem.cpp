#include "../include/KeyItem.h"
#include "../include/Player.h"
//implementare keyitem, use() deschide usa cu tipCheie si scade cantitatea, operator<< prin upcast la item
using namespace std;

KeyItem::KeyItem(string nume, string descriere, int cantitate, string tipCheie)
    : Item(nume, "KeyItem", descriere, cantitate) {
    this->tipCheie = tipCheie;
}

KeyItem::KeyItem(const KeyItem& altul) : Item(altul) {
    this->tipCheie = altul.tipCheie;
}

KeyItem::~KeyItem() {}

KeyItem& KeyItem::operator=(const KeyItem& altul) {
    if (this != &altul) {
        Item::operator=(altul);
        this->tipCheie = altul.tipCheie;
    }
    return *this;
}

ostream& operator<<(ostream& out, const KeyItem& k) {
    out << static_cast<const Item&>(k);
    out << "Tip Cheie: " << k.tipCheie << "\n";
    return out;
}

string KeyItem::getTipCheie() const {
    return this->tipCheie;
}

void KeyItem::use(Player& player) {
    cout << "Folosind " << this->getNume() << " pentru a deschide " << this->tipCheie << ".\n";
    player.decreaseItem(this->getNume());
}
