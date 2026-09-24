#include "byte_sort.h"
#include "byte_sort_internal.h"

#include <algorithm>
#include <fstream>

void sortBytes(void* data, std::size_t size) {
    if (data == nullptr || size < 2) {
        return;
    }

    auto* bytes = static_cast<std::uint8_t*>(data);
    std::sort(bytes, bytes + size);
}

namespace byte_sort::detail {

bool writeBytesToStream(const void* data, std::size_t size, std::ostream& output) {
    if (data == nullptr && size > 0) {
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
    return static_cast<bool>(output);
}

}  // namespace byte_sort::detail

bool saveBytesToFile(
    const void* data,
    std::size_t size,
    const std::string& filename
) {
    if (filename.empty()) {
        return false;
    }

    std::ofstream output(filename, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!output.is_open()) {
        return false;
    }

    if (!byte_sort::detail::writeBytesToStream(data, size, output)) {
        return false;
    }

    output.close();
    return !output.fail();
}
