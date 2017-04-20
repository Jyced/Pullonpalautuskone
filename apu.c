/* 
CT C-ohjelmoinnin ja testauksen perusteet 2017 ohjelmien otsikkotiedot.
Harjoitustyö: Pullonpalautusautomaatti
Päivämäärä: 10.3.2017
*/

#include <string.h>
#include <ctype.h>
#include "apu.h"
#define MAX 50

//Aliohjelman tarkoituksena on tarkastaa käyttäjältä saatu syöte
int SyoteTarkistus (char merkki[MAX]){
	int i=0;
	int toimivuus=1; //Toimivuus on 1, jos syöte on ok. & Toimivuus on 0, jos syöte ei ole ok.
	while (i< strlen(merkki)-1){ //tarkistetaan koko merkkijono ettei löydy numeroita
		toimivuus=isdigit(merkki[i]); //jos merkki on numero, isdigit palautetaan 0
		i++;
	}
	if (strlen(merkki)>2||strlen(merkki)==1){
		toimivuus=0; // testataan onko input oikean pituinen, jos pituudessa vikaa, muutetaan palautuksen arvo nollaksi (oikea pituus 2; merkki+loppumerkki)
	}
	return toimivuus;
}

/* eof */