#pragma once
#include <iostream>
#include <vector>
#include <string>
//clasa template pentru logul evenimentelor din joc, stocheaza intrari de tip T, afiseaza lista numerotata
//cerinta: clasa template (tema 3), instanciata cu string in gameloop

template <typename T>
class GameLog {
private:
    std::vector<T> intrari;
    std::string nume;
public:
    GameLog(std::string nume) : nume(nume) {}

    void adauga(const T& intrare) {
        intrari.push_back(intrare);
    }

    void afiseaza() const {
        std::cout << "=== " << nume << " ===\n";
        for (size_t i = 0; i < intrari.size(); i++)
            std::cout << i + 1 << ". " << intrari[i] << "\n";
    }

    int size() const { return intrari.size(); }
};