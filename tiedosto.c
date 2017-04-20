/* 
CT C-ohjelmoinnin ja testauksen perusteet 2017 ohjelmien otsikkotiedot.
Harjoitustyö: Pullonpalautusautomaatti
Päivämäärä: 10.3.2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tiedosto.h"
#include "pullo.h"
#include "apu.h"
#include "tietorakenteet.h"
#define MAX 50

void kirjoitaTilapainenLokitiedosto(char *pNimi, float koko, float hinta, Pullo *pAlkuSyote){
	time_t nykyinenAika;
	FILE *tiedosto;

	if (pAlkuSyote == NULL){
		if((tiedosto = fopen("tilapaistiedosto.txt","w")) == NULL){
			perror("Tilapäislokitiedoston kirjoittaminen epäonnistui!\n");
		}
		fprintf(tiedosto,"Tilapäinen lokitiedosto\n\n\n");
	}
	else{
		if((tiedosto = fopen("tilapaistiedosto.txt","a+")) == NULL){
			perror("Tilapäislokitiedoston kirjoittaminen epäonnistui!\n");
		}
	}
	time(&nykyinenAika);
	struct tm *minunAika = localtime(&nykyinenAika); // struct tm sisäänrakennettu time.h:on
	fprintf(tiedosto,"%02i.%02i.%i %02i:%02i:%s-%4.2fl:%4.2f€.\n",
		minunAika->tm_mday, minunAika->tm_mon+1, minunAika->tm_year + 1900, minunAika->tm_hour, minunAika->tm_min, pNimi, koko, hinta);
	fclose(tiedosto);
}
void kirjoitaLokitiedosto(Pullo *pAlkuSyote){
	Pullo *pLoppuSyote;
	int laskuri = 0;
	float summa = 0;
	time_t nykyinenAika;

	FILE *tiedosto;
	if((tiedosto = fopen("lokitiedosto.txt","a")) == NULL){
		perror("Lokitiedoston kirjoittaminen epäonnistui!\n");
	}
	if (pAlkuSyote != NULL){
		pLoppuSyote = pAlkuSyote;
		while (pLoppuSyote != NULL){
			laskuri++;
			summa = summa + pLoppuSyote->hinta;
			pLoppuSyote = pLoppuSyote->pSeuraava;
		}
		time(&nykyinenAika);
		struct tm *minunAika = localtime(&nykyinenAika);
		fprintf(tiedosto,"%02i.%02i.%i %02i:%02i - Palautukset %d kpl. Pantit %3.2f€.\n",
			minunAika->tm_mday, minunAika->tm_mon+1, minunAika->tm_year + 1900, minunAika->tm_hour, minunAika->tm_min, laskuri,summa); //mon laskuri alkaa nollasta, siksi +1, samoin vuosilaskuri alkaa häröstä kohtaa
	}
	fclose(tiedosto);
}
Pullo *lueTuotetiedot(Pullo *pAlkuValikko){
	FILE *tiedosto;
	char rivi[MAX];
	char *pPulloNimi;
	char *pPulloKoko;
	char *pPulloHinta;
	float pulloKoko;
	float pulloHinta;

	if ((tiedosto = fopen("tuotetiedosto.txt", "r")) == NULL){
		return pAlkuValikko; // Virheilmoitus tulostuu pullonPalautus aliohjelmasta.
	}
	else{
		while(fgets(rivi, MAX, tiedosto) != NULL) { //Luetaan rivi kerrallaan tuotetiedostosta.
			pPulloNimi = strtok(rivi, " ");
			pPulloKoko = strtok(NULL, " ");
			pPulloHinta = strtok(NULL, "\n");
			if (pPulloHinta == NULL || pPulloKoko == NULL || pPulloHinta == NULL) {
				break;
			}
			pulloKoko = atof(pPulloKoko);
			pulloHinta = atof(pPulloHinta);
			pAlkuValikko = varaaMuistiValikolle(pAlkuValikko, pPulloNimi, pulloHinta, pulloKoko); //Varataan muisti kullekin valikon valinnalle.	
		}
	}
	fclose(tiedosto);
	return pAlkuValikko; //Palautetaan pointteri luodun listan alkuun.
}

/* eof */
