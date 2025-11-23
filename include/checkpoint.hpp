#ifndef CHECKPOINT_H
#define CHECKPOINT_H


#include <array>
#include <string>


extern std::array<int, 3> mapLookup;

extern std::array<std::string, 3> spawnLookup;


void updateSave(std::string fileName, int newCheckpoint);

int readSave(std::string fileName);


#endif