/* 
Ylläpitomoduuli
CT C-ohjelmoinnin ja testauksen perusteet 2017 ohjelmien otsikkotiedot.
Harjoitustyö: Pullonpalautusautomaatti
Päivämäärä: 10.3.2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "apu.h"
#define MAX 60

//Tämä aliohjelma tulostaa tuotetiedoston, jonka jälkeen voidaan tehdä johtopäätöksiä mahdollisesta muokkaamisesta
void tulostaTuotetiedosto(){
	FILE *tiedosto;
	char rivi[MAX];
	int rivimaara = 0;

	if ((tiedosto = fopen("tuotetiedosto.txt", "r")) == NULL){
		printf("\nVirhe tuotetiedoston avaamisessa!\n");
		exit(1);
	}
	while(fgets(rivi, MAX, tiedosto) != NULL) {
		rivimaara++;
	}
	if (rivimaara > 0){
		rewind(tiedosto);
		printf("\nNykyiset tuotteet:\n");
		while(fgets(rivi, MAX, tiedosto) != NULL) { //Luetaan rivi kerrallaan tuotetiedostosta.
			printf("%s", rivi);
		}
	}
	else{
		printf("Tuotetiedosto on tyhjä!\n");
	}
	fclose(tiedosto);
}
//tämä aliohjelma lisää pullo/tölkkiparametrit tuotetiedostoon
void lisaaTuotetiedostoon(){
	FILE *tiedosto;

	if ((tiedosto = fopen("tuotetiedosto.txt", "a")) == NULL){
		printf("Tiedoston avaaminen epäonnistui.");
		exit(1);
	}
	else{
		char lisattavaNimi[MAX];
		char lisattavaKoko[MAX];
		char lisattavaHinta[MAX];

		printf("Anna lisättävän tuotteen nimi (Syötä merkkijono!): ");
		fgets(lisattavaNimi, MAX, stdin);
		if ((strlen(lisattavaNimi))<=1){
			printf("Tyhjä syöte!\n");
			return;
			}
		lisattavaNimi[strcspn(lisattavaNimi, "\n")] = 0;

		printf("Anna lisättävän tuotteen koko (Syötä muodossa x.xx!): ");
		fgets(lisattavaKoko, MAX, stdin);
		if ((strlen(lisattavaKoko))<=1){
			printf("Tyhjä syöte!\n");
			return;
			}
		lisattavaKoko[strcspn(lisattavaKoko, "\n")] = 0;

		printf("Anna lisättävän tuotteen hinta (Syötä muodossa x.xx!): ");
		fgets(lisattavaHinta, MAX, stdin);
		if ((strlen(lisattavaKoko))<=1){
			printf("Tyhjä syöte!\n");
			return;
			}
		lisattavaHinta[strcspn(lisattavaHinta, "\n")] = 0;

		fprintf(tiedosto,"%s %s %s\n",lisattavaNimi,lisattavaKoko,lisattavaHinta);
	}
	fclose(tiedosto);
}
//tällä aliohjelmalla voidaan tyhjentää koko tuotetiedosto
void tyhjennaTuotetiedosto(){
	FILE *tiedosto;
	char valintaMerkki[MAX];
	int valinta = -1;

	//kysytään käyttäjältä onko hän aivan varma että hän haluaa tyhjentää koko tuotetiedoston
	printf("\nOletko varma että haluat tyhjentää tuotetiedoston?\n");
	printf("Kaikki pulloparametrit häviää!\n");
	while (valinta != 0){
		printf("1 = Kyllä \n");
		printf("0 = Ei\n\n");
		printf("-->");

		fgets(valintaMerkki, MAX, stdin);
		int testaus=SyoteTarkistus(valintaMerkki);
		if (testaus==0){
			printf("Väärä valinta!\n");
		}
		else{
			valinta = atoi(valintaMerkki);
			if(valinta == 0){
				printf("\nTuotelistaa ei tyhjennetty.\n");
				break;
			}
			else if(valinta == 1){
				if ((tiedosto = fopen("tuotetiedosto.txt", "w")) == NULL){
					printf("Tiedoston avaaminen epäonnistui.\n");
					fclose(tiedosto);
				}
				else{
					printf("Tuotetiedosto tyhjennetty!\n");
					fclose(tiedosto);
				}
				break;
			}
			else{
				printf("\nVastaa 1 tai 0\n");
			}
		}
	}
}
//tällä aliohjelmalla saadaan poistettua yksi pullo/tölkkiparametri tuotetiedostosta
void poistaTuotetiedostosta(){
	/* toteutimme parametrin poiston tekemällä kaksi väliaikaista teksitiedostoa. Näiden avulla mahdollistamme tiedoston muokkaamisen. Ohjelman lopussa ptrtiedosto2 
	nimetään uudestaan alkuperäisen nimiseksi tuotetiedostoksi. Alkuperäistä tuotetiedostoa ei siis muokata missään vaiheessa. Sitä ainoastaan luetaan ja se poistetaan.*/

	FILE *ptrtiedosto1, *ptrtiedosto2;
	char ch;
	int poistettavaRivi;
	int temp = 1;
	int rivimaara = 0;
	char rivi[MAX];
	char valintaMerkki[MAX];

	if((ptrtiedosto1 = fopen("tuotetiedosto.txt", "r")) == NULL){
		perror("Tuotetiedoston avaaminen ei onnistu.\n");
		exit(1);
	}
	if((ptrtiedosto2 = fopen("vastaava.txt", "w")) == NULL){
		perror("Replikan avaaminen ei onnistu.\n");
		exit(1);
	}
	while(fgets(rivi, MAX, ptrtiedosto1) != NULL) {
		rivimaara++;
	}
	if (rivimaara > 0){
		rewind(ptrtiedosto1);
		rivimaara = 0;

		printf("Minkä pulloparametrin haluat poistaa?\n");
		while(fgets(rivi, MAX, ptrtiedosto1) != NULL) {
			printf("%d) %s",rivimaara+1, rivi);
			rivimaara++;
		}
		printf("0) Peruuta rivin poisto.\n");
		printf("\n-->");
		
		fgets(valintaMerkki, MAX, stdin);
		int testaus=SyoteTarkistus(valintaMerkki);
		if (testaus==0){
			printf("Väärä valinta!\n");
		}
		else{
			rewind(ptrtiedosto1);		

			poistettavaRivi = atoi(valintaMerkki);
			if(poistettavaRivi > rivimaara || poistettavaRivi < 0){
				printf("Tuntematon valinta!\n");
			}
			else if(poistettavaRivi == 1){
				//mikäli poistettava pullo/tölkkiparametri on tekstitiedostossa ensimmäisenä mennään tähän toimintahaaraan
				ch = getc(ptrtiedosto1);
				while(ch != '\n'){
					ch = getc(ptrtiedosto1);
				}
				while( ch != EOF){
					ch = getc(ptrtiedosto1);
					if(ch == EOF){
						break;
						}
					putc(ch, ptrtiedosto2);
				}
				remove("tuotetiedosto.txt"); //poistetaan alkuperäinen wanhentunut tuotetiedosto
				rename("vastaava.txt","tuotetiedosto.txt"); //Nimetään uusi muokattu tuotetiedosto muun ohjelman hyväksymään muotoon
				printf("\nPoistaminen onnistui.\n");
			}
			else if(poistettavaRivi <= rivimaara && poistettavaRivi>0){
				//Mikäli poistettava pullo/tölkkiparametri on tekstitiedostossa muulla kuin ensimmäisellä sijalla mennään tähän haaraan
				ch = getc(ptrtiedosto1);
				putc(ch, ptrtiedosto2);

				while( ch != EOF){
					ch = getc(ptrtiedosto1);
					if (ch == '\n'){
						temp++;
					}
					if(ch == EOF){
						break;
					}
					else if (temp != poistettavaRivi){
						putc(ch, ptrtiedosto2);
					}
				}
				remove("tuotetiedosto.txt"); //poistetaan alkuperäinen wanhentunut tuotetiedosto
				rename("vastaava.txt","tuotetiedosto.txt"); //Nimetään uusi muokattu tuotetiedosto muun ohjelman hyväksymään muotoon
				printf("\nPoistaminen onnistui.\n");
			}
			else if(poistettavaRivi == 0){
				printf("Peruutetaan poistaminen.\n");
			}
			else{
				perror("Tuntematon valinta!\n");
			}
		}
	}
	else{
		printf("Tuotetiedosto on tyhjä!\n");
	}
	fclose(ptrtiedosto1);
	fclose(ptrtiedosto2);
}
void lokiTulostus(){
	FILE *tiedosto;
	float jakaja;
	char rivi[MAX];
	char *rivinLukija;
	float summa=0.00;

	if ((tiedosto = fopen("lokitiedosto.txt", "r")) == NULL){
		perror("Lokitiedostoa ei löydy!\n");
		exit(0);
	}
	else{
		printf("Lokitiedostoon kirjatut tiedot:\n\n");
		while(fgets(rivi, MAX, tiedosto) != NULL) { //Luetaan rivi kerrallaan lokitiedostosta.
			printf("%s", rivi);
			rivinLukija=strtok(rivi, " ");
			rivi[strcspn(rivi, "\n")] = 0; //Poistetaan rivinvaihtomerkki
			rivinLukija=strtok(NULL, " ");
			rivinLukija=strtok(NULL, " ");
			rivinLukija=strtok(NULL, " ");			
			rivinLukija=strtok(NULL, " ");
			rivinLukija=strtok(NULL, " ");
			rivinLukija=strtok(NULL, " ");
			rivinLukija=strtok(NULL, "€");
			summa=summa+atof(rivinLukija);
			jakaja++;
		}
		printf("\n---------------------------------------\n");
		printf("Tilastostatiikka:\n");
		printf("Keskimääräinen palautus: %3.2f€\n", summa/jakaja);
		printf("Kokonaispalautukset: %3.2f€\n", summa);
		printf("---------------------------------------\n");
	}
	printf("--> Paina Enter jatkaaksesi ");
	while(getchar()!='\n');
	fclose(tiedosto);
}
void lokiPaivaAnalyysi(){
//Tämä aliohjelma analysoi tietyn päivän palautukset
	FILE *tiedosto;
	char annettuPvm[MAX];
	char *rivinLukija;
	char tiedostoPvm[MAX];
	char rivi[MAX];
	int loytyi = -1;
	int palautusLkm=0;
	float loppusumma=0;

	printf("Minkä päivän lokitiedot haluat etsiä?\n");
	printf("Anna päivämäärä muodossa dd.mm.yyyy: ");
	fgets(annettuPvm, 18, stdin);
	printf("\nEtsitään tietoja päivältä: %s\n", annettuPvm);
	annettuPvm[strcspn(annettuPvm, "\n")] = 0;
	if ((tiedosto = fopen("lokitiedosto.txt", "r")) == NULL){
		perror("Lokitiedostoa ei löydy!\n");
		exit(0);
	}
	else{
		while(fgets(rivi, MAX, tiedosto) != NULL) { //Luetaan rivi kerrallaan lokitiedostosta.
			rivinLukija = strtok(rivi, " ");

			strcpy(tiedostoPvm, rivinLukija);
			tiedostoPvm[strcspn(tiedostoPvm, "\n")] = 0;

			if ((strcmp(annettuPvm, tiedostoPvm))==0){
				rivinLukija = strtok(NULL, " "); //Kello
				printf("Palautus kello %s.\n", rivinLukija); 
				rivinLukija = strtok(NULL, " "); // -
				rivinLukija = strtok(NULL, " "); // Palatukset
				rivinLukija = strtok(NULL, " "); // palautus LKM
				palautusLkm=palautusLkm+atoi(rivinLukija);
				printf("Palautettiin %s kpl tuotteita, joista maksettiin yhteensä: ", rivinLukija); 
				rivinLukija = strtok(NULL, " "); // kpl.
				rivinLukija = strtok(NULL, " "); // Pantit
				rivinLukija = strtok(NULL, " "); // X€.
				loppusumma=loppusumma+atof(rivinLukija);
				printf("%s\n", rivinLukija);
				loytyi = 1;
			}
		}
		if (loytyi == -1){
			printf("Kyseistä päivää ei löytynyt.\n\n");
		}
		else{
			printf("---------------------------------------\n");
			printf("Päivän %s saldo:\n", annettuPvm);
			printf("Palautettiin yhteensä %d tuotetta.\n", palautusLkm);
			printf("Päivän palautusten kokonaissaldo %3.2f€\n", loppusumma);
			printf("---------------------------------------\n");
		}
	}
	printf("--> Paina Enter jatkaaksesi ");
	while(getchar()!='\n');
	fclose(tiedosto);
}
void yllapitovalikko(){
//Tämä toimii yllapito-aliohjelman valikkona.
	int valinta = -1;
	char valintaMerkki[MAX];

	while(valinta != 0){
		printf("\n\n***Tuotetiedoston operaatiot***\n");
		printf("1) Tulosta tuotetiedosto\n");
		printf("2) Lisää tuote tuotetiedostoon\n");
		printf("3) Poista tuote tuotetiedostosta\n");
		printf("4) Tyhjennä tuotetiedosto\n\n");

		printf("***Lokitiedoston operaatiot***\n");
		printf("5) Tulosta lokitiedot\n");
		printf("6) Etsi lokitiedostosta tietyn päivän tulos\n\n"); 

		printf("0) Palaa alkuvalikkoon\n\n");
		printf("Valitse: ");
		fgets(valintaMerkki, MAX, stdin);

		int testaus=SyoteTarkistus(valintaMerkki);
		if (testaus==0){
			printf("Väärä valinta!\n");
		}
		else{
			valinta = atoi(valintaMerkki);
			if(valinta == 1){
				tulostaTuotetiedosto();
			}
			else if(valinta == 2){
				lisaaTuotetiedostoon();
			}
			else if(valinta == 3){
				poistaTuotetiedostosta();
			}
			else if(valinta == 4){
				tyhjennaTuotetiedosto();
			}
			else if(valinta == 5){
				lokiTulostus();
			}
			else if(valinta ==6){
				lokiPaivaAnalyysi();
			}
			else if(valinta == 0){
				printf("Lopetetaan tuotetiedoston muokkaus.\n");
			}
			else{
				printf("Tunnistamaton valinta!\n");
			}
		}
	}
}
