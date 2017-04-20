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
#include "yllapito.h"
#define MAX 50

int main(void){
	int valinta = -1;
	char valintaMerkki[MAX];

	char annettuSalasana[MAX];
	char oikeaSalasana[MAX] = "salasana";
	char *pOikeaSalasana;
	char *pAnnettuSalasana;

	pAnnettuSalasana = annettuSalasana;
	pOikeaSalasana = oikeaSalasana;

	printf("\nPULLONPALAUTUSAUTOMAATTI\n");
	while(valinta != 0){

		printf("\nAutomaatti on toimintavalmis.\n\n");
		printf("1) Aloita palautus\n");
		printf("2) Kutsu henkilökunta\n");
		printf("3) Ylläpito\n");
		printf("0) Lopeta\n\n");
		printf("Valitse: ");
		fgets(valintaMerkki, MAX, stdin);

		int testaus=SyoteTarkistus(valintaMerkki);
		if (testaus==0){
			printf("Väärä valinta!\n");
		}
		else{
			valinta = atoi(valintaMerkki);
			if (valinta == 1){
				pullonPalautus();
			}
			else if(valinta == 2){
				printf("Henkilökunta hälytetty paikalle!\n");
				printf("Konevalmistajan tavoitat numerosta: 03489333\n");
			}
			else if(valinta == 3){
				printf("Anna salasana: ");
				fgets(annettuSalasana, MAX, stdin);
				annettuSalasana[strcspn(annettuSalasana, "\n")] = 0;
				if (strcmp(pAnnettuSalasana, pOikeaSalasana) == 0){
					printf("Siirrytään ylläpitoon...\n");
					yllapitovalikko();
				}
				else{
					printf("Annoit väärän salasanan!\n");
				}
			}
			else if(valinta == 0){
				printf("Suljetaan pullonpalautusautomaatti.\n");
				break;
			}
			else{
				printf("Annoit väärän valinnan!\n");
			}
		}
	}
	return 0;
}

/* eof */
