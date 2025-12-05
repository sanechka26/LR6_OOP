#include "../include/observer.h"
#include <iostream>
#include <fstream>
#include <string>

class ConsoleLogger : public Observer {
public:
    void update(const std::string& event) override {
        std::cout << "[CONSOLE] " << event << '\n';
    }
};

class FileLogger : public Observer {
private:
    std::string filename;
public:
    explicit FileLogger(const std::string& fname = "log.txt") : filename(fname) {}

    void update(const std::string& event) override {
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << "[FILE] " << event << '\n';
            file.close();
        }
    }
};

static ConsoleLogger console_logger;
static FileLogger file_logger;

Observer* getConsoleLogger() { return &console_logger; }
Observer* getFileLogger()     { return &file_logger; }