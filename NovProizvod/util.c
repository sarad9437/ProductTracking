#define _CRT_SECURE_NO_WARNINGS
#include "util.h"

void kreirajFoldere() {
    _mkdir(ASD_ROOT);
    _mkdir(ASD_DATA);
    _mkdir(ASD_OLD);
    _mkdir(ASD_RPT);
    _mkdir(ASD_ERR);
    _mkdir(ASD_DEMO);
    _mkdir(".\\ASD\\DEMO\\SLUC_1");
    _mkdir(".\\ASD\\DEMO\\SLUC_2");
    _mkdir(".\\ASD\\DEMO\\SLUC_3");
    _mkdir(".\\ASD\\DEMO\\SLUC_4");
    _mkdir(".\\ASD\\DEMO\\SLUC_5");
}

void vratiDatum(char* datum) {
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    sprintf(datum, "%02d%02d%02d", tm->tm_year % 100, tm->tm_mon + 1, tm->tm_mday);
}

int fajlPostoji(const char* path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

int kreirajPutanju(char* dest, const char* folder, const char* prefix, const char* datum, const char* ext) {
    sprintf(dest, "%s%s_%s.%s", folder, prefix, datum, ext);
    return 1;
}

int sortirajProizvode(const void* a, const void* b) {
    return (int)((PROIZVOD*)a)->Id - (int)((PROIZVOD*)b)->Id;
}

int sortirajTransakcije(const void* a, const void* b) {
    return (int)((TRANSAKCIJA*)a)->Id - (int)((TRANSAKCIJA*)b)->Id;
}

int sumirajTransakcije(const char* tran_dat, const char* tran_sum) {
    FILE* f = fopen(tran_dat, "rb");
    if (!f) return;

    TRANSAKCIJA trans[MAX_PROIZVODA], sum[MAX_PROIZVODA];
    int n = 0, s = 0, i, j, found;

    while (fread(&trans[n], sizeof(TRANSAKCIJA), 1, f) == 1) n++;
    fclose(f);

    for (i = 0; i < n; i++) {
        found = -1;
        for (j = 0; j < s; j++) {
            if (sum[j].Id == trans[i].Id) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            sum[s++] = trans[i];
        }
        else {
            int stara_kol = (sum[found].Promena == ULAZ) ? (int)sum[found].Kolicina : -(int)sum[found].Kolicina;
            int nova_trans = (trans[i].Promena == ULAZ) ? (int)trans[i].Kolicina : -(int)trans[i].Kolicina;
            int suma = stara_kol + nova_trans;

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

    qsort(sum, s, sizeof(TRANSAKCIJA), sortirajTransakcije);

    f = fopen(tran_sum, "wb");
    if (f) {
        fwrite(sum, sizeof(TRANSAKCIJA), s, f);
        fclose(f);
    }
}

void generisiNazivProizvoda(unsigned Id, char* naziv) {
    sprintf(naziv, "Pro_%u", Id);
}

void kopirajFajl(const char* src, const char* dst) {
    FILE* fs = fopen(src, "rb");
    FILE* fd = fopen(dst, "wb");

    if (fs && fd) {
        char buf[4096];
        size_t n;
        while ((n = fread(buf, 1, sizeof(buf), fs)) > 0) {
            fwrite(buf, 1, n, fd);
        }
    }

    if (fs) fclose(fs);
    if (fd) fclose(fd);
}