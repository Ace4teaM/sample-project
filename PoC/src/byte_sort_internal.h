#pragma once

#include <cstddef>
#include <iosfwd>

namespace byte_sort::detail {

bool writeBytesToStream(const void* data, std::size_t size, std::ostream& output);

}  // namespace byte_sort::detail
