# Resident Evil 2 but text based

A terminal-based survival game set in the Resident Evil 2 universe. The player fights through ten rooms of Raccoon City — clearing zombies and lickers, managing ammo and healing items, and surviving a final encounter with Mr. X. A second mode lets the player design custom enemies that are injected into the level before play begins.

## Features

- Character selection: Leon (Beretta M9) or Claire (Shotgun W-870), or a fully custom weapon defined at runtime
- Ten procedurally-named rooms with randomized enemy placement (Zombie / Licker)
- Turn-based combat: shoot, use inventory items, reload, or flee
- Critical hit system (20% chance for double damage)
- Weapon upgrade after 3 total kills
- Locked room requiring a key item found earlier in the level
- Rocket Launcher pickup in the penultimate room (100 dmg, 3 shots)
- Final boss fight against Mr. X with multi-weapon selection
- Ammo pickups that reload the active weapon
- Heal items (spray, herbs) usable from inventory during combat
- Custom enemy mode: define N enemies (Zombie or Licker) with custom stats that populate the level
- Kill statistics and full game event log printed at end of session
- Singleton inventory persisted across rooms, reset between game sessions

## How to Run

```bash
g++ -std=c++17 -Iinclude main.cpp source/*.cpp -o game
./game
```

On Windows:
```bash
g++ -std=c++17 -Iinclude main.cpp source/*.cpp -o game.exe
game.exe
```

> Names entered during custom enemy creation must not contain spaces.

---

## Requirements Coverage

### Tema 1

| Requirement | Implementation |
|---|---|
| Interactive menu with input validation | `meniu()` — `main.cpp`; `cin` fail state cleared with `clear()`/`ignore()`, default case on all switches |
| No global variables | All state in class members; `Weapon::numarArme` and `Inventory::instanta` are static members |
| All data members private | Enforced across all 13 classes |
| Minimum 3 classes | 13 classes: `Weapon`, `Player`, `Room`, `Enemy`, `Zombie`, `Licker`, `MrX`, `Item`, `Heal`, `Ammo`, `KeyItem`, `Inventory`, `GameLog` |
| Composition | `Room` owns `Enemy*` — deleted in `Room::~Room()` (`Room.cpp:18`) |
| Aggregation | `Room` holds `Item*` without owning them — `items.clear()` in destructor, no delete |
| Init constructor | `Weapon(const string&, WeaponType, int, int)` — `Weapon.cpp:22` |
| Copy constructor | `Weapon(const Weapon&)` — `Weapon.cpp:30` |
| `operator=` | Self-assignment check, full field copy — `Weapon.cpp:42` |
| Destructor | `~Weapon()` decrements `numarArme` — `Weapon.cpp:38` |
| `operator<<` | Friend non-member — `Weapon.cpp:52` |
| `operator>>` | Friend, delegates to `citire()` — `Weapon.cpp:80` |
| Member operator | `operator[]`, `operator++`, `operator+`, `operator-`, `operator==`, `operator<` — `Weapon.cpp` |
| Non-member operator | `friend int operator+(int, const Weapon&)` — `Weapon.cpp:100` |
| 3+ non-trivial public methods | `fire()` (ammo logic + exception), `lovituraCritica()` (double damage), `reload(int)` — `Weapon.cpp:122-141` |
| Read/display n objects | `modCreator()` — `main.cpp:383`; reads n enemies, user picks derived type per object, displays each with `typeid` |

### Tema 2

| Requirement | Implementation |
|---|---|
| 2+ base classes | `Enemy` (`Enemy.h`) and `Item` (`Item.h`), both abstract |
| Hierarchy with 2-3 derived | `Enemy` → `Zombie`, `Licker`, `MrX`; `Item` → `Heal`, `Ammo`, `KeyItem` |
| Derived calls parent constructor | All 6 derived classes use initializer list — e.g. `Zombie(...) : Enemy(...)` (`Zombie.cpp:5`) |
| Derived copy constructor | `Zombie(const Zombie& altul) : Enemy(altul)` (`Zombie.cpp:9`); same pattern in all derived |
| Derived `operator=` | Calls `Base::operator=(altul)` — `Zombie.cpp:15`, `Licker.cpp:15`, `MrX.cpp`, `Heal.cpp:17`, `Ammo.cpp:17`, `KeyItem.cpp:17` |
| `const` throughout | All getters `const`, parameters `const&` across all classes |
| Static data member | `Weapon::numarArme` — tracks live instances, incremented/decremented in all constructors/destructor (`Weapon.cpp:8`) |
| Static member function | `Inventory::getInstance()`, `Inventory::reset()` — `Inventory.cpp:8,14` |
| Two custom exceptions | `NoAmmoException`, `NoKeyException` — `GameExceptions.h:8-22`; inherit `std::exception`, override `what()` |
| Exceptions thrown and caught | `NoAmmoException`: thrown `Weapon.cpp:130`, caught `main.cpp:180,250`; `NoKeyException`: thrown and caught `main.cpp:314-319` |
| Abstract class | `Enemy::attack()` pure virtual (`Enemy.h:18`); `Item::use()` pure virtual (`Item.h:21`) |
| Enum class | `WeaponType { PISTOL, SHOTGUN, ROCKET_LAUNCHER }` — `Weapon.h:6`; drives `fire()`, display, and input |
| Upcast | `new Zombie(...)` passed to `addEnemy(Enemy*)` in `generateRooms()` (`main.cpp:89`); `static_cast<const Enemy&>` in `Zombie.cpp:24` |
| Downcast with nullptr check | `if (Zombie* z = dynamic_cast<Zombie*>(inamic))` — `combat()`, `main.cpp:132`; stored pointer used to call `z->isDecapitated()` |
| Two STL containers | `vector` (rooms, enemies, items, weapons) and `map<string, int>` (`killCount` — `main.cpp:282`) |
| n-object read with type choice | `modCreator()` `main.cpp:390`: each object prompts "1=Zombie / 2=Licker", reads via virtual `citire()` |

### Tema 3

| Requirement | Implementation |
|---|---|
| Singleton | `Inventory`: private constructor, `static Inventory* instanta` (`Inventory.cpp:6`), `getInstance()` lazy init (`Inventory.cpp:8`) |
| Template class | `GameLog<T>` — `GameLog.h:8`; used as `GameLog<string>` in `gameloop()` and `bossFight()` |
| `dynamic_cast` with runtime check | `Zombie* z = dynamic_cast<Zombie*>(inamic)` — `combat()`, `main.cpp:132`; pointer stored and used after check |
| `typeid` | `typeid(*obiecte[i]).name()` — `modCreator()`, `main.cpp:403` |
| Virtual dispatch | `e.afisare(out)` and `e.citire(in)` through `Enemy&` (`Enemy.cpp:29,34`); `inamic->attack()` (`main.cpp:205`); `item->use(p)` (`main.cpp:191`) |
| Virtual destructor on base classes | `virtual ~Enemy()` (`Enemy.h:14`), `virtual ~Item()` (`Item.h:19`) |

---

## Project Structure

| File | Contents |
|---|---|
| `main.cpp` | Entry point, menu, `selectCharacter()`, `generateRooms()`, `combat()`, `bossFight()`, `gameloop()`, `modCreator()` |
| `include/Weapon.h` / `source/Weapon.cpp` | Main class with all operators, `WeaponType` enum, `fire()`, `reload()`, `lovituraCritica()`, static instance counter |
| `include/Player.h` / `source/Player.cpp` | Player with HP and weapon vector; delegates all item operations to the `Inventory` singleton |
| `include/Room.h` / `source/Room.cpp` | Game room holding enemy and item pointers; owns enemies (composition), borrows items (aggregation) |
| `include/Enemy.h` / `source/Enemy.cpp` | Abstract base for all enemies; `attack()` pure virtual; `citire()`/`afisare()` virtual for polymorphic I/O |
| `include/Zombie.h` / `source/Zombie.cpp` | Derived enemy; tracks decapitation state; halved damage when decapitated |
| `include/Licker.h` / `source/Licker.cpp` | Derived enemy; doubled damage after first attack |
| `include/MrX.h` / `source/MrX.cpp` | Boss enemy; 300 HP, 25 damage per hit |
| `include/Item.h` / `source/Item.cpp` | Abstract base for all items; `use()` pure virtual |
| `include/Heal.h` / `source/Heal.cpp` | Restores player HP on use |
| `include/Ammo.h` / `source/Ammo.cpp` | Reloads active weapon with stored bullet quantity on use |
| `include/KeyItem.h` / `source/KeyItem.cpp` | Unlocks locked rooms when present in inventory |
| `include/Inventory.h` / `source/Inventory.cpp` | Singleton item store; persists across rooms, reset between sessions via `reset()` |
| `include/GameLog.h` | Template class logging game events as `vector<T>`; displayed at session end |
| `include/GameExceptions.h` | `NoAmmoException`, `NoKeyException`, `NoHealException` — all inherit `std::exception` with `what()` |
