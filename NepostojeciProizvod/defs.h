#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
#include <direct.h>


typedef struct {
    unsigned Id;
    char Naziv[15];
    unsigned Kolicina;
} PROIZVOD;

typedef enum {
    IZLAZ = -1,
    ULAZ = 1
} PROMENA;

typedef struct {
    unsigned Id;
    PROMENA Promena;
    unsigned Kolicina;
} TRANSAKCIJA;



#define ASD_ROOT ".\\ASD\\"
#define ASD_DATA ".\\ASD\\DATA\\"
#define ASD_OLD ".\\ASD\\DATA\\OLD\\"
#define ASD_RPT ".\\ASD\\RPT\\"
#define ASD_ERR ".\\ASD\\ERR\\"
#define ASD_DEMO ".\\ASD\\DEMO\\"
#define MAT_DAT ".\\ASD\\DATA\\maticna.dat"
#define TRAN_DAT ".\\ASD\\DATA\\transakciona.dat"
#define INFO_TXT ".\\ASD\\info.txt"


#define MAX_LINE 256
#define MAX_PROIZVODA 1000
#define DATUM_LEN 7
#define PAGE_SIZE 20

#endif