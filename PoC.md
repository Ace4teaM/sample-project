# PoC — Tri de données mémoire et export texte

## 1. Objectif

Ce PoC a pour objectif de démontrer la réalisation d'un programme C++ capable de :

1. trier les octets (`bytes`) présents dans une zone mémoire pointée par un pointeur, par ordre croissant de leur valeur entière ;
2. effectuer ce tri **sans réallocation de la zone mémoire** ;
3. enregistrer le contenu trié dans un fichier texte.

Le PoC doit privilégier une implémentation simple, lisible et vérifiable.

------

## 2. Fonctionnalité 1 — Tri des bytes en mémoire

### Description

Le programme doit fournir une fonction permettant de trier les bytes d'une zone mémoire directement dans celle-ci.

La fonction reçoit :

- un pointeur vers le début de la zone mémoire ;
- le nombre de bytes à trier.

Exemple d'interface :

```cpp
void sortBytes(void* data, std::size_t size);
```

### Contraintes

- Le tri doit être réalisé **en place**.
- Aucune réallocation de la zone mémoire d'entrée ne doit être effectuée.
- Le pointeur fourni par l'appelant doit continuer à désigner la même zone mémoire après le tri.
- Les bytes doivent être classés selon leur valeur entière croissante.
- La fonction doit fonctionner avec une zone mémoire contenant des valeurs comprises entre `0` et `255`.
- L'algorithme ne doit pas dépendre d'un conteneur nécessitant une copie complète des données pour effectuer le tri.

### Exemple

Avant le tri :

```text
[42, 3, 255, 17, 3, 128]
```

Après le tri :

```text
[3, 3, 17, 42, 128, 255]
```

### Gestion des cas particuliers

La fonction doit gérer correctement :

- un pointeur nul ;
- une taille égale à `0` ;
- une zone contenant un seul byte ;
- une zone contenant uniquement des valeurs identiques ;
- une zone déjà triée ;
- une zone triée dans l'ordre inverse.

Le comportement attendu pour un pointeur nul doit être documenté dans le code.

------

## 3. Fonctionnalité 2 — Export du résultat

### Description

Le programme doit permettre d'enregistrer le contenu de la zone mémoire après le tri dans un fichier texte.

Exemple d'interface :

```cpp
bool saveBytesToFile(
    const void* data,
    std::size_t size,
    const std::string& filename
);
```

### Format du fichier

Chaque byte doit être représenté par sa valeur entière décimale.

Exemple :

```text
3
3
17
42
128
255
```

Un byte par ligne doit être utilisé afin de rendre le fichier facilement lisible et exploitable par d'autres outils.

### Contraintes

- Le fichier doit être créé s'il n'existe pas.
- Un fichier existant portant le même nom doit être remplacé.
- Les valeurs doivent être écrites sous forme décimale.
- Les erreurs d'ouverture ou d'écriture du fichier doivent être détectées.
- La fonction ne doit pas modifier les données en mémoire.

------

## 4. Programme de démonstration

Le projet doit fournir un programme permettant de démontrer les deux fonctionnalités.

Le programme devra :

1. créer une zone mémoire contenant plusieurs bytes non triés ;
2. afficher les valeurs initiales ;
3. trier les bytes en mémoire ;
4. afficher les valeurs après le tri ;
5. enregistrer le résultat dans un fichier texte ;
6. indiquer si l'export a réussi.

Exemple de sortie console :

```text
Données initiales :
42 3 255 17 3 128

Données après tri :
3 3 17 42 128 255

Export :
Résultat enregistré dans result.txt
```

------

## 5. Vérification de l'absence de réallocation

Le PoC doit permettre de vérifier que le tri est réalisé directement dans la zone mémoire fournie.

Avant l'appel au tri, conserver l'adresse du premier byte :

```cpp
auto* originalAddress = data;
```

Après le tri, vérifier que l'adresse de la zone mémoire est inchangée.

Le test doit également vérifier que les données ont bien été modifiées dans la zone mémoire originale.

Aucune nouvelle zone mémoire destinée à contenir l'ensemble des bytes triés ne doit être utilisée.

------

## 6. Tests

Le projet doit contenir des tests permettant notamment de vérifier :

### Tri

- tableau non trié ;
- tableau déjà trié ;
- tableau inversé ;
- valeurs dupliquées ;
- toutes les valeurs identiques ;
- tableau vide ;
- tableau contenant un seul élément ;
- valeurs `0` et `255`.

### Mémoire

Vérifier que :

- l'adresse de la zone mémoire reste identique ;
- les données originales sont modifiées directement ;
- aucune copie complète du tableau n'est nécessaire.

### Export

Vérifier :

- la création correcte du fichier ;
- le contenu du fichier ;
- l'ordre des valeurs ;
- l'écrasement d'un fichier existant ;
- la gestion d'un chemin ou fichier inaccessible.

------

## 7. Structure proposée

Une structure simple est attendue :

```text
PoC/
├── CMakeLists.txt
├── README.md
├── src/
│   ├── main.cpp
│   ├── byte_sort.cpp
│   └── byte_sort.h
├── tests/
│   └── byte_sort_tests.cpp
└── output/
```

Le code métier doit être séparé du programme de démonstration.

------

## 8. Contraintes techniques

- Langage : C++.
- Utiliser une version moderne du C++ compatible avec le compilateur disponible.
- Utiliser `std::uint8_t` pour représenter explicitement un byte.
- Utiliser `std::size_t` pour représenter les tailles.
- Éviter les allocations mémoire inutiles.
- Le code doit être compilable avec CMake.
- Le code doit être suffisamment documenté pour expliquer les choix d'implémentation.
- Les erreurs doivent être traitées explicitement.
- Aucun framework externe n'est requis pour les fonctionnalités principales.

------

## 9. Critères d'acceptation

Le PoC sera considéré comme fonctionnel lorsque :

-  le projet se compile avec CMake ;
-  le programme peut recevoir une zone mémoire contenant des bytes ;
-  les bytes sont triés par ordre croissant ;
-  le tri est réalisé directement dans la zone mémoire ;
-  aucune réallocation de la zone mémoire d'entrée n'est effectuée ;
-  les cas limites sont correctement traités ;
-  le contenu trié peut être exporté dans un fichier texte ;
-  le fichier contient une valeur décimale par ligne ;
-  les erreurs d'accès au fichier sont correctement détectées ;
-  des tests automatisés couvrent les principales fonctionnalités ;
-  le fonctionnement du PoC est démontré par `main.cpp`.

------

## 10. Résultat attendu

Le résultat final doit être un petit projet C++ autonome permettant de démontrer clairement :

**Mémoire → Tri en place → Export texte**

```text
Zone mémoire
     │
     ▼
┌───────────────┐
│ 42  3  255... │
└───────────────┘
     │
     │ tri en place
     ▼
┌───────────────┐
│ 3  3  17 ...  │
└───────────────┘
     │
     │ export
     ▼
┌────────────────┐
│ result.txt     │
│ 3              │
│ 3              │
│ 17             │
│ ...            │
└────────────────┘
```

Le PoC doit rester volontairement limité à ces deux fonctionnalités. Il ne doit pas introduire de fonctionnalités supplémentaires sans nécessité pour répondre aux critères d'acceptation.