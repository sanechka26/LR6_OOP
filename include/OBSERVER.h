#pragma once

#include <string>
#include <iostream>
#include <fstream>

class OBSERVER
{
public:
    virtual void update(std::string message) = 0;
};

class Observer_File : public OBSERVER {
private:
    std::ofstream out;
public:
    Observer_File() {
        out.open("log.txt", std::ios::app);
        if (!out.is_open()) {
            throw std::runtime_error("Cannot open log file");
        }
    }

    ~Observer_File() {
        if (out.is_open()) {
            out.close();
        }
    }

    void update(std::string message) override {
        out << message << std::endl;
    }
};

class Observer_CMD : public OBSERVER
{
public:
    void update(std::string message) {
        std::cout << message << std::endl;
    };
};