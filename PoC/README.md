# PoC C++ — Tri en place et export texte

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Exécution

```bash
./build/byte_sort_demo
ctest --test-dir build --output-on-failure
```
