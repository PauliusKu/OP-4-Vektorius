# 4-oji Objektinio programavimo užduotis
# Vektorius

## Programos pagrindinės funkcijos:
 - visos pagrindinės funkcijos sutampa su std::vector funkcijomis;
 - didesnė dalis iš jų veikia be trūkumų :)
 
 ## Spartos analizė:

### push_back funkcijos palyginimas

| Flag| Container      |  100000 |  1000000 |  10000000 |  100000000 |
| ------------| ------------- |--------| --------|--------|--------|
| -Od | std::vector      | 0.0069277 | 0.072547 | 0.149451 | 6.331194 |
| -Od | Vector   | 0.0009989  |   0.0139792 | 0.425403 | 1.1659 |
| -O1 | std::vector     | 0.000688822 | 0.00853663 | 0.102232 | 1.0339 |
| -O1 | Vector   | 0.000475898  |   0.00469991 | 0.073763 | 0.639343 |
| -O2 | std::vector     | 0.000729848 |0.00916966 |0.0892305| 0.869269 |
| -O2 | Vector   | 0.00120739  |   0.00875899 | 0.0919571  | 0.641582 |


### Vektoriaus veikimo greičių palyginimas Mokinio pažymių programoje

| Container      |  100 |  1000 |  10000 |  100000 |
| ------------- |--------| --------|--------|--------|
| std::vector      | 0.0039465 | 0.0450352 | 0.259778 | 2.4382054 |
| Vector   | 0.0009858 | 0.030912 | 0.225556 | 3.149406 |

## Versijos:

### [Changelog v1.0 Daugelis dalykų veikia](https://github.com/PauliusKu/OP-4-Vektorius/releases/tag/v1.0)

#### Pridėta
- Vektorius klasė
- ReadMe.md failas
#### Koreguota 
#### Panaikinta
