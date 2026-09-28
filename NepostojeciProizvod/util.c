#define _CRT_SECURE_NO_WARNINGS
#include "util.h"
#include <limits.h>

void kreirajFoldere() {

    if (_mkdir(ASD_ROOT) != 0 && errno != EEXIST) {
        printf("Doslo je do problema pri kreiranju %s\n", ASD_ROOT);
    }

    if (_mkdir(ASD_DATA) != 0 && errno != EEXIST) {
        printf("Doslo je do problema pri kreiranju %s\n", ASD_DATA);
    }
    if (_mkdir(ASD_OLD) != 0 && errno != EEXIST) {
        printf("Doslo je do problema pri kreiranju %s\n", ASD_OLD);
    }
    if (_mkdir(ASD_RPT) != 0 && errno != EEXIST) {
        printf("Doslo je do problema pri kreiranju %s\n", ASD_RPT);
    }

    if (_mkdir(ASD_ERR) != 0 && errno != EEXIST) {
        printf("Doslo je do problema pri kreiranju %s\n", ASD_ERR);
    }
    if (_mkdir(ASD_DEMO) != 0 && errno != EEXIST) {
        printf("Doslo je do problema pri kreiranju %s\n", ASD_DEMO);
    }
    _mkdir(".\\ASD\\DEMO\\SLUC_1");
    _mkdir(".\\ASD\\DEMO\\SLUC_2");
    _mkdir(".\\ASD\\DEMO\\SLUC_3");
    _mkdir(".\\ASD\\DEMO\\SLUC_4");
    _mkdir(".\\ASD\\DEMO\\SLUC_5");
}

void vratiDatum(char* datum) {
    if (!datum) {
        printf("Doslo je do greske.\n");
        return;
    }

    time_t t = time(NULL);
    if (t == -1) {
        printf("Doslo je do greske.\n");
        strcpy(datum, "000000");
        return;
    }

    struct tm* tm_info = localtime(&t);
    if (!tm_info) {
        printf("Doslo je do greske.\n");
        strcpy(datum, "000000");
        return;
    }

    sprintf(datum, "%02d%02d%02d",
        tm_info->tm_year % 100,
        tm_info->tm_mon + 1,
        tm_info->tm_mday);
}

int fajlPostoji(const char* path) {
    if (!path) return 0;

    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

int kreirajPutanju(char* dest, const char* folder, const char* prefix, const char* datum, const char* ext) {
    if (!dest || !folder || !prefix || !datum || !ext) {
        printf("Doslo je do greske.\n");
        return 0;
    }

    size_t total_len = strlen(folder) + strlen(prefix) + strlen(datum) + strlen(ext) + 3;
    if (total_len > 255) {
        printf("Putanja je predugacka (%zu karaktera).\n", total_len);
        return 0;
    }

    sprintf(dest, "%s%s_%s.%s", folder, prefix, datum, ext);
    return 1;
}

int sortirajProizvode(const void* a, const void* b) {
    if (!a || !b) {
        printf("Doslo je do greske.\n");

        return 0;
    }

    const PROIZVOD* pa = (const PROIZVOD*)a;
    const PROIZVOD* pb = (const PROIZVOD*)b;

    if (pa->Id < pb->Id) return -1;
    if (pa->Id > pb->Id) return 1;
    return 0;
}

int sortirajTransakcije(const void* a, const void* b) {
    if (!a || !b) {
        printf("Doslo je do greske.\n");
        return 0;
    }

    const TRANSAKCIJA* ta = (const TRANSAKCIJA*)a;
    const TRANSAKCIJA* tb = (const TRANSAKCIJA*)b;

    if (ta->Id < tb->Id) return -1;
    if (ta->Id > tb->Id) return 1;

    return 0;
}

int sumirà¼Transakcije(const char* tran_dat, const char* tran_sum) {

    if (!tran_dat || !tran_sum) {
        printf("Doslo je do greske.\n");
        return 0;
    }

    FILE* f = fopen(tran_dat, "rb");

    if (!f) {
        printf("Doslo je do greske pri otvaranju %s.\n", tran_dat);
        return 0;
    }

    TRANSAKCIJA trans[MAX_PROIZVODA], sum[MAX_PROIZVODA];
    int n = 0, s = 0, i, j, found;

    while (fread(&trans[n], sizeof(TRANSAKCIJA), 1, f) == 1) {
        n++;
        if (n >= MAX_PROIZVODA) {
            fclose(f);
            printf("Previse transakcija (%d) je dovelo do greske.\n", MAX_PROIZVODA);
            return 0;
        }
    }
    fclose(f);

    if (n == 0) {
        f = fopen(tran_sum, "wb");
        if (f) fclose(f);
        return 1;
    }

    for (i = 0; i < n; i++) {
        found = -1;
        for (j = 0; j < s; j++) {
            if (sum[j].Id == trans[i].Id) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            if (s >= MAX_PROIZVODA) {
                printf("Previse jedinstvenih ID-ova u transakcijama.\n");
                return 0;
            }
            sum[s++] = trans[i];
        }
        else {
            long long stara_kol = (sum[found].Promena == ULAZ) ?
                (long long)sum[found].Kolicina :
                -(long long)sum[found].Kolicina;
            long long nova_trans = (trans[i].Promena == ULAZ) ?
                (long long)trans[i].Kolicina :
                -(long long)trans[i].Kolicina;
            long long suma = stara_kol + nova_trans;

            if (suma > UINT_MAX) {
                printf("Zbir transakcija za ID=%u je prevelik (%lld). "
                    "Postavljam kolicinu na maksimalnu dozvoljenu vrednost %u.\n", sum[found].Id);
                sum[found].Kolicina = UINT_MAX;
                sum[found].Promena = ULAZ;
            }
            else if (suma < -((long long)UINT_MAX)) {
                printf("Zbir transakcija za ID=%u je suvise mali (%lld). "
                    "Postavljam kolicinu na %u i promenu na IZLAZ.\n", sum[found].Id);
                sum[found].Kolicina = UINT_MAX;
                sum[found].Promena = IZLAZ;
            }
            else if (suma >= 0) {
                sum[found].Kolicina = (unsigned)suma;
                sum[found].Promena = ULAZ;
            }
            else {
                sum[found].Kolicina = (unsigned)(-suma);
                sum[found].Promena = IZLAZ;
            }
        }
    }

    if (s > 0) {
        qsort(sum, s, sizeof(TRANSAKCIJA), sortirajTransakcije);
    }

    f = fopen(tran_sum, "wb");
    if (!f) {
        printf("Greska pri kreiranju %s.\n", tran_sum);
        return 0;
    }

    if (s > 0) {
        if (fwrite(sum, sizeof(TRANSAKCIJA), s, f) != s) {
            printf("Greska pri upisu u %s.\n", tran_sum);
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    return 1;
}

void generisiNazivProizvoda(unsigned Id, char* naziv) {
    if (!naziv) {
        printf("Doslo je do greske pri generisanju naziva proizvoda.\n");
        return;
    }

    if (Id < 1 || Id > 9999) {
        printf("ID %u van opsega, naziv moze biti neispravan.\n", Id);
    }

    int written = sprintf(naziv, "Pro_%u", Id);

    if (written > 14) {
        printf("Naziv proizvoda je duzi od 14 karaktera.\n");
        naziv[14] = '\0';
    }
}

void kopirajFajl(const char* src, const char* dst) {
    if (!src || !dst) {
        printf("Doslo je do greske.\n");
        return;
    }

    FILE* fs = fopen(src, "rb");
    if (!fs) {
        printf("Doslo je do greske pri otvaranju fajla %s.\n", src);
        return;
    }

    FILE* fd = fopen(dst, "wb");
    if (!fd) {
        printf("Doslo je do greske pri kreiranju fajla %s.\n", dst);
        fclose(fs);
        return;
    }

    char buf[4096];
    size_t n;

    int uspesno = 1;

    while ((n = fread(buf, 1, sizeof(buf), fs)) > 0) {

        if (fwrite(buf, 1, n, fd) != n) {
            printf("Doslo je do greske pri upisu u %s.\n", dst);
            uspesno = 0;
            break;
        }
    }

    fclose(fs);

    fclose(fd);

    if (!uspesno) {
        remove(dst);
    }
}