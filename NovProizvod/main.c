#include "defs.h"
#include "util.h"
#include "adts.h"
#include "misc.h"

void meniTransakciona();
void meniMaticna();
void meniPomoc();
void meniDemo();

int main(int argc, char* argv[]) {
    int opcija;

    inicijalizujAplikaciju();

    do {
        ocistiEkran();

        prikaziGlavniMeni();
        opcija = ucitajOpciju();

        switch (opcija) {
        case 1: meniTransakciona(); break;
        case 2: meniMaticna(); break;
        case 3: meniPomoc(); break;
        case 0: printf("\nProgram je uspesno zavrsen.\n"); break;

        default: printf("\nPogresan izbor!\n"); pauziraj();
        }
    } while (opcija != 0);

    return 0;
}

void meniTransakciona() {
    int opcija;

    do {
        ocistiEkran();
        prikaziMeniTransakciona();

        opcija = ucitajOpciju();

        switch (opcija) {
        case 1: kreirajTransakcionu(); break;
        case 2: unistiTransakcionu(); break;
        case 3: dodajTransakciju(); break;
        case 4: prikaziSveTransakcije(); break;
        case 5: prikaziTransakcijeProizvoda(); break;
        case 0: break;
        default: printf("\nPogresan izbor!\n"); pauziraj();
        }
    } while (opcija != 0);
}

void meniMaticna() {
    int opcija;

    do {
        ocistiEkran();

        prikaziMeniMaticna();
        opcija = ucitajOpciju();

        switch (opcija) {
        case 1: kreirajMaticnu(); break;
        case 2: unistiMaticnu(); break;
        case 3: dodajProizvod(); break;
        case 4: obrisiProizvod(); break;
        case 5: azurirajSve(); break;
        case 6: azurirajProizvod(); break;
        case 7: prikaziSveProizvode(); break;
        case 8: prikaziProizvod(); break;
        case 0: break;
        default: printf("\nPogresan izbor!\n"); pauziraj();
        }
    } while (opcija != 0);
}

void meniPomoc() {
    int opcija;

    do {
        ocistiEkran();
        prikaziMeniPomoc();

        opcija = ucitajOpciju();

        switch (opcija) {
        case 1: prikaziOAzuriranju(); break;
        case 2: meniDemo(); break;
        case 3: prikaziONama(); break;
        case 0: break;
        default: printf("\nPogresan izbor!\n"); pauziraj();
        }
    } while (opcija != 0);
}

void meniDemo() {
    int opcija;

    do {
        ocistiEkran();
        prikaziMeniDemo();
        opcija = ucitajOpciju();

        switch (opcija) {
        case 1: prikaziDemo1(); break;
        case 2: prikaziDemo2(); break;
        case 3: prikaziDemo3(); break;
        case 4: prikaziDemo4(); break;
        case 5: prikaziDemo5(); break;
        case 0: break;
        default: printf("\nPogresan izbor!\n"); pauziraj();
        }
    } while (opcija != 0);
}