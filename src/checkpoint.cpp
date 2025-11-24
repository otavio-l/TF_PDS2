#include "checkpoint.hpp"
#include <fstream>


std::array<int, 3> mapLookup {
    9,
    2,
    0
};

std::array<std::string, 3> spawnLookup {
    "right",
    "below-church",
    "down"
};


int readSave(std::string fileName) {
    std::fstream file(fileName, std::ios::in);
    if (!file) {
        throw std::runtime_error(fileName + " could not be opened");
    }
    int checkpoint;
    file >> checkpoint;
    file.close();

    return checkpoint;
}

void updateSave(std::string fileName, int newCheckpoint) {
    std::ofstream out(fileName, std::ios::trunc);
    if (!out) {
        throw std::runtime_error(fileName + " could not be opened");
    }
    out << newCheckpoint;
}
