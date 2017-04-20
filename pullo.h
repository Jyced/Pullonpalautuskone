/* 
CT C-ohjelmoinnin ja testauksen perusteet 2017 ohjelmien otsikkotiedot.
Harjoitustyö: Pullonpalautusautomaatti
Päivämäärä: 8.3.2017
*/

#include "tietorakenteet.h"

Pullo *varaaMuistiValikolle(Pullo *, char *, float , float);
Pullo *varaaMuistiSyotetteelle(Pullo *, Pullo *, int);
void vapautaMuistiValikolta(Pullo *);
void vapautaMuistiSyotteelta(Pullo *);
void pullonPalautus();
int tulostaValikko(Pullo *);
void tulostaKuitti(Pullo *, Pullo *);

/* eof */
