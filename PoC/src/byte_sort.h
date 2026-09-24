#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

// Si `data` est nul ou si `size` vaut 0 ou 1, la fonction ne fait rien.
void sortBytes(void* data, std::size_t size);

// Écrit un byte par ligne sous forme décimale dans `filename`, en remplaçant
// un éventuel fichier existant. Le fichier est écrit avec des fins de ligne
// `\n` stables entre plateformes. La fonction retourne `false` si le nom de
// fichier est vide, si `data` est nul alors que `size` est non nul, si
// l'ouverture échoue ou si l'écriture/finalisation du flux échoue. Quand
// `size` vaut 0, un fichier vide peut être créé même si `data` est nul.
bool saveBytesToFile(
    const void* data,
    std::size_t size,
    const std::string& filename
);
