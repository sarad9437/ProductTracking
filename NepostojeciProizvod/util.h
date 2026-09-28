#ifndef UTIL_H
#define UTIL_H
#include "defs.h"
#include <errno.h>


void kreirajFoldere();


void vratiDatum(char* datum);


int fajlPostoji(const char* path);
int kreirajPutanju(char* dest, const char* folder, const char* prefix, const char* datum, const char* ext);
void kopirajFajl(const char* src, const char* dst);


int sortirajProizvode(const void* a, const void* b);
int sortirajTransakcije(const void* a, const void* b);



int sumirajTransakcije(const char* tran_dat, const char* tran_sum);

void generisiNazivProizvoda(unsigned Id, char* naziv);

#endif