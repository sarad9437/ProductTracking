#define _CRT_SECURE_NO_WARNINGS
#include "misc.h"
#include "util.h"
#include "adts.h"

void prikaziOAzuriranju() {
    ocistiEkran();
    printf("========================================================================\n");
    printf("O AZURIRANJU SERIJSKE DATOTEKE\n");
    printf("========================================================================\n\n");

    printf("Problem azuriranja serijske datoteke:\n\n");

    printf("Date su dve datoteke:\n");
    printf("(1) Maticna datoteka - sadrzi podatke o proizvodima (Id, Naziv, Kolicina)\n");
    printf("    - Sortirana po Id-u u rastucem redosledu\n");
    printf("(2) Transakciona datoteka - sadrzi promene nad proizvodima\n");
    printf("    - ULAZ = primanje novih proizvoda (povecanje kolicine)\n");
    printf("    - IZLAZ = izdavanje postojecih proizvoda (smanjenje kolicine)\n");
    printf("    - Hronoloska (redna), nije sortirana\n\n");

    printf("Proces azuriranja:\n");
    printf("1. Transakcije se sumiraju po Id-u proizvoda\n");
    printf("2. Sumarna transakciona datoteka se sortira po Id-u\n");
    printf("3. Maticna datoteka se azurira pomocu sumarnih transakcija\n");
    printf("4. Generisu se izvestaji o izvrsenim promenama i greskama\n\n");

    printf("Moguci dogadjaji:\n");
    printf("D.1. Azuriranje proizvoda koji postoji u maticnoj datoteci\n");
    printf("D.2. Azuriranje proizvoda koji ne postoji u maticnoj datoteci\n");
    printf("D.3. Povecanje kolicine proizvoda\n");
    printf("D.4. Smanjenje kolicine proizvoda\n\n");

    printf("Moguci ishodi:\n");
    printf("I.1. Uspesan pokusaj azuriranja\n");
    printf("I.2. Neuspesan pokusaj azuriranja (greska)\n\n");

    pauziraj();
}

void prikaziONama() {
    ocistiEkran();
    printf("========================================================================\n");
    printf("O NAMA\n");
    printf("========================================================================\n\n");
    printf("Softverski inzenjer: Sara Da Rold, sd20220413@student.fon.bg.ac.rs\n");
    printf("Domenski inzenjer  : Sasa D. Lazarevic, slazar@fon.rs\n\n");
    printf("Projekat: ASD - Azuriranje Serijske Datoteke\n");
    printf("Verzija : 1.0\n");
    printf("Slucaj  : 5 - Sveobuhvatni slucaj\n");
    printf("Datum   : 03.02.2026.\n\n");
    pauziraj();
}

void prikaziDemo1() {
    ocistiEkran();
    printf("========================================================================\n");
    printf("DEMO - OSNOVNI SLUCAJ\n");
    printf("========================================================================\n\n");

    printf("Osnovni slucaj je najjednostavniji.\n\n");

    printf("Scenariji:\n");
    printf("  D.1. + D.3. = I.1.\n");
    printf("    - Primljena kolicina proizvoda se dodaje na trenutno raspolozivu\n");
    printf("    - Poruka o uspesnom azuriranju se upisuje u izvestaj\n\n");

    printf("  D.1. + D.4. = I.1.\n");
    printf("    - Izdata kolicina je manja od trenutno raspolozive\n");
    printf("    - Poruka o uspesnom azuriranju se upisuje u izvestaj\n\n");

    printf("U osnovnom slucaju nema gresaka.\n");
    printf("Sve transakcije su validne.\n\n");

    pauziraj();

    ocistiEkran();
    printf("========================================================================\n");
    printf("DEMO PODACI - OSNOVNI SLUCAJ\n");
    printf("========================================================================\n\n");

    char demo_mat[] = ".\\ASD\\DEMO\\maticna.dat";
    char demo_tran[] = ".\\ASD\\DEMO\\SLUC_1\\transakciona.dat";

    PROIZVOD stara_mat[MAX_PROIZVODA];
    int nm = 0;

    FILE* f = fopen(demo_mat, "rb");
    if (f) {
        while (fread(&stara_mat[nm], sizeof(PROIZVOD), 1, f) == 1) {
            nm++;
            if (nm >= MAX_PROIZVODA) break;
        }
        fclose(f);
    }

    TRANSAKCIJA trans[MAX_PROIZVODA];
    int nt = 0;

    f = fopen(demo_tran, "rb");
    if (f) {
        while (fread(&trans[nt], sizeof(TRANSAKCIJA), 1, f) == 1) {
            nt++;
            if (nt >= MAX_PROIZVODA) break;
        }
        fclose(f);
    }

    printf("%-35s | %-35s\n", "STARA MATICNA DATOTEKA", "TRANSAKCIONA DATOTEKA");
    printf("%-10s %-15s %-8s | %-10s %-10s %-10s\n",
        "ID", "Naziv", "Kolicina", "ID", "Promena", "Kolicina");
    printf("------------------------------------+------------------------------------\n");

    int max_rows = (nm > nt) ? nm : nt;
    for (int i = 0; i < max_rows; i++) {
        if (i < nm) {
            printf("%-10u %-15s %-8u | ",
                stara_mat[i].Id, stara_mat[i].Naziv, stara_mat[i].Kolicina);
        }
        else {
            printf("%-35s | ", "");
        }

        if (i < nt) {
            printf("%-10u %-10s %-10u\n",
                trans[i].Id,
                trans[i].Promena == ULAZ ? "ULAZ" : "IZLAZ",
                trans[i].Kolicina);
        }
        else {
            printf("\n");
        }
    }

    printf("\n");
    pauziraj();

    ocistiEkran();
    printf("========================================================================\n");
    printf("SUMARNA TRANSAKCIONA I NOVA MATICNA\n");
    printf("========================================================================\n\n");

    TRANSAKCIJA sum[MAX_PROIZVODA];
    int ns = 0;

    for (int i = 0; i < nt; i++) {
        int found = -1;
        for (int j = 0; j < ns; j++) {
            if (sum[j].Id == trans[i].Id) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            sum[ns++] = trans[i];
        }
        else {
            long long stara_kol = (sum[found].Promena == ULAZ) ?
                (long long)sum[found].Kolicina : -(long long)sum[found].Kolicina;
            long long nova_trans = (trans[i].Promena == ULAZ) ?
                (long long)trans[i].Kolicina : -(long long)trans[i].Kolicina;
            long long suma = stara_kol + nova_trans;

            if (suma >= 0) {
                sum[found].Kolicina = (unsigned)suma;
                sum[found].Promena = ULAZ;
            }
            else {
                sum[found].Kolicina = (unsigned)(-suma);
                sum[found].Promena = IZLAZ;
            }
        }
    }

    qsort(sum, ns, sizeof(TRANSAKCIJA), sortirajTransakcije);

    PROIZVOD nova_mat[MAX_PROIZVODA];
    int nv = 0;
    int i = 0, j = 0;

    while (i < nm || j < ns) {
        if (i >= nm) {
            j++;
        }
        else if (j >= ns) {
            nova_mat[nv++] = stara_mat[i++];
        }
        else if (stara_mat[i].Id < sum[j].Id) {
            nova_mat[nv++] = stara_mat[i++];
        }
        else if (stara_mat[i].Id > sum[j].Id) {
            j++;
        }
        else {
            nova_mat[nv] = stara_mat[i];

            if (sum[j].Promena == ULAZ) {
                nova_mat[nv].Kolicina += sum[j].Kolicina;
            }
            else {
                nova_mat[nv].Kolicina -= sum[j].Kolicina;
            }

            nv++;
            i++;
            j++;
        }
    }

    printf("%-35s | %-35s\n", "SUMARNA TRANSAKCIONA", "NOVA MATICNA");
    printf("%-10s %-10s %-13s | %-10s %-15s %-8s\n",
        "ID", "Promena", "Kolicina", "ID", "Naziv", "Kolicina");
    printf("------------------------------------+------------------------------------\n");

    max_rows = (ns > nv) ? ns : nv;
    for (int i = 0; i < max_rows; i++) {
        if (i < ns) {
            printf("%-10u %-10s %-13u | ",
                sum[i].Id,
                sum[i].Promena == ULAZ ? "ULAZ" : "IZLAZ",
                sum[i].Kolicina);
        }
        else {
            printf("%-35s | ", "");
        }

        if (i < nv) {
            printf("%-10u %-15s %-8u\n",
                nova_mat[i].Id, nova_mat[i].Naziv, nova_mat[i].Kolicina);
        }
        else {
            printf("\n");
        }
    }

    printf("\n");
    pauziraj();
}

void prikaziDemo2() {
    ocistiEkran();
    printf("========================================================================\n");
    printf("DEMO - NEPOSTOJECA KOLICINA\n");
    printf("========================================================================\n\n");

    printf("Ovaj slucaj prosiruje osnovni slucaj.\n\n");

    printf("Scenariji:\n");
    printf("  D.1. + D.3. = I.1.\n");
    printf("    - Primljena kolicina proizvoda se dodaje na trenutno raspolozivu\n\n");

    printf("  D.1. + D.4. = I.1.\n");
    printf("    - Izdata kolicina je manja od trenutno raspolozive\n\n");

    printf("  D.1. + D.4. = I.2. - GRESKA!\n");
    printf("    - Izdata kolicina nije manja od trenutno raspolozive\n");
    printf("    - Operacija se odbija\n");
    printf("    - Poruka o greski se upisuje u err_kol_YYMMDD.rpt\n\n");

    printf("Generisu se izvestaji:\n");
    printf("- prom_YYMMDD.rpt     - Uspesne promene\n");
    printf("- err_kol_YYMMDD.rpt  - Greske: Nepostojeca kolicina\n\n");

    pauziraj();

    ocistiEkran();
    printf("========================================================================\n");
    printf("DEMO PODACI - NEPOSTOJECA KOLICINA\n");
    printf("========================================================================\n\n");

    char demo_mat[] = ".\\ASD\\DEMO\\maticna.dat";
    char demo_tran[] = ".\\ASD\\DEMO\\SLUC_2\\transakciona.dat";

    PROIZVOD stara_mat[MAX_PROIZVODA];
    int nm = 0;

    FILE* f = fopen(demo_mat, "rb");
    if (f) {
        while (fread(&stara_mat[nm], sizeof(PROIZVOD), 1, f) == 1) {
            nm++;
            if (nm >= MAX_PROIZVODA) break;
        }
        fclose(f);
    }

    TRANSAKCIJA trans[MAX_PROIZVODA];
    int nt = 0;

    f = fopen(demo_tran, "rb");
    if (f) {
        while (fread(&trans[nt], sizeof(TRANSAKCIJA), 1, f) == 1) {
            nt++;
            if (nt >= MAX_PROIZVODA) break;
        }
        fclose(f);
    }

    printf("%-35s | %-35s\n", "STARA MATICNA DATOTEKA", "TRANSAKCIONA DATOTEKA");
    printf("%-10s %-15s %-8s | %-10s %-10s %-10s\n",
        "ID", "Naziv", "Kolicina", "ID", "Promena", "Kolicina");
    printf("------------------------------------+------------------------------------\n");

    int max_rows = (nm > nt) ? nm : nt;
    for (int i = 0; i < max_rows; i++) {
        if (i < nm) {
            printf("%-10u %-15s %-8u | ",
                stara_mat[i].Id, stara_mat[i].Naziv, stara_mat[i].Kolicina);
        }
        else {
            printf("%-35s | ", "");
        }

        if (i < nt) {
            printf("%-10u %-10s %-10u\n",
                trans[i].Id,
                trans[i].Promena == ULAZ ? "ULAZ" : "IZLAZ",
                trans[i].Kolicina);
        }
        else {
            printf("\n");
        }
    }

    printf("\n");
    pauziraj();

    ocistiEkran();
    printf("========================================================================\n");
    printf("SUMARNA TRANSAKCIONA, NOVA MATICNA I IZVESTAJI\n");
    printf("========================================================================\n\n");

    TRANSAKCIJA sum[MAX_PROIZVODA];
    int ns = 0;

    for (int i = 0; i < nt; i++) {
        int found = -1;
        for (int j = 0; j < ns; j++) {
            if (sum[j].Id == trans[i].Id) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            sum[ns++] = trans[i];
        }
        else {
            long long stara_kol = (sum[found].Promena == ULAZ) ?
                (long long)sum[found].Kolicina : -(long long)sum[found].Kolicina;
            long long nova_trans = (trans[i].Promena == ULAZ) ?
                (long long)trans[i].Kolicina : -(long long)trans[i].Kolicina;
            long long suma = stara_kol + nova_trans;

            if (suma >= 0) {
                sum[found].Kolicina = (unsigned)suma;
                sum[found].Promena = ULAZ;
            }
            else {
                sum[found].Kolicina = (unsigned)(-suma);
                sum[found].Promena = IZLAZ;
            }
        }
    }

    qsort(sum, ns, sizeof(TRANSAKCIJA), sortirajTransakcije);

    PROIZVOD nova_mat[MAX_PROIZVODA];
    TRANSAKCIJA greske[MAX_PROIZVODA];
    int nv = 0, ng = 0;
    int i = 0, j = 0;

    while (i < nm || j < ns) {
        if (i >= nm) {
            j++;
        }
        else if (j >= ns) {
            nova_mat[nv++] = stara_mat[i++];
        }
        else if (stara_mat[i].Id < sum[j].Id) {
            nova_mat[nv++] = stara_mat[i++];
        }
        else if (stara_mat[i].Id > sum[j].Id) {
            j++;
        }
        else {
            nova_mat[nv] = stara_mat[i];

            if (sum[j].Promena == IZLAZ && sum[j].Kolicina > stara_mat[i].Kolicina) {
                greske[ng++] = sum[j];
                nova_mat[nv++] = stara_mat[i++];
            }
            else {
                if (sum[j].Promena == ULAZ) {
                    nova_mat[nv].Kolicina += sum[j].Kolicina;
                }
                else {
                    nova_mat[nv].Kolicina -= sum[j].Kolicina;
                }
                nv++;
                i++;
            }
            j++;
        }
    }

    printf("%-35s | %-35s\n", "SUMARNA TRANSAKCIONA", "NOVA MATICNA");
    printf("%-10s %-10s %-13s | %-10s %-15s %-8s\n",
        "ID", "Promena", "Kolicina", "ID", "Naziv", "Kolicina");
    printf("------------------------------------+------------------------------------\n");

    max_rows = (ns > nv) ? ns : nv;
    for (int i = 0; i < max_rows; i++) {
        if (i < ns) {
            printf("%-10u %-10s %-13u | ",
                sum[i].Id,
                sum[i].Promena == ULAZ ? "ULAZ" : "IZLAZ",
                sum[i].Kolicina);
        }
        else {
            printf("%-35s | ", "");
        }

        if (i < nv) {
            printf("%-10u %-15s %-8u\n",
                nova_mat[i].Id, nova_mat[i].Naziv, nova_mat[i].Kolicina);
        }
        else {
            printf("\n");
        }
    }

    printf("\n");

    if (ng > 0) {
        printf("========================================================================\n");
        printf("GRESKE - NEPOSTOJECA KOLICINA\n");
        printf("========================================================================\n");
        printf("%-10s %-10s %-10s\n", "ID", "Promena", "Kolicina");
        printf("------------------------------------\n");
        for (int i = 0; i < ng; i++) {
            printf("%-10u %-10s %-10u\n",
                greske[i].Id, "IZLAZ", greske[i].Kolicina);
        }
        printf("\n");
    }

    pauziraj();
}

void prikaziDemo3() {
    ocistiEkran();
    printf("========================================================================\n");
    printf("DEMO - NOV PROIZVOD\n");
    printf("========================================================================\n\n");

    printf("Ovaj slucaj prosiruje osnovni slucaj.\n\n");

    printf("Scenariji:\n");
    printf("  D.1. + D.3. = I.1.\n");
    printf("    - Primljena kolicina postojeceg proizvoda se dodaje\n\n");

    printf("  D.1. + D.4. = I.1.\n");
    printf("    - Izdata kolicina postojeceg proizvoda se oduzima\n\n");

    printf("  D.2. + D.3. = I.1. - NOV PROIZVOD!\n");
    printf("    - Primljena je kolicina proizvoda koji ne postoji u maticnoj\n");
    printf("    - Dodaje se NOV proizvod u maticnu datoteku\n");
    printf("    - Poruka o novom proizvodu se upisuje u nov_pro_YYMMDD.rpt\n\n");

    printf("U ovom slucaju nema provere nepostojece kolicine.\n\n");

    pauziraj();

    ocistiEkran();
    printf("========================================================================\n");
    printf("DEMO PODACI - NOV PROIZVOD\n");
    printf("========================================================================\n\n");

    char demo_mat[] = ".\\ASD\\DEMO\\maticna.dat";
    char demo_tran[] = ".\\ASD\\DEMO\\SLUC_3\\transakciona.dat";

    PROIZVOD stara_mat[MAX_PROIZVODA];
    int nm = 0;

    FILE* f = fopen(demo_mat, "rb");
    if (f) {
        while (fread(&stara_mat[nm], sizeof(PROIZVOD), 1, f) == 1) {
            nm++;
            if (nm >= MAX_PROIZVODA) break;
        }
        fclose(f);
    }

    TRANSAKCIJA trans[MAX_PROIZVODA];
    int nt = 0;

    f = fopen(demo_tran, "rb");
    if (f) {
        while (fread(&trans[nt], sizeof(TRANSAKCIJA), 1, f) == 1) {
            nt++;
            if (nt >= MAX_PROIZVODA) break;
        }
        fclose(f);
    }

    printf("%-35s | %-35s\n", "STARA MATICNA DATOTEKA", "TRANSAKCIONA DATOTEKA");
    printf("%-10s %-15s %-8s | %-10s %-10s %-10s\n",
        "ID", "Naziv", "Kolicina", "ID", "Promena", "Kolicina");
    printf("------------------------------------+------------------------------------\n");

    int max_rows = (nm > nt) ? nm : nt;
    for (int i = 0; i < max_rows; i++) {
        if (i < nm) {
            printf("%-10u %-15s %-8u | ",
                stara_mat[i].Id, stara_mat[i].Naziv, stara_mat[i].Kolicina);
        }
        else {
            printf("%-35s | ", "");
        }

        if (i < nt) {
            printf("%-10u %-10s %-13u\n",
                trans[i].Id,
                trans[i].Promena == ULAZ ? "ULAZ" : "IZLAZ",
                trans[i].Kolicina);
        }
        else {
            printf("\n");
        }
    }

    printf("\n");
    pauziraj();

    ocistiEkran();
    printf("========================================================================\n");
    printf("SUMARNA TRANSAKCIONA, NOVA MATICNA I IZVESTAJI\n");
    printf("========================================================================\n\n");

    TRANSAKCIJA sum[MAX_PROIZVODA];
    int ns = 0;

    for (int i = 0; i < nt; i++) {
        int found = -1;
        for (int j = 0; j < ns; j++) {
            if (sum[j].Id == trans[i].Id) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            sum[ns++] = trans[i];
        }
        else {
            long long stara_kol = (sum[found].Promena == ULAZ) ?
                (long long)sum[found].Kolicina : -(long long)sum[found].Kolicina;
            long long nova_trans = (trans[i].Promena == ULAZ) ?
                (long long)trans[i].Kolicina : -(long long)trans[i].Kolicina;
            long long suma = stara_kol + nova_trans;

            if (suma >= 0) {
                sum[found].Kolicina = (unsigned)suma;
                sum[found].Promena = ULAZ;
            }
            else {
                sum[found].Kolicina = (unsigned)(-suma);
                sum[found].Promena = IZLAZ;
            }
        }
    }

    qsort(sum, ns, sizeof(TRANSAKCIJA), sortirajTransakcije);

    PROIZVOD nova_mat[MAX_PROIZVODA];
    PROIZVOD novi_proizvodi[MAX_PROIZVODA];
    int nv = 0, np = 0;
    int i = 0, j = 0;

    while (i < nm || j < ns) {
        if (i >= nm) {
            if (sum[j].Promena == ULAZ) {
                PROIZVOD nov;
                nov.Id = sum[j].Id;
                generisiNazivProizvoda(nov.Id, nov.Naziv);
                nov.Kolicina = sum[j].Kolicina;
                nova_mat[nv++] = nov;
                novi_proizvodi[np++] = nov;
            }
            j++;
        }
        else if (j >= ns) {
            nova_mat[nv++] = stara_mat[i++];
        }
        else if (stara_mat[i].Id < sum[j].Id) {
            nova_mat[nv++] = stara_mat[i++];
        }
        else if (stara_mat[i].Id > sum[j].Id) {
            if (sum[j].Promena == ULAZ) {
                PROIZVOD nov;
                nov.Id = sum[j].Id;
                generisiNazivProizvoda(nov.Id, nov.Naziv);
                nov.Kolicina = sum[j].Kolicina;
                nova_mat[nv++] = nov;
                novi_proizvodi[np++] = nov;
            }
            j++;
        }
        else {
            nova_mat[nv] = stara_mat[i];

            if (sum[j].Promena == ULAZ) {
                nova_mat[nv].Kolicina += sum[j].Kolicina;
            }
            else {
                nova_mat[nv].Kolicina -= sum[j].Kolicina;
            }
            nv++;
            i++;
            j++;
        }
    }

    printf("%-35s | %-35s\n", "SUMARNA TRANSAKCIONA", "NOVA MATICNA");
    printf("%-10s %-10s %-13s | %-10s %-15s %-8s\n",
        "ID", "Promena", "Kolicina", "ID", "Naziv", "Kolicina");
    printf("------------------------------------+------------------------------------\n");

    max_rows = (ns > nv) ? ns : nv;
    for (int i = 0; i < max_rows; i++) {
        if (i < ns) {
            printf("%-10u %-10s %-13u | ",
                sum[i].Id,
                sum[i].Promena == ULAZ ? "ULAZ" : "IZLAZ",
                sum[i].Kolicina);
        }
        else {
            printf("%-35s | ", "");
        }

        if (i < nv) {
            printf("%-10u %-15s %-8u\n",
                nova_mat[i].Id, nova_mat[i].Naziv, nova_mat[i].Kolicina);
        }
        else {
            printf("\n");
        }
    }

    printf("\n");

    if (np > 0) {
        printf("========================================================================\n");
        printf("NOVI PROIZVODI\n");
        printf("========================================================================\n");
        printf("%-10s %-15s %-10s\n", "ID", "Naziv", "Kolicina");
        printf("--------------------------------------\n");
        for (int i = 0; i < np; i++) {
            printf("%-10u %-15s %-10u\n",
                novi_proizvodi[i].Id, novi_proizvodi[i].Naziv, novi_proizvodi[i].Kolicina);
        }
        printf("\n");
    }

    pauziraj();
}

void prikaziDemo4() {
    ocistiEkran();
    printf("========================================================================\n");
    printf("DEMO - NEPOSTOJECI PROIZVOD\n");
    printf("========================================================================\n\n");

    printf("Ovaj slucaj prosiruje osnovni slucaj.\n\n");

    printf("Scenariji:\n");
    printf("  D.1. + D.3. = I.1.\n");
    printf("    - Primljena kolicina postojeceg proizvoda se dodaje\n\n");

    printf("  D.1. + D.4. = I.1.\n");
    printf("    - Izdata kolicina postojeceg proizvoda se oduzima\n\n");

    printf("  D.2. + D.4. = I.2. - GRESKA: NEPOSTOJECI PROIZVOD!\n");
    printf("    - Pokusaj izdavanja kolicine proizvoda koji ne postoji\n");
    printf("    - Operacija se odbija\n");
    printf("    - Poruka o greski se upisuje u err_pro_YYMMDD.rpt\n\n");

    printf("U ovom slucaju:\n");
    printf("- Nema provere nepostojece kolicine\n");
    printf("- Nema dodavanja novih proizvoda\n\n");

    pauziraj();

    ocistiEkran();
    printf("========================================================================\n");
    printf("DEMO PODACI - NEPOSTOJECI PROIZVOD\n");
    printf("========================================================================\n\n");

    char demo_mat[] = ".\\ASD\\DEMO\\maticna.dat";
    char demo_tran[] = ".\\ASD\\DEMO\\SLUC_4\\transakciona.dat";

    PROIZVOD stara_mat[MAX_PROIZVODA];
    int nm = 0;

    FILE* f = fopen(demo_mat, "rb");
    if (f) {
        while (fread(&stara_mat[nm], sizeof(PROIZVOD), 1, f) == 1) {
            nm++;
            if (nm >= MAX_PROIZVODA) break;
        }
        fclose(f);
    }

    TRANSAKCIJA trans[MAX_PROIZVODA];
    int nt = 0;

    f = fopen(demo_tran, "rb");
    if (f) {
        while (fread(&trans[nt], sizeof(TRANSAKCIJA), 1, f) == 1) {
            nt++;
            if (nt >= MAX_PROIZVODA) break;
        }
        fclose(f);
    }

    printf("%-35s | %-35s\n", "STARA MATICNA DATOTEKA", "TRANSAKCIONA DATOTEKA");
    printf("%-10s %-15s %-8s | %-10s %-10s %-10s\n",
        "ID", "Naziv", "Kolicina", "ID", "Promena", "Kolicina");
    printf("------------------------------------+------------------------------------\n");

    int max_rows = (nm > nt) ? nm : nt;
    for (int i = 0; i < max_rows; i++) {
        if (i < nm) {
            printf("%-10u %-15s %-8u | ",
                stara_mat[i].Id, stara_mat[i].Naziv, stara_mat[i].Kolicina);
        }
        else {
            printf("%-35s | ", "");
        }

        if (i < nt) {
            printf("%-10u %-10s %-10u\n",
                trans[i].Id,
                trans[i].Promena == ULAZ ? "ULAZ" : "IZLAZ",
                trans[i].Kolicina);
        }
        else {
            printf("\n");
        }
    }

    printf("\n");
    pauziraj();

    ocistiEkran();
    printf("========================================================================\n");
    printf("SUMARNA TRANSAKCIONA, NOVA MATICNA I IZVESTAJI\n");
    printf("========================================================================\n\n");

    TRANSAKCIJA sum[MAX_PROIZVODA];
    int ns = 0;

    for (int i = 0; i < nt; i++) {
        int found = -1;
        for (int j = 0; j < ns; j++) {
            if (sum[j].Id == trans[i].Id) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            sum[ns++] = trans[i];
        }
        else {
            long long stara_kol = (sum[found].Promena == ULAZ) ?
                (long long)sum[found].Kolicina : -(long long)sum[found].Kolicina;
            long long nova_trans = (trans[i].Promena == ULAZ) ?
                (long long)trans[i].Kolicina : -(long long)trans[i].Kolicina;
            long long suma = stara_kol + nova_trans;

            if (suma >= 0) {
                sum[found].Kolicina = (unsigned)suma;
                sum[found].Promena = ULAZ;
            }
            else {
                sum[found].Kolicina = (unsigned)(-suma);
                sum[found].Promena = IZLAZ;
            }
        }
    }

    qsort(sum, ns, sizeof(TRANSAKCIJA), sortirajTransakcije);

    PROIZVOD nova_mat[MAX_PROIZVODA];
    TRANSAKCIJA greske[MAX_PROIZVODA];
    int nv = 0, ng = 0;
    int i = 0, j = 0;

    while (i < nm || j < ns) {
        if (i >= nm) {
            if (sum[j].Promena == IZLAZ) {
                greske[ng++] = sum[j];
            }
            j++;
        }
        else if (j >= ns) {
            nova_mat[nv++] = stara_mat[i++];
        }
        else if (stara_mat[i].Id < sum[j].Id) {
            nova_mat[nv++] = stara_mat[i++];
        }
        else if (stara_mat[i].Id > sum[j].Id) {
            if (sum[j].Promena == IZLAZ) {
                greske[ng++] = sum[j];
            }
            j++;
        }
        else {
            nova_mat[nv] = stara_mat[i];

            if (sum[j].Promena == ULAZ) {
                nova_mat[nv].Kolicina += sum[j].Kolicina;
            }
            else {
                nova_mat[nv].Kolicina -= sum[j].Kolicina;
            }
            nv++;
            i++;
            j++;
        }
    }

    printf("%-35s | %-35s\n", "SUMARNA TRANSAKCIONA", "NOVA MATICNA");
    printf("%-10s %-10s %-13s | %-10s %-15s %-8s\n",
        "ID", "Promena", "Kolicina", "ID", "Naziv", "Kolicina");
    printf("------------------------------------+------------------------------------\n");

    max_rows = (ns > nv) ? ns : nv;
    for (int i = 0; i < max_rows; i++) {
        if (i < ns) {
            printf("%-10u %-10s %-13u | ",
                sum[i].Id,
                sum[i].Promena == ULAZ ? "ULAZ" : "IZLAZ",
                sum[i].Kolicina);
        }
        else {
            printf("%-35s | ", "");
        }

        if (i < nv) {
            printf("%-10u %-15s %-8u\n",
                nova_mat[i].Id, nova_mat[i].Naziv, nova_mat[i].Kolicina);
        }
        else {
            printf("\n");
        }
    }

    printf("\n");

    if (ng > 0) {
        printf("========================================================================\n");
        printf("GRESKE - NEPOSTOJECI PROIZVOD\n");
        printf("========================================================================\n");
        printf("%-10s %-10s %-10s\n", "ID", "Promena", "Kolicina");
        printf("------------------------------------\n");
        for (int i = 0; i < ng; i++) {
            printf("%-10u %-10s %-10u\n",
                greske[i].Id, "IZLAZ", greske[i].Kolicina);
        }
        printf("\n");
    }

    pauziraj();
}

void prikaziDemo5() {
    ocistiEkran();
    printf("========================================================================\n");
    printf("DEMO - SVEOBUHVATNI SLUCAJ\n");
    printf("========================================================================\n\n");

    printf("Kombinuje sve prethodne slucajeve.\n\n");

    printf("Scenariji:\n");
    printf("  D.1. + D.3. = I.1. - Primanje postojeceg proizvoda (uspesno)\n");
    printf("  D.1. + D.4. = I.1. - Izdavanje postojeceg proizvoda (uspesno)\n");
    printf("  D.1. + D.4. = I.2. - Izdavanje postojeceg (GRESKA: nedovoljna kolicina)\n");
    printf("  D.2. + D.3. = I.1. - Primanje nepostojeceg (NOV PROIZVOD)\n");
    printf("  D.2. + D.4. = I.2. - Izdavanje nepostojeceg (GRESKA)\n\n");

    printf("Svi izvestaji:\n");
    printf("1. prom_YYMMDD.rpt     - Uspesne promene\n");
    printf("2. nov_pro_YYMMDD.rpt  - Novi proizvodi\n");
    printf("3. err_kol_YYMMDD.rpt  - Greske: Nepostojeca kolicina\n");
    printf("4. err_pro_YYMMDD.rpt  - Greske: Nepostojeci proizvod\n\n");

    pauziraj();

    ocistiEkran();
    printf("========================================================================\n");
    printf("DEMO PODACI - SVEOBUHVATNI SLUCAJ\n");
    printf("========================================================================\n\n");

    char demo_mat[] = ".\\ASD\\DEMO\\maticna.dat";
    char demo_tran[] = ".\\ASD\\DEMO\\SLUC_5\\transakciona.dat";

    PROIZVOD stara_mat[MAX_PROIZVODA];
    int nm = 0;

    FILE* f = fopen(demo_mat, "rb");
    if (f) {
        while (fread(&stara_mat[nm], sizeof(PROIZVOD), 1, f) == 1) {
            nm++;
            if (nm >= MAX_PROIZVODA) break;
        }
        fclose(f);
    }

    TRANSAKCIJA trans[MAX_PROIZVODA];
    int nt = 0;

    f = fopen(demo_tran, "rb");
    if (f) {
        while (fread(&trans[nt], sizeof(TRANSAKCIJA), 1, f) == 1) {
            nt++;
            if (nt >= MAX_PROIZVODA) break;
        }
        fclose(f);
    }

    printf("%-35s | %-35s\n", "STARA MATICNA DATOTEKA", "TRANSAKCIONA DATOTEKA");
    printf("%-10s %-15s %-8s | %-10s %-10s %-10s\n",
        "ID", "Naziv", "Kolicina", "ID", "Promena", "Kolicina");
    printf("------------------------------------+------------------------------------\n");

    int max_rows = (nm > nt) ? nm : nt;
    for (int i = 0; i < max_rows; i++) {
        if (i < nm) {
            printf("%-10u %-15s %-8u | ",
                stara_mat[i].Id, stara_mat[i].Naziv, stara_mat[i].Kolicina);
        }
        else {
            printf("%-35s | ", "");
        }

        if (i < nt) {
            printf("%-10u %-10s %-10u\n",
                trans[i].Id,
                trans[i].Promena == ULAZ ? "ULAZ" : "IZLAZ",
                trans[i].Kolicina);
        }
        else {
            printf("\n");
        }
    }

    printf("\n");
    pauziraj();

    ocistiEkran();
    printf("========================================================================\n");
    printf("SUMARNA TRANSAKCIONA I NOVA MATICNA\n");
    printf("========================================================================\n\n");

    TRANSAKCIJA sum[MAX_PROIZVODA];
    int ns = 0;

    for (int i = 0; i < nt; i++) {
        int found = -1;
        for (int j = 0; j < ns; j++) {
            if (sum[j].Id == trans[i].Id) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            sum[ns++] = trans[i];
        }
        else {
            long long stara_kol = (sum[found].Promena == ULAZ) ?
                (long long)sum[found].Kolicina : -(long long)sum[found].Kolicina;
            long long nova_trans = (trans[i].Promena == ULAZ) ?
                (long long)trans[i].Kolicina : -(long long)trans[i].Kolicina;
            long long suma = stara_kol + nova_trans;

            if (suma >= 0) {
                sum[found].Kolicina = (unsigned)suma;
                sum[found].Promena = ULAZ;
            }
            else {
                sum[found].Kolicina = (unsigned)(-suma);
                sum[found].Promena = IZLAZ;
            }
        }
    }

    qsort(sum, ns, sizeof(TRANSAKCIJA), sortirajTransakcije);

    PROIZVOD nova_mat[MAX_PROIZVODA];
    PROIZVOD novi_proizvodi[MAX_PROIZVODA];
    TRANSAKCIJA greske_kol[MAX_PROIZVODA], greske_pro[MAX_PROIZVODA];
    int nv = 0, np = 0, ngk = 0, ngp = 0;
    int i = 0, j = 0;

    while (i < nm || j < ns) {
        if (i >= nm) {
            if (sum[j].Promena == ULAZ) {
                PROIZVOD nov;
                nov.Id = sum[j].Id;
                generisiNazivProizvoda(nov.Id, nov.Naziv);
                nov.Kolicina = sum[j].Kolicina;
                nova_mat[nv++] = nov;
                novi_proizvodi[np++] = nov;
            }
            else {
                greske_pro[ngp++] = sum[j];
            }
            j++;
        }
        else if (j >= ns) {
            nova_mat[nv++] = stara_mat[i++];
        }
        else if (stara_mat[i].Id < sum[j].Id) {
            nova_mat[nv++] = stara_mat[i++];
        }
        else if (stara_mat[i].Id > sum[j].Id) {
            if (sum[j].Promena == ULAZ) {
                PROIZVOD nov;
                nov.Id = sum[j].Id;
                generisiNazivProizvoda(nov.Id, nov.Naziv);
                nov.Kolicina = sum[j].Kolicina;
                nova_mat[nv++] = nov;
                novi_proizvodi[np++] = nov;
            }
            else {
                greske_pro[ngp++] = sum[j];
            }
            j++;
        }
        else {
            nova_mat[nv] = stara_mat[i];

            if (sum[j].Promena == IZLAZ && sum[j].Kolicina > stara_mat[i].Kolicina) {
                greske_kol[ngk++] = sum[j];
                nova_mat[nv++] = stara_mat[i++];
            }
            else {
                if (sum[j].Promena == ULAZ) {
                    nova_mat[nv].Kolicina += sum[j].Kolicina;
                }
                else {
                    nova_mat[nv].Kolicina -= sum[j].Kolicina;
                }
                nv++;
                i++;
            }
            j++;
        }
    }

    printf("%-35s | %-35s\n", "SUMARNA TRANSAKCIONA", "NOVA MATICNA");
    printf("%-10s %-10s %-13s | %-10s %-15s %-8s\n",
        "ID", "Promena", "Kolicina", "ID", "Naziv", "Kolicina");
    printf("------------------------------------+------------------------------------\n");

    max_rows = (ns > nv) ? ns : nv;
    for (int i = 0; i < max_rows; i++) {
        if (i < ns) {
            printf("%-10u %-10s %-13u | ",
                sum[i].Id,
                sum[i].Promena == ULAZ ? "ULAZ" : "IZLAZ",
                sum[i].Kolicina);
        }
        else {
            printf("%-35s | ", "");
        }

        if (i < nv) {
            printf("%-10u %-15s %-8u\n",
                nova_mat[i].Id, nova_mat[i].Naziv, nova_mat[i].Kolicina);
        }
        else {
            printf("\n");
        }
    }

    printf("\n");

    if (np > 0) {
        printf("========================================================================\n");
        printf("NOVI PROIZVODI\n");
        printf("========================================================================\n");
        printf("%-10s %-15s %-10s\n", "ID", "Naziv", "Kolicina");
        printf("--------------------------------------\n");
        for (int i = 0; i < np; i++) {
            printf("%-10u %-15s %-10u\n",
                novi_proizvodi[i].Id, novi_proizvodi[i].Naziv, novi_proizvodi[i].Kolicina);
        }
        printf("\n");
    }

    if (ngk > 0) {
        printf("========================================================================\n");
        printf("GRESKE - NEPOSTOJECA KOLICINA\n");
        printf("========================================================================\n");
        printf("%-10s %-10s %-10s\n", "ID", "Promena", "Kolicina");
        printf("------------------------------------\n");
        for (int i = 0; i < ngk; i++) {
            printf("%-10u %-10s %-10u\n",
                greske_kol[i].Id, "IZLAZ", greske_kol[i].Kolicina);
        }
        printf("\n");
    }

    if (ngp > 0) {
        printf("========================================================================\n");
        printf("GRESKE - NEPOSTOJECI PROIZVOD\n");
        printf("========================================================================\n");
        printf("%-10s %-10s %-10s\n", "ID", "Promena", "Kolicina");
        printf("------------------------------------\n");
        for (int i = 0; i < ngp; i++) {
            printf("%-10u %-10s %-10u\n",
                greske_pro[i].Id, "IZLAZ", greske_pro[i].Kolicina);
        }
        printf("\n");
    }

    pauziraj();
}

void kreirajInfoTxt() {
    FILE* f = fopen(INFO_TXT, "w");
    if (f) {
        fprintf(f, "========================================================================\n");
        fprintf(f, "APLIKACIJA: ASD - Azuriranje Serijske Datoteke\n");
        fprintf(f, "========================================================================\n\n");
        fprintf(f, "Verzija: 1.0\n");
        fprintf(f, "Slucaj : 5 - Sveobuhvatni slucaj\n");
        fprintf(f, "Autor  : Sara Da Rold, sd20220413@student.fon.bg.ac.rs\n");
        fprintf(f, "Mentor : Sasa D. Lazarevic, slazar@fon.rs\n\n");
        fprintf(f, "========================================================================\n");
        fprintf(f, "UPOTREBA:\n");
        fprintf(f, "========================================================================\n\n");
        fprintf(f, "Program se pokrece komandom: asd.exe\n\n");
        fprintf(f, "Struktura foldera:\n");
        fprintf(f, ".\\ASD\\DATA\\          - Aktivne datoteke (maticna.dat, transakciona.dat)\n");
        fprintf(f, ".\\ASD\\DATA\\OLD\\     - Arhivirane datoteke (mat_YYMMDD.dat, tran_YYMMDD.dat)\n");
        fprintf(f, ".\\ASD\\RPT\\           - Izvestaji (prom_YYMMDD.rpt, nov_pro_YYMMDD.rpt)\n");
        fprintf(f, ".\\ASD\\ERR\\           - Izvestaji o greskama (err_kol_YYMMDD.rpt, err_pro_YYMMDD.rpt)\n");
        fprintf(f, ".\\ASD\\DEMO\\          - Demo podaci\n\n");
        fprintf(f, "========================================================================\n");
        fprintf(f, "SLUCAJ 5 - SVEOBUHVATNI SLUCAJ - Karakteristike:\n");
        fprintf(f, "========================================================================\n\n");
        fprintf(f, "Kombinuje sve prethodne slucajeve\n");
        fprintf(f, "Scenariji: D.1.+D.3.=I.1., D.1.+D.4.=I.1., D.1.+D.4.=I.2., D.2.+D.3.=I.1., D.2.+D.4.=I.2.\n");
        fprintf(f, "Generisu se svi izvestaji prema potrebi\n\n");
        fclose(f);
    }
}

void kreirajDemoPodatke() {
    char demo_mat_path[] = ".\\ASD\\DEMO\\maticna.dat";
    FILE* f = fopen(demo_mat_path, "wb");
    if (f) {
        PROIZVOD demo_mat[] = {
            {20, "Pro_20", 100},
            {30, "Pro_30", 150},
            {40, "Pro_40", 200},
            {50, "Pro_50", 250},
            {60, "Pro_60", 300},
            {70, "Pro_70", 350},
            {80, "Pro_80", 400},
            {90, "Pro_90", 450}
        };
        fwrite(demo_mat, sizeof(PROIZVOD), 8, f);
        fclose(f);
    }

    char demo_tran5[] = ".\\ASD\\DEMO\\SLUC_5\\transakciona.dat";
    f = fopen(demo_tran5, "wb");
    if (f) {
        TRANSAKCIJA demo_tran[] = {
            {20, ULAZ, 50},
            {70, IZLAZ, 50},
            {90, IZLAZ, 50},
            {50, IZLAZ, 800},
            {60, IZLAZ, 800},
            {35, ULAZ, 150},
            {15, ULAZ, 150},
            {22, IZLAZ, 175},
            {92, IZLAZ, 175},
            {20, ULAZ, 50},
            {70, IZLAZ, 50},
            {90, ULAZ, 50}
        };
        fwrite(demo_tran, sizeof(TRANSAKCIJA), 12, f);
        fclose(f);
    }
}

void inicijalizujAplikaciju() {
    kreirajFoldere();
    kreirajInfoTxt();
    kreirajDemoPodatke();
    if (!fajlPostoji(MAT_DAT)) {
        char demo_mat[] = ".\\ASD\\DEMO\\maticna.dat";
        if (fajlPostoji(demo_mat)) {
            kopirajFajl(demo_mat, MAT_DAT);
        }
    }

    if (!fajlPostoji(TRAN_DAT)) {
        char demo_tran[] = ".\\ASD\\DEMO\\SLUC_5\\transakciona.dat";
        if (fajlPostoji(demo_tran)) {
            kopirajFajl(demo_tran, TRAN_DAT);
        }
    }
}