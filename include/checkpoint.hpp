#ifndef CHECKPOINT_H
#define CHECKPOINT_H


#include <array>
#include <string>


extern std::array<int, 3> mapLookup;

extern std::array<std::string, 3> spawnLookup;

/**
 * @brief Sobrescreve o arquivo com o número passado 
 * 
 * @param fileName Nome do arquivo a ser sobreescrito 
 * @param newCheckpoint Novo conteúdo do arquivo
 */
void updateSave(std::string fileName, int newCheckpoint);

/**
 * @brief Lê o número contido no arquivo
 * 
 * @param fileName Nome do arquivo a ser
 * @return int Número contido no arquivo
 */
int readSave(std::string fileName);


#endif