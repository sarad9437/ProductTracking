#define _CRT_SECURE_NO_WARNINGS
#include "adts.h"
#include "util.h"

void ocistiBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ucitajID(unsigned* id) {
    char line[100];
    int result;

    do {
        printf("Unesite ID proizvoda: ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("GRESKA: Neispravan unos!\n");
            continue;
        }

        if (strchr(line, '-') != NULL) {
            printf("GRESKA: ID ne moze biti negativan!\n");
            continue;
        }

        result = sscanf(line, "%u", id);

        if (result != 1) {
            printf("GRESKA: Morate uneti broj!\n");
            continue;
        }
        if (*id < 1 || *id > 9999) {
            printf("GRESKA: ID mora biti u opsegu 1-9999!\n");
            continue;
        }
        return 1;
    } while (1);
}

int ucitajKolicinu(unsigned* kolicina) {
    char line[100];
    int result;

    do {
        printf("Unesite kolicinu: ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("GRESKA: Neispravan unos!\n");
            continue;
        }

        if (strchr(line, '-') != NULL) {
            printf("GRESKA: Kolicina ne moze biti negativna!\n");
            continue;
        }

        result = sscanf(line, "%u", kolicina);

        if (result != 1) {
            printf("GRESKA: Morate uneti broj!\n");
            continue;
        }
        if (*kolicina < 1 || *kolicina > 999999) {
            printf("GRESKA: Kolicina mora biti u opsegu 1-999999!\n");
            continue;
        }
        return 1;
    } while (1);
}

int ucitajPotvrdu(const char* pitanje) {
    char odg[10];
    do {
        printf("%s (D/N): ", pitanje);
        if (scanf("%9s", odg) != 1) {
            ocistiBuffer();
            printf("GRESKA: Neispravan unos!\n");
            continue;
        }
        ocistiBuffer();

        if (strcmp(odg, "D") == 0 || strcmp(odg, "d") == 0 ||
            strcmp(odg, "Da") == 0 || strcmp(odg, "da") == 0) {
            return 1;
        }
        if (strcmp(odg, "N") == 0 || strcmp(odg, "n") == 0 ||
            strcmp(odg, "Ne") == 0 || strcmp(odg, "ne") == 0) {
            return 0;
        }
        printf("GRESKA: Unesite D (da) ili N (ne)!\n");
    } while (1);
}

int ucitajPromenu(PROMENA* promena) {
    char prom[10];
    do {
        printf("Unesite promenu (ULAZ/IZLAZ): ");
        if (scanf("%9s", prom) != 1) {
            ocistiBuffer();
            printf("GRESKA: Neispravan unos!\n");
            continue;
        }
        ocistiBuffer();

        int i;
        for (i = 0; prom[i]; i++) {
            prom[i] = toupper((unsigned char)prom[i]);
        }

        if (strcmp(prom, "ULAZ") == 0) {
            *promena = ULAZ;
            return 1;
        }
        if (strcmp(prom, "IZLAZ") == 0) {
            *promena = IZLAZ;
            return 1;
        }
        printf("GRESKA: Unesite ULAZ ili IZLAZ!\n");
    } while (1);
}

void ocistiEkran() {
    system("cls");
}

void pauziraj() {
    printf("\nPritisnite ENTER za nastavak...");
    ocistiBuffer();
}

int ucitajOpciju() {
    int op;
    int result;

    printf("\nOpcija: ");
    result = scanf("%d", &op);
    ocistiBuffer();

    if (result != 1) {
        return -999;
    }
    return op;
}

void prikaziGlavniMeni() {
    printf("************************************************************************\n");
    printf("* Aplikacija: ASD - SLUCAJ 3 (Nov proizvod)\n");
    printf("* Opis      : Azuriranje serijske (sortirane redne) datoteke\n");
    printf("* Verzija   : 1.0\n");
    printf("* Upotreba  : NovProizvod.exe\n");
    printf("* Datum     : 03.02.2026.\n");
    printf("* Autor     : Sara Da Rold, sd20220413@student.fon.bg.ac.rs\n");
    printf("* Mentor    : Sasa D. Lazarevic, slazar@fon.rs\n");
    printf("************************************************************************\n\n");
    printf("==================================\n");
    printf("GLAVNI MENI\n");
    printf("==================================\n");
    printf("0. Kraj rada\n\n");
    printf("1. Rad sa transakcionom datotekom\n");
    printf("2. Rad sa maticnom datotekom\n");
    printf("3. Pomoc\n");
}

void prikaziMeniTransakciona() {
    printf("====================================================================\n");
    printf("MENI Transakciona datoteka\n");
    printf("====================================================================\n");
    printf("0. Povratak\n\n");
    printf("1. Create ::= Kreiranje nove transakcione datoteke\n");
    printf("2. Drop   ::= Unistavanje postojece transakcione datoteke\n");
    printf("3. Insert ::= Dodavanje nove transakcije\n");
    printf("4. Select All ::= Prikazivanje svih transakcija\n");
    printf("5. Select Id  ::= Prikazivanje svih transakcija jednog proizvoda\n");
}

void prikaziMeniMaticna() {
    printf("================================================================================\n");
    printf("MENI Maticna datoteka\n");
    printf("================================================================================\n");
    printf("0. Povratak\n\n");
    printf("1. Create     ::= Kreiranje nove maticne datoteke\n");
    printf("2. Drop       ::= Unistavanje postojece maticne datoteke\n");
    printf("3. Insert     ::= Dodavanje novog proizvoda\n");
    printf("4. Delete     ::= Brisanje postojeceg proizvoda\n");
    printf("5. Update All ::= Azuriranje maticne datoteke upotrebom transakcione datoteke\n");
    printf("6. Update Id  ::= Azuriranje jednog proizvoda\n");
    printf("7. Select All ::= Prikazivanje svih proizvoda\n");
    printf("8. Select Id  ::= Prikazivanje jednog proizvoda\n");
}

void prikaziMeniPomoc() {
    printf("==================================\n");
    printf("MENI Pomoc\n");
    printf("==================================\n");
    printf("0. Povratak\n\n");
    printf("1. O azuriranju serijske datoteke\n");
    printf("2. Demo\n");
    printf("3. O nama\n");
}

void prikaziMeniDemo() {
    printf("=========================\n");
    printf("MENI Demo\n");
    printf("=========================\n");
    printf("0. Povratak\n\n");
    printf("1. Osnovni slucaj\n");
    printf("2. Nepostojeca kolicina\n");
    printf("3. Nov proizvod\n");
    printf("4. Nepostojeci proizvod\n");
    printf("5. Sveobuhvatni slucaj\n");
}

void kreirajMaticnu() {
    if (fajlPostoji(MAT_DAT)) {
        printf("\nU folderu sa podacima vec postoji maticna datoteka.\n");
        if (!ucitajPotvrdu("Da li zelite da je obrisete i kreirate novu maticnu datoteku?")) {
            printf("Operacija otkazana.\n");
            pauziraj();
            return;
        }
        if (remove(MAT_DAT) != 0) {
            printf("ERROR: Stara maticna datoteka nije obrisana.\n");
            pauziraj();
            return;
        }
    }

    FILE* f = fopen(MAT_DAT, "wb");
    if (!f) {
        printf("ERROR: Maticna datoteka nije kreirana (problem sa pravima pristupa).\n");
        pauziraj();
        return;
    }

    fclose(f);
    printf("INFO: Maticna datoteka je uspesno kreirana.\n");
    pauziraj();
}

void unistiMaticnu() {
    if (!fajlPostoji(MAT_DAT)) {
        printf("INFO: Maticna datoteka ne postoji.\n");
        pauziraj();
        return;
    }

    if (!ucitajPotvrdu("Da li ste sigurni da zelite da obrisete maticnu datoteku?")) {
        printf("Operacija otkazana.\n");
        pauziraj();
        return;
    }

    if (remove(MAT_DAT) == 0) {
        printf("INFO: Maticna datoteka je uspesno obrisana.\n");
    }
    else {
        printf("ERROR: Maticna datoteka nije obrisana (u upotrebi ili nema prava).\n");
    }
    pauziraj();
}

void dodajProizvod() {
    PROIZVOD p, temp[MAX_PROIZVODA];
    int n = 0, i;

    if (!ucitajID(&p.Id)) return;

    FILE* f = fopen(MAT_DAT, "rb");
    if (f) {
        PROIZVOD postojeci;
        while (fread(&postojeci, sizeof(PROIZVOD), 1, f) == 1) {
            if (postojeci.Id == p.Id) {
                fclose(f);
                printf("GRESKA: Proizvod sa ID=%u vec postoji!\n", p.Id);
                printf("        Postojeci: ID=%u, Naziv=%s, Kolicina=%u\n",
                    postojeci.Id, postojeci.Naziv, postojeci.Kolicina);
                pauziraj();
                return;
            }
        }
        fclose(f);
    }

    generisiNazivProizvoda(p.Id, p.Naziv);
    printf("Naziv proizvoda (generisan): %s\n", p.Naziv);

    if (!ucitajKolicinu(&p.Kolicina)) return;

    f = fopen(MAT_DAT, "rb");
    if (f) {
        while (fread(&temp[n], sizeof(PROIZVOD), 1, f) == 1) {
            n++;
            if (n >= MAX_PROIZVODA) {
                fclose(f);
                printf("GRESKA: Dostignut maksimalan broj proizvoda (%d)!\n", MAX_PROIZVODA);
                pauziraj();
                return;
            }
        }
        fclose(f);
    }

    temp[n++] = p;
    qsort(temp, n, sizeof(PROIZVOD), sortirajProizvode);

    f = fopen(MAT_DAT, "wb");
    if (!f) {
        printf("ERROR: Ne mogu da otvorim maticnu datoteku za upis!\n");
        pauziraj();
        return;
    }

    if (fwrite(temp, sizeof(PROIZVOD), n, f) != n) {
        printf("ERROR: Greska pri upisu u maticnu datoteku!\n");
        fclose(f);
        pauziraj();
        return;
    }

    fclose(f);
    printf("INFO: Proizvod je uspesno dodat.\n");
    pauziraj();
}

void obrisiProizvod() {
    unsigned id;
    PROIZVOD temp[MAX_PROIZVODA];
    int n = 0, i, found = -1;

    if (!ucitajID(&id)) return;

    FILE* f = fopen(MAT_DAT, "rb");
    if (!f) {
        printf("ERROR: Maticna datoteka ne postoji.\n");
        pauziraj();
        return;
    }

    while (fread(&temp[n], sizeof(PROIZVOD), 1, f) == 1) {
        if (temp[n].Id == id) found = n;
        n++;
    }
    fclose(f);

    if (n == 0) {
        printf("INFO: Maticna datoteka je prazna.\n");
        pauziraj();
        return;
    }

    if (found == -1) {
        printf("INFO: Proizvod sa ID=%u ne postoji.\n", id);
        pauziraj();
        return;
    }

    printf("\nProizvod: ID=%u, Naziv=%s, Kolicina=%u\n",
        temp[found].Id, temp[found].Naziv, temp[found].Kolicina);

    if (!ucitajPotvrdu("Da li ste sigurni da zelite da obrisete navedeni proizvod?")) {
        printf("Operacija otkazana.\n");
        pauziraj();
        return;
    }

    f = fopen(MAT_DAT, "wb");
    if (!f) {
        printf("ERROR: Ne mogu da otvorim maticnu datoteku za upis!\n");
        pauziraj();
        return;
    }

    for (i = 0; i < n; i++) {
        if (i != found) {
            if (fwrite(&temp[i], sizeof(PROIZVOD), 1, f) != 1) {
                printf("ERROR: Greska pri upisu!\n");
                fclose(f);
                pauziraj();
                return;
            }
        }
    }

    fclose(f);
    printf("INFO: Proizvod je uspesno obrisan.\n");
    pauziraj();
}

void azurirajProizvod() {
    unsigned id;
    PROIZVOD temp[MAX_PROIZVODA];
    int n = 0, i, found = -1;

    if (!ucitajID(&id)) return;

    FILE* f = fopen(MAT_DAT, "rb");
    if (!f) {
        printf("ERROR: Maticna datoteka ne postoji.\n");
        pauziraj();
        return;
    }

    while (fread(&temp[n], sizeof(PROIZVOD), 1, f) == 1) {
        if (temp[n].Id == id) found = n;
        n++;
    }
    fclose(f);

    if (n == 0) {
        printf("INFO: Maticna datoteka je prazna.\n");
        pauziraj();
        return;
    }

    if (found == -1) {
        printf("INFO: Proizvod sa ID=%u ne postoji.\n", id);
        pauziraj();
        return;
    }

    printf("\nTrenutni podaci: ID=%u, Naziv=%s, Kolicina=%u\n",
        temp[found].Id, temp[found].Naziv, temp[found].Kolicina);

    printf("\nNapomena: Naziv se automatski generise na osnovu ID-a i ne moze se menjati.\n");

    if (!ucitajKolicinu(&temp[found].Kolicina)) return;

    f = fopen(MAT_DAT, "wb");
    if (!f) {
        printf("ERROR: Ne mogu da otvorim maticnu datoteku za upis!\n");
        pauziraj();
        return;
    }

    if (fwrite(temp, sizeof(PROIZVOD), n, f) != n) {
        printf("ERROR: Greska pri upisu!\n");
        fclose(f);
        pauziraj();
        return;
    }

    fclose(f);
    printf("INFO: Proizvod je uspesno azuriran.\n");
    pauziraj();
}

void prikaziSveProizvode() {
    PROIZVOD p;
    FILE* f = fopen(MAT_DAT, "rb");
    int count = 0;

    if (!f) {
        printf("ERROR: Maticna datoteka ne postoji.\n");
        pauziraj();
        return;
    }

    printf("\n%-10s %-15s %-10s\n", "ID", "Naziv", "Kolicina");
    printf("--------------------------------------\n");

    while (fread(&p, sizeof(PROIZVOD), 1, f) == 1) {
        printf("%-10u %-15s %-10u\n", p.Id, p.Naziv, p.Kolicina);
        count++;
        if (count % PAGE_SIZE == 0) {
            printf("\n--- Pritisnite ENTER za nastavak ---");
            getchar();
        }
    }

    fclose(f);

    if (count == 0) {
        printf("INFO: Maticna datoteka je prazna.\n");
    }
    else {
        printf("\nUkupno proizvoda: %d\n", count);
    }

    pauziraj();
}

void prikaziProizvod() {
    unsigned id;
    PROIZVOD p;
    int found = 0;

    if (!ucitajID(&id)) return;

    FILE* f = fopen(MAT_DAT, "rb");
    if (!f) {
        printf("ERROR: Maticna datoteka ne postoji.\n");
        pauziraj();
        return;
    }

    while (fread(&p, sizeof(PROIZVOD), 1, f) == 1) {
        if (p.Id == id) {
            printf("\nProizvod: ID=%u, Naziv=%s, Kolicina=%u\n", p.Id, p.Naziv, p.Kolicina);
            found = 1;
            break;
        }
    }

    fclose(f);

    if (!found) {
        printf("INFO: Proizvod sa ID=%u ne postoji.\n", id);
    }
    pauziraj();
}

void kreirajTransakcionu() {
    if (fajlPostoji(TRAN_DAT)) {
        printf("\nU folderu sa podacima vec postoji transakciona datoteka.\n");
        if (!ucitajPotvrdu("Da li zelite da je obrisete i kreirate novu transakcionu datoteku?")) {
            printf("Operacija otkazana.\n");
            pauziraj();
            return;
        }
        if (remove(TRAN_DAT) != 0) {
            printf("ERROR: Stara transakciona datoteka nije obrisana.\n");
            pauziraj();
            return;
        }
    }

    FILE* f = fopen(TRAN_DAT, "wb");
    if (!f) {
        printf("ERROR: Transakciona datoteka nije kreirana.\n");
        pauziraj();
        return;
    }

    fclose(f);
    printf("INFO: Transakciona datoteka je uspesno kreirana.\n");
    pauziraj();
}

void unistiTransakcionu() {
    if (!fajlPostoji(TRAN_DAT)) {
        printf("INFO: Transakciona datoteka ne postoji.\n");
        pauziraj();
        return;
    }

    if (!ucitajPotvrdu("Da li ste sigurni da zelite da obrisete transakcionu datoteku?")) {
        printf("Operacija otkazana.\n");
        pauziraj();
        return;
    }

    if (remove(TRAN_DAT) == 0) {
        printf("INFO: Transakciona datoteka je uspesno obrisana.\n");
    }
    else {
        printf("ERROR: Transakciona datoteka nije obrisana.\n");
    }
    pauziraj();
}

void dodajTransakciju() {
    TRANSAKCIJA t;

    if (!ucitajID(&t.Id)) return;
    if (!ucitajPromenu(&t.Promena)) return;
    if (!ucitajKolicinu(&t.Kolicina)) return;

    FILE* f = fopen(TRAN_DAT, "ab");
    if (!f) {
        printf("ERROR: Ne mogu da otvorim transakcionu datoteku!\n");
        pauziraj();
        return;
    }

    if (fwrite(&t, sizeof(TRANSAKCIJA), 1, f) != 1) {
        printf("ERROR: Greska pri upisu transakcije!\n");
        fclose(f);
        pauziraj();
        return;
    }

    fclose(f);
    printf("INFO: Transakcija je uspesno dodata.\n");
    pauziraj();
}

void prikaziSveTransakcije() {
    TRANSAKCIJA t;
    FILE* f = fopen(TRAN_DAT, "rb");
    int count = 0;

    if (!f) {
        printf("ERROR: Transakciona datoteka ne postoji.\n");
        pauziraj();
        return;
    }

    printf("\n%-10s %-10s %-10s\n", "ID", "Promena", "Kolicina");
    printf("--------------------------------------\n");

    while (fread(&t, sizeof(TRANSAKCIJA), 1, f) == 1) {
        printf("%-10u %-10s %-10u\n", t.Id, t.Promena == ULAZ ? "ULAZ" : "IZLAZ", t.Kolicina);
        count++;
        if (count % PAGE_SIZE == 0) {
            printf("\n--- Pritisnite ENTER za nastavak ---");
            getchar();
        }
    }

    fclose(f);

    if (count == 0) {
        printf("INFO: Transakciona datoteka je prazna.\n");
    }
    else {
        printf("\nUkupno transakcija: %d\n", count);
    }

    pauziraj();
}

void prikaziTransakcijeProizvoda() {
    unsigned id;
    TRANSAKCIJA t;
    int found = 0;

    if (!ucitajID(&id)) return;

    FILE* f = fopen(TRAN_DAT, "rb");
    if (!f) {
        printf("ERROR: Transakciona datoteka ne postoji.\n");
        pauziraj();
        return;
    }

    printf("\n%-10s %-10s %-10s\n", "ID", "Promena", "Kolicina");
    printf("--------------------------------------\n");

    while (fread(&t, sizeof(TRANSAKCIJA), 1, f) == 1) {
        if (t.Id == id) {
            printf("%-10u %-10s %-10u\n", t.Id, t.Promena == ULAZ ? "ULAZ" : "IZLAZ", t.Kolicina);
            found++;
        }
    }

    fclose(f);

    if (!found) {
        printf("\nINFO: Ne postoje transakcije za proizvod ID=%u.\n", id);
    }
    else {
        printf("\nPronadjeno transakcija: %d\n", found);
    }
    pauziraj();
}

void azurirajSve() {
    char datum[DATUM_LEN];
    char mat_tek[256], tran_tek[256], prom_rpt[256], nov_pro_rpt[256];
    PROIZVOD mat[MAX_PROIZVODA], nova_mat[MAX_PROIZVODA];
    TRANSAKCIJA tran[MAX_PROIZVODA];
    int nm = 0, nt = 0, nv = 0, i = 0, j = 0;
    FILE* f, * rpt_prom, * rpt_nov_pro;
    int ima_novih = 0;

    vratiDatum(datum);

    if (!kreirajPutanju(mat_tek, ASD_OLD, "mat", datum, "dat")) {
        printf("ERROR: Greska pri kreiranju putanje!\n");
        pauziraj();
        return;
    }
    kreirajPutanju(tran_tek, ASD_OLD, "tran", datum, "dat");
    kreirajPutanju(prom_rpt, ASD_RPT, "prom", datum, "rpt");
    kreirajPutanju(nov_pro_rpt, ASD_RPT, "nov_pro", datum, "rpt");

    if (!fajlPostoji(MAT_DAT)) {
        printf("ERROR: Maticna datoteka ne postoji.\n");
        pauziraj();
        return;
    }

    if (!fajlPostoji(TRAN_DAT)) {
        printf("ERROR: Transakciona datoteka ne postoji.\n");
        pauziraj();
        return;
    }

    if (!sumirajTransakcije(TRAN_DAT, tran_tek)) {
        printf("ERROR: Greska pri sumiranju transakcija!\n");
        pauziraj();
        return;
    }

    f = fopen(MAT_DAT, "rb");
    if (!f) {
        printf("ERROR: Ne mogu da otvorim maticnu datoteku!\n");
        pauziraj();
        return;
    }

    while (fread(&mat[nm], sizeof(PROIZVOD), 1, f) == 1) {
        nm++;
        if (nm >= MAX_PROIZVODA) {
            fclose(f);
            printf("ERROR: Previse proizvoda u maticnoj datoteci!\n");
            pauziraj();
            return;
        }
    }
    fclose(f);

    if (nm == 0) {
        printf("UPOZORENJE: Maticna datoteka je prazna.\n");
        pauziraj();
        return;
    }

    kopirajFajl(MAT_DAT, mat_tek);

    f = fopen(tran_tek, "rb");
    if (!f) {
        printf("ERROR: Sumarna transakciona datoteka ne postoji.\n");
        pauziraj();
        return;
    }

    while (fread(&tran[nt], sizeof(TRANSAKCIJA), 1, f) == 1) {
        nt++;
        if (nt >= MAX_PROIZVODA) {
            fclose(f);
            printf("ERROR: Previse transakcija!\n");
            pauziraj();
            return;
        }
    }
    fclose(f);

    if (nt == 0) {
        printf("UPOZORENJE: Transakciona datoteka je prazna. Nema azuriranja.\n");
        pauziraj();
        return;
    }

    rpt_prom = fopen(prom_rpt, "w");
    if (!rpt_prom) {
        printf("ERROR: Ne mogu da kreiram izvestaj o promenama!\n");
        pauziraj();
        return;
    }

    fprintf(rpt_prom, "%22s %26s %9s\n", "Proizvod", "Promena", "Nova");
    fprintf(rpt_prom, "%-10s %-10s %-15s %-5s %-10s %-10s\n",
        "Id", "Kolicina", "Naziv", "Tip", "Kolicina", "kolicina");
    fprintf(rpt_prom, "--------------------------------------------------------------------\n");

    rpt_nov_pro = fopen(nov_pro_rpt, "w");
    if (!rpt_nov_pro) {
        printf("ERROR: Ne mogu da kreiram izvestaj o novim proizvodima!\n");
        fclose(rpt_prom);
        pauziraj();
        return;
    }

    fprintf(rpt_nov_pro, "%-10s %-15s %-10s\n", "Id", "Proizvod", "Kolicina");
    fprintf(rpt_nov_pro, "------------------------------------\n");

    i = 0;
    j = 0;

    while (i < nm || j < nt) {
        if (i >= nm) {
            if (j < nt) {
                if (tran[j].Promena == ULAZ) {
                    PROIZVOD novi;
                    novi.Id = tran[j].Id;
                    generisiNazivProizvoda(novi.Id, novi.Naziv);
                    novi.Kolicina = tran[j].Kolicina;
                    nova_mat[nv++] = novi;

                    fprintf(rpt_nov_pro, "%-10u %-15s %-10u\n", novi.Id, novi.Naziv, novi.Kolicina);
                    ima_novih = 1;
                }
                j++;
            }
        }
        else if (j >= nt) {
            nova_mat[nv++] = mat[i++];
        }
        else if (mat[i].Id < tran[j].Id) {
            nova_mat[nv++] = mat[i++];
        }
        else if (mat[i].Id > tran[j].Id) {
            if (tran[j].Promena == ULAZ) {
                PROIZVOD novi;
                novi.Id = tran[j].Id;
                generisiNazivProizvoda(novi.Id, novi.Naziv);
                novi.Kolicina = tran[j].Kolicina;
                nova_mat[nv++] = novi;

                fprintf(rpt_nov_pro, "%-10u %-15s %-10u\n", novi.Id, novi.Naziv, novi.Kolicina);
                ima_novih = 1;
            }
            j++;
        }
        else {
            unsigned stara_kol = mat[i].Kolicina;
            nova_mat[nv] = mat[i];

            if (tran[j].Promena == ULAZ) {
                if (nova_mat[nv].Kolicina > UINT_MAX - tran[j].Kolicina) {
                    printf("UPOZORENJE: Overflow pri primanju proizvoda ID=%u!\n",
                        nova_mat[nv].Id);
                    nova_mat[nv].Kolicina = UINT_MAX;
                }
                else {
                    nova_mat[nv].Kolicina += tran[j].Kolicina;
                }
            }
            else {
                nova_mat[nv].Kolicina -= tran[j].Kolicina;
            }

            fprintf(rpt_prom, "%-10u %-10u %-15s %-5s %-10u %-10u\n",
                nova_mat[nv].Id, stara_kol, nova_mat[nv].Naziv,
                tran[j].Promena == ULAZ ? "+" : "-",
                tran[j].Kolicina, nova_mat[nv].Kolicina);

            nv++;
            i++;
            j++;
        }

        if (nv >= MAX_PROIZVODA) {
            printf("ERROR: Previse proizvoda u novoj maticnoj!\n");
            break;
        }
    }

    fclose(rpt_prom);
    fclose(rpt_nov_pro);

    qsort(nova_mat, nv, sizeof(PROIZVOD), sortirajProizvode);

    f = fopen(MAT_DAT, "wb");
    if (!f) {
        printf("ERROR: Ne mogu da snimim novu maticnu datoteku!\n");
        pauziraj();
        return;
    }

    if (nv > 0) {
        if (fwrite(nova_mat, sizeof(PROIZVOD), nv, f) != nv) {
            printf("ERROR: Greska pri upisu nove maticne!\n");
            fclose(f);
            pauziraj();
            return;
        }
    }
    fclose(f);

    ocistiEkran();
    printf("\n=== IZVESTAj O PROMENAMA ===\n\n");
    FILE* rpt = fopen(prom_rpt, "r");
    if (rpt) {
        char line[MAX_LINE];
        int line_count = 0;
        while (fgets(line, MAX_LINE, rpt)) {
            printf("%s", line);
            line_count++;
            if (line_count % PAGE_SIZE == 0) {
                printf("\n--- Pritisnite ENTER za nastavak ---");
                getchar();
            }
        }
        fclose(rpt);
    }

    if (ima_novih) {
        printf("\n\n=== IZVESTAj O NOVIM PROIZVODIMA ===\n\n");
        rpt = fopen(nov_pro_rpt, "r");
        if (rpt) {
            char line[MAX_LINE];
            int line_count = 0;
            while (fgets(line, MAX_LINE, rpt)) {
                printf("%s", line);
                line_count++;
                if (line_count % PAGE_SIZE == 0) {
                    printf("\n--- Pritisnite ENTER za nastavak ---");
                    getchar();
                }
            }
            fclose(rpt);
        }
    }

    printf("\n\nINFO: Azuriranje je uspesno zavrseno.\n");
    printf("Stara maticna datoteka: %s\n", mat_tek);
    printf("Transakciona datoteka : %s\n", tran_tek);
    printf("Izvestaj o promenama  : %s\n", prom_rpt);
    if (ima_novih) {
        printf("Izvestaj o novim proizvodima: %s\n", nov_pro_rpt);
    }
    pauziraj();
}