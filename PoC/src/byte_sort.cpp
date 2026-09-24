#include "byte_sort.h"

#include <algorithm>
#include <fstream>

void sortBytes(void* data, std::size_t size) {
    if (data == nullptr || size < 2) {
        return;
    }

    auto* bytes = static_cast<std::uint8_t*>(data);
    std::sort(bytes, bytes + size);
}

bool saveBytesToFile(
    const void* data,
    std::size_t size,
    const std::string& filename
) {
    if (filename.empty()) {
        return false;
    }

    if (data == nullptr && size > 0) {
        return false;
    }

    std::ofstream output(filename, std::ios::out | std::ios::trunc);
    if (!output.is_open()) {
        return false;
    }

    const auto* bytes = static_cast<const std::uint8_t*>(data);
    for (std::size_t index = 0; index < size; ++index) {
        output << static_cast<unsigned int>(bytes[index]) << '\n';
        if (!output) {
            return false;
        }
    }

    output.flush();
    if (!output) {
        return false;
    }

    output.close();
    return !output.fail();
}
