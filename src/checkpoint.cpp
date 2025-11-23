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
    // TODO: exception when file doesn't exist
    std::fstream file(fileName, std::ios::in);
    int checkpoint;
    file >> checkpoint;
    file.close();

    return checkpoint;
}

void updateSave(std::string fileName, int newCheckpoint) {
    std::ofstream out(fileName, std::ios::trunc);
    out << newCheckpoint;
}
