#include "byte_sort.h"

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <vector>

namespace {

void printBytes(const std::vector<std::uint8_t>& bytes) {
    for (std::size_t index = 0; index < bytes.size(); ++index) {
        if (index > 0) {
            std::cout << ' ';
        }
        std::cout << static_cast<unsigned int>(bytes[index]);
    }
    std::cout << '\n';
}

}  // namespace

int main() {
    std::vector<std::uint8_t> bytes{42, 3, 255, 17, 3, 128};
    auto* originalAddress = bytes.data();

    std::cout << "Données initiales :\n";
    printBytes(bytes);

    sortBytes(bytes.data(), bytes.size());

    std::cout << "\nDonnées après tri :\n";
    printBytes(bytes);

    std::cout << "\nVérification mémoire :\n";
    std::cout << (originalAddress == bytes.data()
            ? "Adresse mémoire inchangée"
            : "Adresse mémoire modifiée")
              << '\n';

    std::filesystem::create_directories("output");
    const std::string outputFile = "output/result.txt";

    std::cout << "\nExport :\n";
    if (saveBytesToFile(bytes.data(), bytes.size(), outputFile)) {
        std::cout << "Résultat enregistré dans " << outputFile << '\n';
        return 0;
    }

    std::cout << "Échec de l'export vers " << outputFile << '\n';
    return 1;
}
