/* 
CT C-ohjelmoinnin ja testauksen perusteet 2017 ohjelmien otsikkotiedot.
Harjoitustyö: Pullonpalautusautomaatti
Päivämäärä: 8.3.2017
*/

#ifndef STRUCT_H 
#define STRUCT_H

struct pullo {
	char *pNimi;
	float hinta;
	float koko;
	struct pullo *pSeuraava;
}; 
typedef struct pullo Pullo;

#endif

/* eof */
