# Contexte du projet pour les agents IA

## Objectif

Ce dépôt sert à préparer un PoC C++ qui doit démontrer qu'il est techniquement possible de :

1. trier des bytes en mémoire directement dans la zone fournie ;
2. conserver la même adresse mémoire avant et après le tri ;
3. exporter le résultat trié dans un fichier texte, avec une valeur décimale par ligne.

Le PoC peut être simple et pragmatique. L'objectif n'est pas l'industrialisation, mais la démonstration de faisabilité technique.

## Source de vérité

Le document `/home/runner/work/sample-project/sample-project/PoC.md` décrit le besoin fonctionnel et technique de référence :

- tri en place de `std::uint8_t` ;
- absence de réallocation de la zone mémoire ;
- export texte ;
- programme de démonstration ;
- cas limites et tests attendus ;
- structure de projet C++ proposée.

## État actuel du dépôt

À ce stade, le dépôt contient surtout la spécification du PoC. L'implémentation C++ décrite dans `PoC.md` n'est pas encore présente.

## Structure cible attendue

`PoC.md` propose une structure de travail simple autour d'un sous-répertoire `PoC/` contenant notamment :

- un `CMakeLists.txt` ;
- du code source dans `src/` ;
- des tests dans `tests/` ;
- un répertoire `output/`.

## Points d'attention pour les agents

- privilégier des changements minimaux et ciblés ;
- garder le code métier séparé du programme de démonstration ;
- documenter explicitement le comportement sur pointeur nul ;
- vérifier les cas limites listés dans `PoC.md` ;
- rester aligné avec les critères d'acceptation de `PoC.md`.
