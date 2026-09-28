#ifndef ADTS_H
#define ADTS_H

#include "defs.h"

void ocistiBuffer();
int ucitajID(unsigned* id);
int ucitajKolicinu(unsigned* kolicina);
int ucitajPotvrdu(const char* pitanje);
int ucitajPromenu(PROMENA* promena);



void prikaziGlavniMeni();
void prikaziMeniTransakciona();
void prikaziMeniMaticna();
void prikaziMeniPomoc();
void prikaziMeniDemo();
void ocistiEkran();
void pauziraj();
int ucitajOpciju();



void kreirajMaticnu();
void unistiMaticnu();
void dodajProizvod();
void obrisiProizvod();
void azurirajSve();
void azurirajProizvod();
void prikaziSveProizvode();
void prikaziProizvod();



void kreirajTransakcionu();
void unistiTransakcionu();
void dodajTransakciju();
void prikaziSveTransakcije();
void prikaziTransakcijeProizvoda();

#endif