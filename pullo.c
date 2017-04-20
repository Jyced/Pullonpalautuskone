/* 
CT C-ohjelmoinnin ja testauksen perusteet 2017 ohjelmien otsikkotiedot.
Harjoitustyö: Pullonpalautusautomaatti
Päivämäärä: 10.3.2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pullo.h"
#include "apu.h"
#include "tiedosto.h"
#include "tietorakenteet.h"
#define MAX 50

//Tämä aliohjelma varaa muisti syötteitä varten ja rakentaa linkitettyä listaa
Pullo *varaaMuistiSyotetteelle(Pullo *pAlkuValikko, Pullo *pAlkuSyote, int valinta){
	Pullo *pTempSyote, *pLoppuSyote;

	if((pTempSyote = malloc(sizeof(Pullo))) == NULL){
		perror("Muistinvaraus epäonnistui!");
		exit(1);
	}
	/* Käydään valikkolista läpi valittuun tuotteeseen asti. */
	Pullo *pTempValikko = pAlkuValikko;
	int i;
	for(i=1; i<valinta; i++){
		pTempValikko = pTempValikko->pSeuraava;
	}
	/* Valikkolistan läpikäynti loppuu. */
	if((pTempSyote->pNimi = malloc(sizeof(pTempValikko->pNimi))) == NULL){
		perror("Muistinvaraus epäonnistui!");
		exit(1);
	}
	//Lisätään listaan nimi-, koko- ja hintatiedot.
	strcpy(pTempSyote->pNimi, pTempValikko->pNimi);
	pTempSyote->koko = pTempValikko->koko;
	pTempSyote->hinta = pTempValikko->hinta;
	pTempSyote->pSeuraava = NULL;

	kirjoitaTilapainenLokitiedosto(pTempSyote->pNimi, pTempSyote->koko, pTempSyote->hinta, pAlkuSyote);
	printf("\nSyötetty: %s %3.2fl\n",pTempSyote->pNimi, pTempSyote->koko);

	if (pAlkuSyote == NULL){ //Jos tehdään ensimmäinen alkio, niin mennään tähän.
		pAlkuSyote = pTempSyote;
	}
	else{
		pLoppuSyote = pAlkuSyote;
		while (pLoppuSyote->pSeuraava != NULL){
			pLoppuSyote = pLoppuSyote->pSeuraava;
		}
		pLoppuSyote->pSeuraava = pTempSyote;
	}
	return (pAlkuSyote);
}
//Tämä aliohjelma varaa valikkotietoja varten ja rakentaa linkitettyä listaa
Pullo *varaaMuistiValikolle(Pullo *pAlkuValikko, char *pPulloNimi, float pulloHinta, float pulloKoko){
	Pullo *pTempValikko, *pLoppuValikko;

	if((pTempValikko = malloc(sizeof(Pullo))) == NULL){
		perror("Muistinvaraus epäonnistui!");
		exit(1);
	}
	if((pTempValikko->pNimi = malloc(sizeof(pPulloNimi))) == NULL){
		perror("Muistinvaraus epäonnistui!");
		exit(1);
	}
	//Lisätään listaan nimi-, koko- ja hintatiedot.
	strcpy(pTempValikko->pNimi, pPulloNimi);
	pTempValikko->koko = pulloKoko;
	pTempValikko->hinta = pulloHinta;
	pTempValikko->pSeuraava = NULL;
	
	if (pAlkuValikko == NULL){
		pAlkuValikko = pTempValikko;
	}
	else{
		pLoppuValikko = pAlkuValikko;
		while (pLoppuValikko->pSeuraava != NULL){
			pLoppuValikko = pLoppuValikko->pSeuraava;
		}
		pLoppuValikko->pSeuraava = pTempValikko;
	}
	return pAlkuValikko;
}
void vapautaMuistiValikolta(Pullo *pAlkuValikko){
	Pullo *pTempValikko = pAlkuValikko;
	if (pAlkuValikko != NULL){
		while (pTempValikko != NULL){
			pAlkuValikko = pTempValikko->pSeuraava;
			// printf("Vapautetaan valikkorakenteesta %s.\n", pTempValikko->pNimi); //Tarkistus
			free(pTempValikko->pNimi);
			free(pTempValikko);
			pTempValikko = pAlkuValikko;
		}
	}
}
void vapautaMuistiSyotteelta(Pullo *pAlkuSyote){
	Pullo *pTempSyote = pAlkuSyote;
	if (pAlkuSyote != NULL){
		while (pTempSyote != NULL){
			pAlkuSyote = pTempSyote->pSeuraava;
			// printf("Vapautetaan syötteen listasta %s.\n", pTempSyote->pNimi); //Tarkistus
			free(pTempSyote->pNimi);
			free(pTempSyote);
			pTempSyote = pAlkuSyote;
		}
	}
}
//Dynaamisen valikkorakenteen tulostaminen luodun valikko-linkitetyn listan avulla
int tulostaValikko(Pullo *pAlkuValikko){
	Pullo *pTempValikko = pAlkuValikko;
	int kierros = 1;

	if (pAlkuValikko == NULL){
		printf("Lista on tyhjä!\n");
	}
	else{
		while (pTempValikko != NULL){
			printf("%d) %s %3.2fl\n", kierros, pTempValikko->pNimi, pTempValikko->koko); //esim: 1) pullo 0.33l
			pTempValikko = pTempValikko->pSeuraava;
			kierros++;
		}
		printf("%d) Lopeta syöttö ja tulosta kuitti.\n", kierros);
	}
	return(kierros);
}
void tulostaKuitti(Pullo *pAlkuValikko, Pullo *pAlkuSyote){
	int tuoteLaskuri = 0;
	float summa = 0;
	float tuoteSumma = 0;

	printf("\n\nKuitti\n\n\n");
	Pullo *pTempSyote = pAlkuSyote;
	Pullo *pTempValikko = pAlkuValikko;
	if (pTempSyote == NULL) {
		printf("Et palauttanut pulloja!\n");
	}
	else {
		while (pTempSyote != NULL) {
			tuoteLaskuri++;
			pTempSyote = pTempSyote->pSeuraava;
		}
		printf("Palautetut pullot ja tölkit yhteensä %d kappaletta.\n\n", tuoteLaskuri);
		tuoteLaskuri = 0;
		pTempSyote = pAlkuSyote;

		while (pTempValikko != NULL) { //Käydään jokainen valikossa oleva alkio läpi
			pTempSyote = pAlkuSyote;
			tuoteLaskuri = 0;
			tuoteSumma = 0;
			while (pTempSyote != NULL) { // Verrataan syötelistassa olevia alkioita valikkolistassa oleviin, jonka perusteella tulostetaan kuitti.
				if((strcmp(pTempValikko->pNimi, pTempSyote->pNimi) == 0) && (pTempValikko->koko == pTempSyote->koko)){
					tuoteSumma = tuoteSumma + pTempSyote->hinta;
					tuoteLaskuri++;
				}
				pTempSyote = pTempSyote->pSeuraava;
			}
			if (tuoteLaskuri != 0){
				//Kuittiin tulostuu esim: pullo 0.33l summa 1 x 0.10 = 0.10€
				printf("%s %3.2fl pantit %d x %3.2f = %3.2f€\n",pTempValikko->pNimi, pTempValikko->koko, tuoteLaskuri, pTempValikko->hinta, tuoteSumma);
				summa = summa + tuoteSumma;
			}
			pTempValikko = pTempValikko->pSeuraava;
		}
	}
	printf("\nPantit yhteensä %3.2f€\n\n\n", summa);
}
//Päävalikkorakenne, joka toimii dynaamisesti tuotetiedosto.txt mukaan.
void pullonPalautus(){
	int valinta =-1;
	char valintaMerkki[MAX];
	int kierros = -2;
	Pullo *pAlkuValikko = NULL;
	Pullo *pAlkuSyote = NULL;
	pAlkuValikko = lueTuotetiedot(pAlkuValikko); //Luetaan tuotetiedosto.txt kerran ja tehdään sen sisällöstä linkitetty lista.
	if (pAlkuValikko != NULL){; 
		while(valinta != kierros){
			printf("Syötä uusi pullo tai tölkki.\n\n");
			kierros = tulostaValikko(pAlkuValikko); //Tulostetaan valikko annettujen tuotetietojen pohjalta.
			printf("--> ");
			fgets(valintaMerkki, MAX, stdin);

			int testaus=SyoteTarkistus(valintaMerkki); //Tarkistetaan syötteen oikeellisuus
			if (testaus==0){
				printf("Väärä valinta!\n");
			}
			else{
				valinta = atoi(valintaMerkki);
				if (valinta>0 && valinta<kierros){
					pAlkuSyote = varaaMuistiSyotetteelle(pAlkuValikko, pAlkuSyote, valinta); //Luodaan annetuille syötteille oma lista.
				}
				else if (valinta == kierros){
					tulostaKuitti(pAlkuValikko, pAlkuSyote);
					break;
				}
				else{
					printf("Väärä valinta!\n");
				}
			}
		}
		kirjoitaLokitiedosto(pAlkuSyote);
		
		//Vapautetaan muisti.
		vapautaMuistiSyotteelta(pAlkuSyote);
		vapautaMuistiValikolta(pAlkuValikko);
		printf("\nPULLONPALAUTUSAUTOMAATTI\n");
	}
	else{
		printf("Virhe tuotetietojen lukemisessa. Tarkista tuotetiedosto.txt\n");
	}
}

/* eof */