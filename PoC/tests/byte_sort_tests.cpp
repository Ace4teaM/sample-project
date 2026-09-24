#include "byte_sort.h"

#include <array>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

struct TestCase {
    std::string name;
    std::function<void()> run;
};

void require(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void testSortUnsortedData() {
    std::vector<std::uint8_t> bytes{42, 3, 255, 17, 3, 128};
    sortBytes(bytes.data(), bytes.size());
    require(
        bytes == std::vector<std::uint8_t>({3, 3, 17, 42, 128, 255}),
        "unsorted bytes should be sorted in ascending order"
    );
}

void testSortEdgeCases() {
    std::vector<std::uint8_t> alreadySorted{0, 3, 17, 42, 255};
    sortBytes(alreadySorted.data(), alreadySorted.size());
    require(
        alreadySorted == std::vector<std::uint8_t>({0, 3, 17, 42, 255}),
        "already sorted input should stay sorted"
    );

    std::vector<std::uint8_t> reversed{255, 42, 17, 3, 0};
    sortBytes(reversed.data(), reversed.size());
    require(
        reversed == std::vector<std::uint8_t>({0, 3, 17, 42, 255}),
        "reverse-sorted input should be sorted"
    );

    std::vector<std::uint8_t> identical{7, 7, 7, 7};
    sortBytes(identical.data(), identical.size());
    require(
        identical == std::vector<std::uint8_t>({7, 7, 7, 7}),
        "identical values should remain unchanged"
    );

    std::vector<std::uint8_t> single{99};
    sortBytes(single.data(), single.size());
    require(single == std::vector<std::uint8_t>({99}), "single value should be preserved");

    std::vector<std::uint8_t> empty;
    sortBytes(empty.data(), empty.size());
    require(empty.empty(), "empty input should be handled");

    sortBytes(nullptr, 0);
}

void testSortKeepsSameAddressAndMutatesOriginalMemory() {
    std::array<std::uint8_t, 6> bytes{42, 3, 255, 17, 3, 128};
    auto* originalAddress = bytes.data();

    sortBytes(bytes.data(), bytes.size());

    require(bytes.data() == originalAddress, "sort should keep the same memory address");
    require(
        bytes == std::array<std::uint8_t, 6>{3, 3, 17, 42, 128, 255},
        "sort should modify the original memory directly"
    );
}

void testSaveBytesToFileCreatesExpectedContentAndOverwrites() {
    const auto tempDir = std::filesystem::temp_directory_path() / "byte_sort_tests";
    std::filesystem::create_directories(tempDir);

    const auto outputFile = tempDir / "result.txt";
    {
        std::ofstream seed(outputFile);
        seed << "old content\n";
    }

    const std::vector<std::uint8_t> bytes{3, 3, 17, 42, 128, 255};
    require(
        saveBytesToFile(bytes.data(), bytes.size(), outputFile.string()),
        "saveBytesToFile should succeed for a writable file"
    );

    std::ifstream input(outputFile);
    std::stringstream buffer;
    buffer << input.rdbuf();
    require(
        buffer.str() == "3\n3\n17\n42\n128\n255\n",
        "saveBytesToFile should write one decimal value per line and overwrite existing content"
    );
}

void testSaveBytesToFileFailureCases() {
    const auto tempDir = std::filesystem::temp_directory_path() / "byte_sort_tests_failure";
    std::filesystem::create_directories(tempDir);

    const std::vector<std::uint8_t> bytes{1, 2, 3};
    require(
        !saveBytesToFile(bytes.data(), bytes.size(), ""),
        "saveBytesToFile should reject an empty filename"
    );
    require(
        !saveBytesToFile(nullptr, bytes.size(), (tempDir / "null.txt").string()),
        "saveBytesToFile should reject null data when size is non-zero"
    );
    require(
        !saveBytesToFile(bytes.data(), bytes.size(), tempDir.string()),
        "saveBytesToFile should fail when the path is not a writable file"
    );
    require(
        saveBytesToFile(nullptr, 0, (tempDir / "empty.txt").string()),
        "saveBytesToFile should allow creating an empty file for empty input"
    );
}

void testSaveBytesToFileReportsFlushFailure() {
    if (!std::filesystem::exists("/dev/full")) {
        return;
    }

    const std::vector<std::uint8_t> bytes{1, 2, 3};
    require(
        !saveBytesToFile(bytes.data(), bytes.size(), "/dev/full"),
        "saveBytesToFile should fail when the stream cannot be finalized"
    );
}

}  // namespace

int main() {
    const std::vector<TestCase> tests{
        {"testSortUnsortedData", testSortUnsortedData},
        {"testSortEdgeCases", testSortEdgeCases},
        {"testSortKeepsSameAddressAndMutatesOriginalMemory", testSortKeepsSameAddressAndMutatesOriginalMemory},
        {"testSaveBytesToFileCreatesExpectedContentAndOverwrites", testSaveBytesToFileCreatesExpectedContentAndOverwrites},
        {"testSaveBytesToFileFailureCases", testSaveBytesToFileFailureCases},
        {"testSaveBytesToFileReportsFlushFailure", testSaveBytesToFileReportsFlushFailure},
    };

    bool hasFailure = false;
    for (const auto& test : tests) {
        try {
            test.run();
            std::cout << "[PASS] " << test.name << '\n';
        } catch (const std::exception& exception) {
            hasFailure = true;
            std::cerr << "[FAIL] " << test.name << ": " << exception.what() << '\n';
        }
    }

    return hasFailure ? 1 : 0;
}
