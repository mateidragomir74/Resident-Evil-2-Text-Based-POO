cmake_minimum_required(VERSION 3.10)
project(RE2)

set(CMAKE_CXX_STANDARD 17)

add_executable(RE2
    main.cpp
    source/Item.cpp
    source/Weapon.cpp
    source/Enemy.cpp
    source/Room.cpp
    source/Player.cpp
    source/Zombie.cpp
    source/Licker.cpp
    source/MrX.cpp
    source/Inventory.cpp
    source/Ammo.cpp
    source/Heal.cpp
    source/KeyItem.cpp
)

target_include_directories(RE2 PRIVATE include)
