#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

// Si `data` est nul ou si `size` vaut 0 ou 1, la fonction ne fait rien.
void sortBytes(void* data, std::size_t size);

bool saveBytesToFile(
    const void* data,
    std::size_t size,
    const std::string& filename
);
