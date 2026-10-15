#include "../include/Inventory.h"
//implementare singleton, getInstance cu lazy init, reset sterge instanta la joc nou, decreaseItem scade cantitatea si sterge itemul la 0
//cerinta: instanta statica initializata cu nullptr, constructor privat apelat doar din getInstance
using namespace std;

Inventory* Inventory::instanta = nullptr;

Inventory* Inventory::getInstance() {
    if (instanta == nullptr)
        instanta = new Inventory();
    return instanta;
}

void Inventory::reset() {
    if (instanta != nullptr) {
        instanta->items.clear();
        delete instanta;
        instanta = nullptr;
    }
}

void Inventory::addItem(Item* item) {
    items.push_back(item);
}

void Inventory::removeItem(const string& name) {
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i]->getNume() == name) {
            items.erase(items.begin() + i);
            return;
        }
    }
}

void Inventory::decreaseItem(const string& name) {
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i]->getNume() == name) {
            int cant = items[i]->getCantitate();
            if (cant > 1) 
                items[i]->setCantitate(cant - 1);
            else          
                items.erase(items.begin() + i);
            return;
        }
    }
}

void Inventory::setCantitate(const string& name, int cant) {
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i]->getNume() == name) {
            items[i]->setCantitate(cant);
            return;
        }
    }
}

vector<Item*> Inventory::getItems() const {
    return items;
}

bool Inventory::isEmpty() const {
    return items.empty();
}

bool Inventory::hasItemOfTip(const string& tip) const {
    for (size_t i = 0; i < items.size(); i++)
        if (items[i]->getTip() == tip) return true;
    return false;
}

void Inventory::afiseaza() const {
    cout << "\n--- Inventar ---\n";
    if (items.empty()) { cout << "Inventar gol.\n"; return; }
    for (size_t i = 0; i < items.size(); i++)
        cout << i + 1 << ". " << items[i]->getNume()
             << " (" << items[i]->getTip() << ")"
             << " x" << items[i]->getCantitate() << "\n";
}

ostream& operator<<(ostream& out, const Inventory& inv) {
    out << "--- Inventar ---\n";
    if (inv.items.empty()) { out << "Inventar gol.\n"; return out; }
    for (size_t i = 0; i < inv.items.size(); i++)
        out << i + 1 << ". " << inv.items[i]->getNume()
            << " (" << inv.items[i]->getTip() << ")"
            << " x" << inv.items[i]->getCantitate() << "\n";
    return out;
}
