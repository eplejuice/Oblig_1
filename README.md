Navn: Martin Brådalen

Studentnr: 473145

Klasse: 16HBITSECA

# IMT2282 Operativsystemer: Oblig 1 - Programmering i C.

Filen oblig1_3.c og dining.c ble laget i samarbeid med Per-Kristian Kongelf Buer (https://github.com/CelebornBrian/IMT-2282-Operating-Systems/tree/master/Oblig1).



## Alle c filer kan kompileres med kommendoen (inkluderer alle warnings og threads):
    gcc -pthread -Wall -o <filename> <filename.c>

## Så kjøre programmet med:
    ./<filename>

## Koden har blitt kvaitetsikret med clang-tidy:

### clang-tidy kan installeres på ubuntu med kommandoene
    sudo apt-install clang
    sudo apt-install clang-tidy
    
### Så kjøres med kommandoen:
    clang-tidy -checks='*' -system-headers -header-filter=.* <filnavn>.c -- -std=c11

Dette returnerte mange warnings i include filer og header filer, disse kan jeg ikke gjøre noe med og valge derfor å bruke:
`clang-tidy -checks='*' <filnavn>.c -- -std=c11`
Denne returnerte 23 warnings, som ble supressed fordi de var i non-user code.
