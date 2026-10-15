#pragma once
#include <iostream>
#include <string>
#include <exception>
//trei exceptii proprii derivate din std::exception, noammoexception pentru arma fara gloante, nokeyexception pentru usa blocata, nohealexception pentru inventar gol
//cerinta: doua exceptii proprii tratate prin try/catch in weapon si gameloop (tema 2)

class NoAmmoException : public std::exception {
private:
    std::string message;
public:
    NoAmmoException(std::string msg = "Nu ai gloante!") : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class NoKeyException : public std::exception {
private:
    std::string message;
public:
    NoKeyException(std::string msg = "Nu ai cheia necesara!") : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class NoHealException : public std::exception {
private:
    std::string message;
public:
    NoHealException(std::string msg = "Nu ai iteme de vindecare!") : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

    
