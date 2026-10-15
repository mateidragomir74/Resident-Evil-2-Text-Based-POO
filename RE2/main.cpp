#include <iostream>
#include <stdlib.h>
#include "Player.h"
#include "Room.h"
#include "Weapon.h"
#include "Heal.h"
#include "KeyItem.h"
#include "Ammo.h"
#include "Enemy.h"
#include "Licker.h"
#include "Zombie.h"
#include "MrX.h"
#include <vector>
#include <ctime>
#include "GameExceptions.h"
#include <map>
#include <string>
#include "GameLog.h"
#include "Inventory.h"
#include <typeinfo>
#include <limits>
//meniu interactiv, selectcharacter cu comparare arme, generaterooms cu camere si inamici, combat cu dynamic_cast si critical hit, bossfight, modcreator cu late binding pentru citire n obiecte
//cerinta: meniu interactiv, dynamic_cast pentru downcast (tema 2+3), map<string,int> al doilea container stl, gamelog template, modcreator cu functii virtuale pentru citire/afisare n obiecte
using namespace std;

Player selectCharacter() {
    Weapon leon_w("Beretta M9", WeaponType::PISTOL, 25, 20);
    Weapon claire_w("Shotgun W-870", WeaponType::SHOTGUN, 35, 6);

    cout << "Selecteaza un personaj:\n";
    cout << "1. Leon:  " << leon_w.getNume()
         << " | damage: " << leon_w[0] << " | ammo: " << leon_w[1] << "\n";
    cout << "2. Claire: " << claire_w.getNume()
         << " | damage: " << claire_w[0] << " | ammo: " << claire_w[1] << "\n";
    cout << "3. Arma custom\n";

    if (leon_w == claire_w)
        cout << "Armele au acelasi damage!\n";
    else if (leon_w < claire_w)
        cout << "Claire porneste cu arma mai puternica.\n";
    else
        cout << "Leon porneste cu arma mai puternica.\n";

    cout << "Damage potential Leon cu bonus +10: " << (10 + leon_w) << "\n";

    int opt;
    cout << "Optiune: ";
    cin >> opt;

    Player p;
    switch (opt) {
        case 1:
            cout << "Ai ales Leon!\n";
            p = Player("Leon", 100);
            p.addWeapon(leon_w);
            break;
        case 2:
            cout << "Ai ales Claire!\n";
            p = Player("Claire", 100);
            p.addWeapon(claire_w);
            break;
        case 3: {
            Weapon w;
            cout << "Introdu datele armei:\n";
            cin >> w;                      
            cout << "Arma creata:" << w << "\n";  
            p = Player("Custom", 100);
            p.addWeapon(w);
            break;
        }
        default:
            cout << "Optiune nevalida! Ai primit Leon by default.\n";
            p = Player("Leon", 100);
            p.addWeapon(leon_w);
    }
    return p;
}

vector<Room> generateRooms(vector<Enemy*> inamici = {}) {
    vector<Room> camere;
    camere.reserve(10);
    camere.push_back(Room("Hol Principal", false));
    string tipuri[] = {"Biblioteca", "Camera Normala", "Lockerroom",
                       "Laborator", "Subsol", "Camera Secreta", "Camera de Control"};
    for (int i = 0; i < 8; i++) {
        camere.push_back(Room(tipuri[rand() % 7], false));
        if (inamici.empty()) {
            if (rand() % 2 == 0) 
                camere.back().addEnemy(new Zombie("Zombie", 60, 5));
            else                  
                camere.back().addEnemy(new Licker("Licker", 100, 10));
        }
    }
    camere.push_back(Room("Pod", false));
    for (int i = 0; i < (int)inamici.size(); i++) {
        int idx = (i < 8) ? i + 1 : 8;
        camere[idx].addEnemy(inamici[i]);
    }

    camere[4].setUsaInchisa(true);

    camere[0].addItem(new Heal("Spray Medical", "Heal 30 HP", 1, 30));
    camere[1].addItem(new Ammo("Gloante pistol", 'P', "Munitie pentru pistol", 15));
    camere[2].addItem(new KeyItem("Cheie pod", "Deschide camera blocata", 1, "blocat"));
    camere[3].addItem(new Ammo("Cartuse shotgun", 'S', "Munitie pentru shotgun", 4));
    camere[5].addItem(new Heal("Ierburi verzi", "Restaureaza 20 HP", 1, 20));
    camere[6].addItem(new Ammo("Gloante pistol", 'P', "Munitie pentru pistol", 10));
    camere[7].addItem(new Heal("Ierburi mixte", "Restaureaza 50 HP", 1, 50));

    return camere;
}

void uiMeniu() {
    cout << "+++++++++++++++++++++++++++++++++++++" << endl;
    cout << " 1. Joc nou cu inamici random        " << endl;
    cout << " 2. Joc nou cu inamici custom        " << endl;
    cout << " 0. Iesire                           " << endl;
    cout << "-------------------------------------\n" << endl;
}

void afiseazaInventar() {
    Inventory::getInstance()->afiseaza();
    cout << "Arme active in joc: " << Weapon::getNumarArme() << "\n";
}

void combat(Player& p, Room& camera, map<string, int>& killCount, GameLog<string>& log, GameLog<int>& damageLog) {
    while (camera.hasEnemies() && p.isAlive()) {
        Enemy* inamic = camera.getEnemies()[0];
        Weapon& arma = p.getWeapon(0);

        cout << "\n";
        if (Licker* l = dynamic_cast<Licker*>(inamic)) {
            if (!l->hasAttacked()) {
                int dmgSurprise = l->attack();
                p.takeDamage(dmgSurprise);
                cout << "!!! LICKER sare din umbra! (" << dmgSurprise << " damage) HP ramas: " << p.getHP() << "\n";
                log.adauga("Jumpscare Licker in " + camera.getNume());
                if (!p.isAlive()) break;
            }
            cout << "[LICKER] " << inamic->getNume() << " | HP: " << inamic->getHP() << "\n";
        } else if (Zombie* z = dynamic_cast<Zombie*>(inamic)) {
            cout << "[ZOMBIE] " << z->getNume() << " | HP: " << z->getHP();
            if (z->isDecapitated()) cout << " (decapitat - damage redus)";
            cout << "\n";
        }

        string tipStr;
        WeaponType t = arma.getTip();
        if (t == WeaponType::PISTOL) tipStr = "Pistol";
        else if (t == WeaponType::SHOTGUN) tipStr = "Shotgun";
        else tipStr = "Rocket";
        cout << "Tu: " << p.getHP() << " HP | "
             << arma.getNume() << " [" << tipStr << "]"
             << " | dmg: " << arma[0]
             << " | ammo: " << arma[1] << "\n";
        cout << "1. Trage  2. Inventar  3. Fugi  4. Reincarcare\n";
        cout << "Optiune: ";
        int opt; cin >> opt;

        if (opt == 1) {
            try {
                int dmg;
                if (rand() % 5 == 0) {
                    dmg = arma.lovituraCritica();
                    cout << "LOVITURA CRITICA! (" << dmg << " damage)\n";
                } else {
                    dmg = arma.getDamage();
                }
                arma.fire();
                inamic->takeDamage(dmg);
                damageLog.adauga(dmg);

                if (Zombie* z = dynamic_cast<Zombie*>(inamic)) {
                    if (!z->isDecapitated() && inamic->getHP() > 0 && inamic->getHP() <= 15) {
                        z->decapitate();
                        cout << "L-ai decapitat pe " << z->getNume() << "! Damage redus la jumatate.\n";
                    }
                }

                if (!inamic->isAlive()) {
                    cout << inamic->getNume() << " a murit!\n";
                    killCount[inamic->getNume()]++;
                    log.adauga(inamic->getNume() + " eliminat din " + camera.getNume());
                    camera.removeEnemy(inamic->getNume());

                    int totalKills = 0;
                    for (auto& pereche : killCount) totalKills += pereche.second;
                    if (totalKills == 3) {
                        ++arma;
                        cout << ">>> Arma imbunatatita dupa 3 kills! Damage nou: " << arma[0] << "\n";
                        log.adauga("Weapon upgrade la " + arma.getNume());
                    }
                    continue;
                }
            } catch (NoAmmoException& e) {
                cout << "Eroare: " << e.what() << "\n";
                cout << "(Damage potential cu bonus +10 ar fi fost: " << (arma + 10) << ")\n";
            }
        } else if (opt == 2) {
            afiseazaInventar();
            vector<Item*> items = p.getInventory();
            if (!items.empty()) {
                cout << "Foloseste item (0 = anuleaza): ";
                int idx; cin >> idx;
                if (idx > 0 && idx <= (int)items.size())
                    items[idx - 1]->use(p);
            }
            continue;
        } else if (opt == 4) {
            arma.reload(10);
            log.adauga("Reincarcare in " + camera.getNume());
            continue;
        } else {
            cout << "Fugi din camera!\n";
            log.adauga("Fuga din " + camera.getNume());
            break;
        }

        if (inamic->isAlive()) {
            int dmgPrimit = inamic->attack();
            p.takeDamage(dmgPrimit);
            cout << inamic->getNume() << " te ataca! Primesti " << dmgPrimit
                 << " damage! HP ramas: " << p.getHP() << "\n";
        }
    }
}

bool bossFight(Player& p, GameLog<string>& log) {
    MrX mrx("Mr. X", 300, 25);
    cout << "\n============================\n";
    cout << "    MR. X A APARUT!\n";
    cout << mrx << "\n";
    cout << "============================\n";

    while (mrx.isAlive() && p.isAlive()) {
        cout << "\nMrX HP: " << mrx.getHP() << " | Tu: " << p.getHP() << " HP\n";
        cout << "1. Trage  2. Inventar\n";
        cout << "Optiune: ";
        int opt; cin >> opt;

        if (opt == 1) {
            int wIdx = 0;
            if ((int)p.getWeapons().size() > 1) {
                cout << "Cu ce arma tragi?\n";
                for (int w = 0; w < (int)p.getWeapons().size(); w++)
                    cout << w + 1 << ". " << p.getWeapon(w).getNume()
                         << " | dmg: " << p.getWeapon(w)[0]
                         << " | ammo: " << p.getWeapon(w)[1] << "\n";
                cout << "Arma: ";
                cin >> wIdx;
                wIdx = max(1, min(wIdx, (int)p.getWeapons().size())) - 1;
            }
            try {
                Weapon& arma = p.getWeapon(wIdx);
                int dmg;
                if (rand() % 5 == 0) {
                    dmg = arma.lovituraCritica();
                    cout << "LOVITURA CRITICA! (" << dmg << " damage)\n";
                } else {
                    dmg = arma[0];
                }
                arma.fire();
                mrx.takeDamage(dmg);
                cout << "Ai dat " << dmg << " damage lui MrX!\n";
            } catch (NoAmmoException& e) {
                cout << "Eroare: " << e.what() << "\n";
            }
        } else {
            afiseazaInventar();
            vector<Item*> items = p.getInventory();
            if (!items.empty()) {
                cout << "Foloseste item (0 = anuleaza): ";
                int idx; cin >> idx;
                if (idx > 0 && idx <= (int)items.size())
                    items[idx - 1]->use(p);
            }
            continue;
        }

        if (mrx.isAlive()) {
            int dmg = mrx.attack();
            p.takeDamage(dmg);
            cout << "MrX te ataca! Primesti " << dmg
                 << " damage! HP ramas: " << p.getHP() << "\n";
        }
    }

    if (!p.isAlive()) {
        log.adauga("Mort in lupta cu MrX");
        return false;
    }
    log.adauga("MrX invins!");
    return true;
}

bool gameloop(Player& p, vector<Room>& camere) {
    map<string, int> killCount;
    GameLog<string> log("Evenimente joc");
    GameLog<int> damageLog("Damage dealt");

    for (int i = 0; i < (int)camere.size(); i++) {
        cout << "\n=============================\n";
        cout << "Intri in: " << camere[i].getNume() << "\n";

        if (i == (int)camere.size() - 1) {
            if (!bossFight(p, log)) {
                cout << "\n=== GAME OVER ===\n";
                cout << "\n--- Statistici kills ---\n";
                for (auto& pereche : killCount)
                    cout << pereche.first << ": " << pereche.second << "\n";
                damageLog.afiseaza();
                log.afiseaza();
                return false;
            }
            cout << "\n=== AI CASTIGAT! Ai scapat din Raccoon City! ===\n";
            cout << "\n--- Statistici kills ---\n";
            for (auto& pereche : killCount)
                cout << pereche.first << ": " << pereche.second << "\n";
            damageLog.afiseaza();
            log.afiseaza();
            return true;
        }

        if (camere[i].isLocked()) {
            try {
                bool areCheia = false;
                vector<Item*> inv = p.getInventory();
                for (size_t k = 0; k < inv.size(); k++) {
                    if (inv[k]->getTip() == "KeyItem") {
                        areCheia = true;
                        cout << "Folosesti " << inv[k]->getNume() << "! Usa s-a deschis.\n";
                        log.adauga("Usa deschisa in " + camere[i].getNume());
                        p.removeItem(inv[k]->getNume());
                        camere[i].setUsaInchisa(false);
                        break;
                    }
                }
                if (!areCheia) throw NoKeyException("Nu ai cheia pentru aceasta usa!");
            } catch (NoKeyException& e) {
                cout << "Eroare: " << e.what() << "\n";
                cout << "Cauta cheia mai intai! Sari peste camera.\n";
                continue;
            }
        }

        if (camere[i].hasEnemies()) {
            int nrInamici = (int)camere[i].getEnemies().size();
            int ammoRamas = p.getWeapon(0) - nrInamici;
            if (ammoRamas < 0)
                cout << "Atentie: s-ar putea sa nu ai gloante suficiente ("
                     << p.getWeapon(0).getAmmoCount() << " ammo, " << nrInamici << " inamici)!\n";
            cout << "Inamici detectati!\n";
            combat(p, camere[i], killCount, log, damageLog);
            if (!p.isAlive()) {
                cout << "\n=== GAME OVER ===\n";
                log.afiseaza();
                return false;
            }
        } else {
            cout << "Camera e libera.\n";
        }

        if (camere[i].hasItems()) {
            vector<Item*> itemsCamera = camere[i].getItems();
            for (size_t k = 0; k < itemsCamera.size(); k++) {
                cout << "Gasesti: " << itemsCamera[k]->getNume()
                     << " (" << itemsCamera[k]->getTip() << ")"
                     << ". Il iei? (1=Da / 0=Nu): ";
                int opt; cin >> opt;
                if (opt == 1) {
                    p.addItem(itemsCamera[k]);
                    cout << itemsCamera[k]->getNume() << " adaugat in inventar.\n";
                    log.adauga("Item luat: " + itemsCamera[k]->getNume());
                } else {
                    cout << "Lasi " << itemsCamera[k]->getNume() << " pe jos.\n";
                }
            }
        }

        if (i == (int)camere.size() - 2) {
            cout << "\nGasesti un Rocket Launcher (dmg: 100, rachete: 3) pe jos!\n";
            cout << "Il iei? (1=Da / 0=Nu): ";
            int opt; cin >> opt;
            if (opt == 1) {
                p.addWeapon(Weapon("Rocket Launcher", WeaponType::ROCKET_LAUNCHER, 100, 3));
                cout << "Rocket Launcher adaugat! Foloseste-l impotriva lui Mr. X.\n";
                log.adauga("Rocket Launcher ridicat");
            }
        }
    }

    cout << "\n--- Statistici kills ---\n";
    for (auto& pereche : killCount)
        cout << pereche.first << ": " << pereche.second << "\n";

    if (!p.getWeapons().empty()) {
        Weapon& arma = p.getWeapon(0);
        cout << "Arma finala: " << arma.getNume()
             << " | Damage: " << arma[0]
             << " | Damage maxim cu bonus +10: " << (10 + arma) << "\n";
    }

    log.afiseaza();
    return true;
}

vector<Enemy*> modCreator() {
    int n;
    cout << "Cate inamici vrei sa creezi? ";
    cin >> n;

    vector<Enemy*> obiecte;
    for (int i = 0; i < n; i++) {
        cout << "\nInamic " << i + 1 << " tip (1=Zombie, 2=Licker): ";
        int tip; cin >> tip;
        Enemy* e;
        if (tip == 1) 
            e = new Zombie();
        else         
            e = new Licker();
        cout << "Introdu datele:\n";
        cin >> *e;     
        obiecte.push_back(e);
    }

    cout << "\n=== Inamici creati (" << n << ") vor aparea in joc ===\n";
    for (int i = 0; i < (int)obiecte.size(); i++) {
        cout << "Inamic " << i + 1
             << " [" << typeid(*obiecte[i]).name() << "]:\n";
        cout << *obiecte[i];
        cout << "---\n";
    }

    return obiecte;
}

void meniu() {
    bool stop = false;
    int opt;
    while (!stop) {
        uiMeniu();
        cout << "Introd opt: ";
        if (!(cin >> opt)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input invalid. Reincearca.\n";
            continue;
        }
        switch (opt) {
            case 1: {
                Inventory::reset();
                Player p = selectCharacter();
                vector<Room> camere = generateRooms();
                gameloop(p, camere);
                break;
            }
            case 2: {
                Inventory::reset();
                Player p = selectCharacter();
                vector<Enemy*> inamici = modCreator();
                vector<Room> camere = generateRooms(inamici);
                gameloop(p, camere);
                break;
            }
            case 0:
                stop = true;
                break;
            default:
                cout << "Optiune nevalida! Incearca din nou.\n";
        }
        system("pause");
        system("cls");
    }
}

int main() {
    srand(time(0));
    meniu();
    return 0;
}
